#include <cstdio>
#include <iostream>
#include <chrono>
#include <boost/filesystem/operations.hpp>
#include "../src/exact.h"
#include "../src/Utils.h"
#include "grafGen.h"
#include "../src/greedy.h"
#include "../src/localsearch.h"
#include "../src/grasp.h"

#define FILE_EXACT  "exact.csv"
#define FILE_GREEDY "greedy.csv"
#define FILE_LOCAL  "local.csv"
#define FILE_GRASP  "grasp.csv"
#define FILE_FIT    "fit.csv"

#define ACCURACY(file) ("accuracy-"+std::string(file)).c_str()

#define GET_TIME std::chrono::high_resolution_clock::now()
#define GET_TIME_DELTA(begin, end) \
 std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count()

#define REPETITIONS (unsigned int)100
#define MIN_N  (unsigned int)2
#define MAX_N  (unsigned int)40
#define MIN_M  (unsigned int)0
#define MAX_M  (unsigned int)80

#define MAX_IT (unsigned int)15

struct testcase {
    graphInfo input;
    cliqueInfo output;
};

#define BIGDIR "enormes"
#define IN_FILEEXT ".in"
#define OUT_FILEEXT ".out"

void print_help(char* name) {
    std::cout << "Uso: " << name << " <impl>" << std::endl
              << std::endl
              << "donde las implementaciones son:" << std::endl
              << "        all : ejectuar pruebas de perf de todas las implementaciones" << std::endl
              << "      exact : metodo por fuerza bruta" << std::endl
              << "  heuristic : ejecutar pruebas de perf de todas las heuristicas" << std::endl
              << "     greedy : heuristica golosa" << std::endl
              << "      local : heuristica de busqueda local" << std::endl
              << "      grasp : heuristica golosa con metaheuristica GRASP" << std::endl
              << "   accuracy : mide la precision de los algoritmos heuristicos" << std::endl
              << "        fit : genera datos de fitteo para GRASP" << std::endl
              << std::endl;
}

int runExact();
int runGreedy();
int runGreedyMaxDeg();
int runGreedyEqDeg();
int runLocal();
int runGrasp();
int runAccuracy();
int runFit();
std::vector<testcase> generateRandomTests();
std::vector<testcase> getTests();

int main(int argc, char* argv[]) {
    if (argc != 2) {
        print_help(argv[0]);
        return argc == 1 ? 0 : 1;
    }
    std::string impl(argv[1]);

    if(impl == "all") {
        runExact();
        runGreedy();
        runLocal();
        runGrasp();
        return 0;
    } else if(impl == "heuristic") {
        runGreedy();
        runLocal();
        runGrasp();
        return 0;
    } else if(impl == "exact") {
        return runExact();
    } else if(impl == "greedy") {
        return runGreedyEqDeg();
    } else if(impl == "local") {
        return runLocal();
    } else if(impl == "grasp") {
        return runGrasp();
    } else if(impl == "accuracy") {
        return runAccuracy();
    } else if(impl == "fit") {
        return runFit();
    } else {
        std::cout << "No entendi que implementacion es." << std::endl;
        return 1;
    }
}

int runExact() {
    remove(FILE_EXACT);
    FILE* data = fopen(FILE_EXACT, "a");

    fprintf(data, "n,m,ns\n");
    for (unsigned int n = MIN_N; n <= MAX_N; ++n) {
        edgeList kGraph = genKGraph(n);
        for (unsigned int m = MIN_M; m <= std::min(MAX_M, (n*(n-1)) >> 1); ++m) {
            edgeList graph = getSubgraph(m, kGraph);
            graphInfo info = {n, graph};
            std::cout << "impl = exact, n = " << n << ", m = " << m
                      << "                " << "\r" << std::flush;
            for (unsigned int i = 0; i < REPETITIONS; ++i) {

                auto begin = GET_TIME;

                exactCMF(info);

                auto end = GET_TIME;

                fprintf(data, "%d,%d,%ld\n", n, m, GET_TIME_DELTA(begin, end));
            }
        }
    }
    std::cout << "exact = done!                " << std::endl;
    fclose(data);
    return 0;
}

int runGreedy() {
    remove(FILE_GREEDY);
    FILE* data = fopen(FILE_GREEDY, "a");

    fprintf(data, "n,m,ns\n");
    for (unsigned int n = MIN_N; n <= MAX_N; ++n) {
        edgeList kGraph = genKGraph(n);
        for (unsigned int m = MIN_M; m <= (n*(n-1)) >> 1; ++m) {
            edgeList graph = getSubgraph(m, kGraph);
            adjList input = Graph::createAdjacencyList({n, graph});
            std::cout << "impl = greedy, n = " << n << ", m = " << m
                      << "                " << "\r" << std::flush;
            for (unsigned int i = 0; i < REPETITIONS; ++i) {
                auto begin = GET_TIME;

                greedyHeuristic(input);

                auto end = GET_TIME;

                fprintf(data, "%d,%d,%ld\n", n, m, GET_TIME_DELTA(begin, end));
            }
        }
    }
    std::cout << "greedy = done!                " << std::endl;
    fclose(data);
    return 0;
}

int runGreedyMaxDeg() {
    remove(FILE_GREEDY);
    FILE* data = fopen(FILE_GREEDY, "a");

    fprintf(data, "n,m,maxDeg,ns\n");
    //for (unsigned int n = MIN_N; n <= MAX_N; ++n) {
    unsigned int n = 80;
    //for (unsigned int m = MIN_M; m <= (n*(n-1)) >> 1; ++m) {
    unsigned int m = (n*(n-1)) >> 4;
    for (unsigned int maxDeg = 0; maxDeg < std::min(n,m); ++maxDeg) {
        try {
            adjList input = createWithMaxDeg(n, m, maxDeg);
            std::cout << "impl = greedy, n = " << n << ", m = " << m
                      << ", maxDeg = " << maxDeg
                      << "                " << "\r" << std::flush;
            for (unsigned int i = 0; i < REPETITIONS; ++i) {
                auto begin = GET_TIME;

                greedyHeuristic(input);

                auto end = GET_TIME;

                fprintf(data, "%d,%d,%d,%ld\n", n, m, maxDeg, GET_TIME_DELTA(begin, end));
            }
        } catch (graphGenException& ex) {
            // skip
        }
    }
    //}
    //}
    std::cout << "greedy = done!                " << std::endl;
    fclose(data);
    return 0;
}

int runGreedyEqDeg() {
    remove(FILE_GREEDY);
    FILE* data = fopen(FILE_GREEDY, "a");

    fprintf(data, "n,m,maxDeg,ns\n");
    for (unsigned int n = MIN_N; n <= MAX_N; ++n) {
        for (unsigned int m = MIN_M; m <= (n*(n-1)) >> 1; ++m) {
            //for (unsigned int maxDeg = 0; maxDeg < n; ++maxDeg) {
                unsigned int maxDeg = (m << 1) / n;
                if((m << 1) % n > 0) {
                    ++maxDeg;
                }
                try {
                    adjList input = createWithMaxDeg(n, m, maxDeg);
                    std::cout << "impl = greedy, n = " << n << ", m = " << m
                              << ", maxDeg = " << maxDeg
                              << "                " << "\r" << std::flush;
                    for (unsigned int i = 0; i < REPETITIONS; ++i) {
                        auto begin = GET_TIME;

                        greedyHeuristic(input);

                        auto end = GET_TIME;

                        fprintf(data, "%d,%d,%d,%ld\n", n, m, maxDeg, GET_TIME_DELTA(begin, end));
                    }
                } catch (graphGenException& ex) {
                    // skip
                }
            //}
        }
    }
    std::cout << "greedy = done!                " << std::endl;
    fclose(data);
    return 0;
}

int runLocal() {
    remove(FILE_LOCAL);
    FILE* data = fopen(FILE_LOCAL, "a");

    fprintf(data, "n,m,ns\n");
    for (unsigned int n = MIN_N; n <= MAX_N; ++n) {
        edgeList kGraph = genKGraph(n);
        for (unsigned int m = MIN_M; m <= std::min(MAX_M, (n*(n-1)) >> 1); ++m) {
            edgeList graph = getSubgraph(m, kGraph);
            adjList adjacencies = Graph::createAdjacencyList({n, graph});
            cliqueInfo partialClique = greedyHeuristic(adjacencies);

            std::cout << "impl = local, n = " << n << ", m = " << m
                      << "                " << "\r" << std::flush;

            for (unsigned int i = 0; i < REPETITIONS; ++i) {
                auto begin = GET_TIME;

                localSearchHeuristic(adjacencies, partialClique);

                auto end = GET_TIME;

                fprintf(data, "%d,%d,%ld\n", n, m, GET_TIME_DELTA(begin, end));
            }
        }
    }
    std::cout << "local = done!                " << std::endl;
    fclose(data);
    return 0;
}

int runGrasp() {
    remove(FILE_GRASP);
    FILE* data = fopen(FILE_GRASP, "a");

    fprintf(data, "n,m,p,it,ns\n");
    for (unsigned int n = MIN_N; n <= MAX_N; ++n) {
        edgeList kGraph = genKGraph(n);
        for (unsigned int m = MIN_M; m <= std::min(MAX_M, (n*(n-1)) >> 1); ++m) {
            edgeList graph = getSubgraph(m, kGraph);
            adjList adjacencies = Graph::createAdjacencyList({n, graph});
            for (unsigned int p = 1; p <= 10; ++p) {
                float fp = (float)p/10;
                for (unsigned int it = 1; it <= MAX_IT; ++it) {
                    std::cout << "impl = grasp, n = " << n << ", m = " << m
                              << ", p = " << fp << ", it = " << it
                              << "     " << "\r" << std::flush;
                    for (unsigned int i = 0; i < REPETITIONS; ++i) {
                        auto begin = GET_TIME;

                        grasp(adjacencies, fp, it);

                        auto end = GET_TIME;

                        fprintf(data, "%d,%d,%.1f,%d,%ld\n", n, m, fp, it, GET_TIME_DELTA(begin, end));
                    }
                }
            }
        }
    }
    std::cout << "grasp = done!                " << std::endl;
    fclose(data);
    return 0;
}

int runAccuracy() {
    FILE* data;

    std::vector<testcase> cases = generateRandomTests();

    remove(ACCURACY(FILE_GREEDY));
    data = fopen(ACCURACY(FILE_GREEDY), "a");

    fprintf(data, "n,m,diff\n");
    for (auto it = cases.begin(); it != cases.end(); ++it) {
        adjList input = Graph::createAdjacencyList((*it).input);
        std::cout << "impl = greedy, n = " << input.size()
                  << ", m = " << (*it).input.edges.size()
                  << "                " << "\r" << std::flush;

        cliqueInfo output = greedyHeuristic(input);
        unsigned int diff = (*it).output.outgoing - output.outgoing;

        fprintf(data, "%ld,%ld,%d\n", input.size(), (*it).input.edges.size(), diff);
    }
    std::cout << "greedy = done!                " << std::endl;
    fclose(data);

    remove(ACCURACY(FILE_LOCAL));
    data = fopen(ACCURACY(FILE_LOCAL), "a");

    fprintf(data, "n,m,diff\n");
    for (auto it = cases.begin(); it != cases.end(); ++it) {
        adjList input = Graph::createAdjacencyList((*it).input);
        std::cout << "impl = local, n = " << input.size()
                  << ", m = " << (*it).input.edges.size()
                  << "                " << "\r" << std::flush;

        cliqueInfo output = localSearchHeuristic(input);
        unsigned int diff = (*it).output.outgoing - output.outgoing;

        fprintf(data, "%ld,%ld,%d\n", input.size(), (*it).input.edges.size(), diff);
    }
    std::cout << "local = done!                " << std::endl;
    fclose(data);


    remove(ACCURACY(FILE_GRASP));
    data = fopen(ACCURACY(FILE_GRASP), "a");

    fprintf(data, "n,m,p,it,diff\n");
    for (auto it = cases.begin(); it != cases.end(); ++it) {
        adjList input = Graph::createAdjacencyList((*it).input);

        //for (unsigned int p = 1; p <= 10; ++p) {
        //    float fp = (float)p/10;
        //    for (unsigned int i = 1; i <= MAX_IT; ++i) {
        float fp = 0.6f;
        unsigned int i = 50;
                std::cout << "impl = grasp, n = " << input.size()
                          << ", m = " << (*it).input.edges.size()
                          << ", p = " << fp
                          << ", it = " << i
                          << "     " << "\r"
                          << std::flush;

                cliqueInfo output = grasp(input, fp, i);

                unsigned int diff = (*it).output.outgoing - output.outgoing;

                fprintf(data, "%ld,%ld,%.1f,%d,%d\n", input.size(), (*it).input.edges.size(), fp, i, diff);
            //}
        //}
    }
    std::cout << "grasp = done!                " << std::endl;
    fclose(data);

    return 0;
}

int runFit() {
    std::vector<testcase> tests = getTests();
    if(tests.empty()) {
        std::cout << "¡No hay casos de test para fittear!" << std::endl;
        return 1;
    }
    remove(FILE_FIT);
    FILE* data = fopen(FILE_FIT, "a");

    fprintf(data, "n,m,p,it,diff\n");

    std::vector<testcase>::const_iterator it;
    for (it = tests.begin(); it != tests.end(); ++it) {
        unsigned int n = (*it).input.n;
        size_t m = (*it).input.edges.size();

        unsigned int best = (*it).output.outgoing;

        for (unsigned int p = 1; p <= 10; ++p) {
            float fp = (float)p/10;
            for (unsigned int i = 1; i <= MAX_IT; ++i) {
                std::cout << "n = " << n
                          << ", m = " << m
                          << ", p = " << fp
                          << ", it = " << i
                          << "     " << "\r"
                          << std::flush;

                cliqueInfo result = grasp((*it).input, fp, i);

                unsigned int diff = best - result.outgoing;

                fprintf(data, "%d,%ld,%.1f,%d,%d\n", n, m, fp, i, diff);
            }
        }
    }
    std::cout << "fitting = done!                        " << std::endl;
    fclose(data);
    return 0;
}

std::vector<testcase> generateRandomTests() {
    std::vector<testcase> tests;

    for (unsigned int n = MIN_N; n <= MAX_N; ++n) {
        edgeList kGraph = genKGraph(n);
        for (unsigned int m = MIN_M; m <= (n*(n-1)) >> 2; ++m) {
            edgeList graph = getSubgraph(m, kGraph);
            std::cout << "generating test case: n = " << n << ", m = " << m
                      << "                " << "\r" << std::flush;


            testcase aCase = {{n, graph}, exactCMF({n, graph})};
            tests.push_back(aCase);
        }
    }

    return tests;
}

std::vector<testcase> getTests() {
    std::vector<testcase> tests;
    std::string dirname = BIGDIR;

    if(boost::filesystem::exists(dirname)) {
        boost::filesystem::directory_iterator end_itr;
        for (boost::filesystem::directory_iterator itr(dirname); itr != end_itr; ++itr) {
            if (itr->path().extension() == OUT_FILEEXT) {
                std::string outputName = itr->path().string();
                std::string inputName = outputName.substr(0, outputName.size() - 4) + IN_FILEEXT;

                std::ifstream inputFile(inputName);
                tests.push_back({Utils::parseGraph(inputFile), Utils::parseCliqueInfo(outputName)});
                inputFile.close();
            }
        }
    }
    return tests;
}
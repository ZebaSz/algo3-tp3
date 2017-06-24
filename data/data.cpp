#include <cstdio>
#include <iostream>
#include <chrono>
#include "../src/exact.h"
#include "../src/Utils.h"
#include "grafGen.h"
#include "../src/greedy.h"
#include "../src/localsearch.h"

#define FILE_EXACT  "exact.csv"
#define FILE_GREEDY "greedy.csv"
#define FILE_LOCAL  "local.csv"
#define FILE_GRASP  "grasp.csv"

#define GET_TIME std::chrono::high_resolution_clock::now()
#define GET_TIME_DELTA(begin, end) \
 std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count()

#define REPETITIONS (unsigned int)100
#define MIN_N (unsigned int)2
#define MAX_N (unsigned int)20

void print_help(char* name) {
    std::cout << "Uso: " << name << " <impl>" << std::endl
              << std::endl
              << "donde las implementaciones son:" << std::endl
              << "      all : ejectuar todas las implementaciones" << std::endl
              << "    exact : brute-force" << std::endl
              << "   greedy : heuristica golosa" << std::endl
              << "    local : heuristica de busqueda local" << std::endl
              << "    grasp : heuristica golosa con metaheuristica GRASP" << std::endl
              << std::endl;
}

int runExact();
int runGreedy();
int runLocal();
int runGrasp();

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
    } else if(impl == "exact") {
        return runExact();
    } else if(impl == "greedy") {
        return runGreedy();
    } else if(impl == "local") {
        return runLocal();
    } else if(impl == "grasp") {
        return runGrasp();
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
        for (unsigned int m = 0; m <= (n*(n-1)) >> 1; ++m) {
            edgeList graph = getSubgraph(m, kGraph);
            graphInfo info = {n, graph};
            for (unsigned int i = 0; i < REPETITIONS; ++i) {
                std::cout << "impl = exact, n = " << n << ", m = " << m
                          << "     " << "\r" << std::flush;

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
        for (unsigned int m = 0; m <= (n*(n-1)) >> 1; ++m) {
            edgeList graph = getSubgraph(m, kGraph);
            graphInfo info = {n, graph};
            for (unsigned int i = 0; i < REPETITIONS; ++i) {
                std::cout << "impl = greedy, n = " << n << ", m = " << m
                          << "     " << "\r" << std::flush;
                auto begin = GET_TIME;

                greedyHeuristic(info);

                auto end = GET_TIME;

                fprintf(data, "%d,%d,%ld\n", n, m, GET_TIME_DELTA(begin, end));
            }
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
        for (unsigned int m = 0; m <= (n*(n-1)) >> 1; ++m) {
            edgeList graph = getSubgraph(m, kGraph);
            graphInfo info = {n, graph};
            for (unsigned int i = 0; i < REPETITIONS; ++i) {
                std::cout << "impl = local, n = " << n << ", m = " << m
                          << "     " << "\r" << std::flush;
                auto begin = GET_TIME;

                localSearchHeuristic(info);

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
    std::cout << "Oh noes! GRASP no esta listo!" << std::endl;
    return 1;
}

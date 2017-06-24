#include <iostream>
#include <chrono>
#include "grafGen.h"
#include "../src/delivery.h"
#include "../src/subsidy.h"
#include "../src/reconfiguration.h"

#define REPETITIONS (unsigned int)100
#define MAX_N (unsigned int)30
#define MAX_M (unsigned int)30
#define MAX_W (unsigned int)20

#define MAX_P (unsigned int)20
#define MAX_K (unsigned int)20

void getDataDelivery() {
    remove("delivery.csv");
    FILE* data = fopen("delivery.csv", "a");

    fprintf(data, "Ciudades,Rutas,TotalPremium,LimitePremium,Nanosegundos\n");
    for (unsigned int i = 2; i <= MAX_N; ++i) {
        printf("Running with %d cities for Delivery problem\n", i);
        for (unsigned int j = i-1; j <= std::min(MAX_M, (i*(i-1)) >> 1); ++j) {
            printf("Running with %d routes for Delivery problem\n", j);
            for (unsigned int k = 0; k <= std::min(j, MAX_P); ++k) {
                printf("Running with %d premium routes for Delivery problem\n", k);
                edgeList baseGraph;
                genConex(i, j, baseGraph, MAX_W);
                edgeList edges(baseGraph.begin(), baseGraph.end());
                edgeList premiumEdges;
                getSubgraph(k, edges, premiumEdges);
                for (unsigned int l = 0; l <= std::min(k, MAX_K); ++l) {
                    long best = -1;
                    for (unsigned int m = 0; m < REPETITIONS; ++m) {
                        auto begin = std::chrono::high_resolution_clock::now();

                        optimumDelivery(0, 1, i, l, edges, premiumEdges);

                        auto end = std::chrono::high_resolution_clock::now();
                        if(best == -1 || best > std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count()) {
                            best = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count();
                        }
                    }
                    fprintf(data, "%d,%d,%d,%d,%ld\n", i, j, k, l, best);
                }
            }
        }
    }
    fclose(data);
}

void getDataSubsidy() {
    remove("subsidy.csv");
    FILE* data = fopen("subsidy.csv", "a");

    fprintf(data, "Ciudades,Rutas,PesoMaximo,Nanosegundos\n");
    for (unsigned int i = 2; i <= MAX_N; ++i) {
        printf("Running with %d cities for Subsidy problem\n", i);
        for (unsigned int j = i; j <= std::min(MAX_M, (i*(i-1))); ++j) {
            printf("Running with %d routes for Subsidy problem\n", j);
            for (unsigned int k = 0; k <= MAX_W; ++k) {
                printf("Running with %d max weight for Subsidy problem\n", k);

                edgeList baseGraph;
                genKGraph(i, baseGraph, k, true);
                edgeList subgraph;
                getSubgraph(j, baseGraph, subgraph);

                long best = -1;
                for (unsigned int l = 0; l < REPETITIONS; ++l) {
                    auto begin = std::chrono::high_resolution_clock::now();

                    binarySearchTax(i, j, subgraph);

                    auto end = std::chrono::high_resolution_clock::now();
                    if (best == -1 ||
                        best > std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count()) {
                        best = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count();
                    }
                }
                fprintf(data, "%d,%d,%d,%ld\n", i, j, k, best);
            }
        }
    }
    fclose(data);
}

void getDataSubsidyComplete() {
    remove("subsidy-complete.csv");
    FILE* data = fopen("subsidy-complete.csv", "a");

    fprintf(data, "Ciudades,PesoMaximo,Nanosegundos\n");
    for (unsigned int i = 2; i <= MAX_N; ++i) {
        printf("Running with %d cities and complete graph for Subsidy problem\n", i);
        for (unsigned int k = 0; k <= MAX_W; ++k) {
            printf("Running with %d max weight for Subsidy problem\n", k);
            edgeList baseGraph;
            genKGraph(i, baseGraph, k, true);
            long best = -1;

            int j = i * i-1;
            for (unsigned int l = 0; l < REPETITIONS; ++l) {
                auto begin = std::chrono::high_resolution_clock::now();

                binarySearchTax(i, j, baseGraph);

                auto end = std::chrono::high_resolution_clock::now();
                if (best == -1 ||
                    best > std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count()) {
                    best = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count();
                }
            }
            fprintf(data, "%d,%d,%ld\n", i, k, best);
        }
    }

    fclose(data);
}

void getDataReconfiguration() {
    remove("reconfiguration.csv");
    FILE* data = fopen("reconfiguration.csv", "a");

    fprintf(data, "Ciudades,RutasExistentes,Nanosegundos\n");
    for (unsigned int i = 2; i <= MAX_N; ++i) {
        printf("Running with %d cities for Reconfiguration problem\n", i);
        edgeList baseGraph;
        genKGraph(i, baseGraph, MAX_W, false);
        unsigned int m = (i*(i-1)) >> 1;
        for (unsigned int j = 0; j <= m; ++j) {
            printf("Running with %d pre-existing routes for Reconfiguration problem\n", j);
            edgeList existing(baseGraph.begin(), baseGraph.end());
            edgeList potential;
            getSubgraph(m - j, existing, potential);

            long best = -1;
            for (unsigned int k = 0; k < REPETITIONS; ++k) {
                auto begin = std::chrono::high_resolution_clock::now();

                int p;
                rebuildRoads(i, p, existing, potential);

                auto end = std::chrono::high_resolution_clock::now();
                if(best == -1 || best > std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count()) {
                    best = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count();
                }
            }
            fprintf(data, "%d,%d,%ld\n", i, j, best);
        }
    }
    fclose(data);
}

int main() {
    getDataDelivery();
//    getDataSubsidy();
//    getDataSubsidyComplete();
//    getDataReconfiguration();
    return 0;
}

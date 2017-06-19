#ifndef ALGO3_TP3_EXACT_H
#define ALGO3_TP3_EXACT_H

#include "graph.h"

int exactCMF (int n, int m, const edgeList edges);
std::vector<int>* findCliques(int cliqueSize, int n, int** adjacencyMatrix);
bool itsAClique(const std::vector<int> clique, int** adjacencyMatrix);
int** createAdjacencyMatrix(int n, int m, const edgeList edges);

#endif //ALGO3_TP3_EXACT_H
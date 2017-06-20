#ifndef ALGO3_TP3_EXACT_H
#define ALGO3_TP3_EXACT_H

#include "graph.h"

typedef std::vector<int> nodeSet;
typedef std::vector< std::vector< bool > > adjMatrix;

unsigned int exactCMF(unsigned int n, unsigned int m, const edgeList& edges);
std::vector<nodeSet> findCliques(size_t cliqueSize, int n, const adjMatrix &adjacencyMatrix);
bool itsAClique(const nodeSet& clique, const adjMatrix& adjacencyMatrix);
adjMatrix createAdjacencyMatrix(unsigned int n, unsigned int m, const edgeList& edges);

#endif //ALGO3_TP3_EXACT_H
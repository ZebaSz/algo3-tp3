#ifndef ALGO3_TP3_GRAFGEN_H
#define ALGO3_TP3_GRAFGEN_H

#include "../src/graph.h"

edgeList genKGraph(unsigned int n);
edgeList shuffleEdges(const edgeList &edges);
edgeList getSubgraph(unsigned int m, const edgeList &base);

#endif //ALGO3_TP3_GRAFGEN_H

#ifndef ALGO3_TP2_GRAPH_H
#define ALGO3_TP2_GRAPH_H

#include <vector>

typedef unsigned int node;
typedef std::vector<unsigned int> nodeSet;
typedef std::vector< std::vector< bool > > adjMatrix;

struct edge {
    node start;
    node end;
};

typedef std::vector<edge> edgeList;

struct graphInfo {
    unsigned int n;
    edgeList edges;
};

#endif //ALGO3_TP2_GRAPH_H

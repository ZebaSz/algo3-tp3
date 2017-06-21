#ifndef ALGO3_TP3_CLIQUE_H
#define ALGO3_TP3_CLIQUE_H

#include "graph.h"

struct cliqueInfo {
    cliqueInfo(std::size_t k, unsigned int f) : nodes(k), outgoing(f) {}
    cliqueInfo(nodeSet g, unsigned int f) : nodes(g), outgoing(f) {}
    cliqueInfo(const cliqueInfo& other)  : nodes(other.nodes), outgoing(other.outgoing) {}

    nodeSet nodes;
    unsigned int outgoing;
};

#endif //ALGO3_TP3_CLIQUE_H

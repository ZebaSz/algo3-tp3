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


struct fullCliqueInfo {
    fullCliqueInfo(const nodeSet &insideNodes, const nodeSet &outsideNodes, unsigned int outgoing) : insideNodes(
            insideNodes), outsideNodes(outsideNodes), outgoing(outgoing) {}

    fullCliqueInfo(const fullCliqueInfo& another): insideNodes(another.insideNodes), outsideNodes(another.outsideNodes), outgoing(another.outgoing) {}

    nodeSet insideNodes;
    nodeSet outsideNodes;
    unsigned int outgoing;
};
#endif //ALGO3_TP3_CLIQUE_H

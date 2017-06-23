#include <iostream>
#include "graph.h"

bool ::Graph::allAdjacentTo(const adjMatrix &graph, const nodeSet &subclique, const unsigned int node) {
    for (size_t i = 0; i < subclique.size(); i++){
        if(!graph[subclique[i]][node]) {
            return false;
        }
    }
    return true;
}

bool ::Graph::allAdjacentTo(const adjList &graph, const nodeSet &subclique, const unsigned int node) {
    unsigned bool cliqueElementsFound[graph.size()];
    for (size_t i = 0; i < subclique.size(); i++) {
        cliqueElementsFound[i] = false;
    }
    for (size_t i = 0; i < graph[node].size(); i++) {
        cliqueElementsFound[graph[node][i]] = true;
    }
    for (size_t i = 0; i < subclique.size(); i++) {
        if (!cliqueElementsFound[i]) {
           return false;
        }
    }
    return true;
}

#include <iostream>
#include "graph.h"

bool ::Graph::allAdjacentTo(const adjMatrix &graph, const nodeSet &subclique, const node node) {
    for (size_t i = 0; i < subclique.size(); i++){
        if (!graph[subclique[i]][node]) {
            return false;
        }
    }
    return true;
}

bool ::Graph::allAdjacentTo(const adjList &graph, const nodeSet &subclique, const node node) {
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

bool ::Graph::allAdjacentToOrd(const adjList &graph, const nodeSet &subclique, const node node) {
    std::vector<unsigned int>::const_iterator it;
    size_t cliqueNodeIndex = 0;
    for (it = graph[node].begin(); it != graph[node].end(); ++it) {
        if (*it > subclique[cliqueNodeIndex]) {
            return false;
        } else if (*it == subclique[cliqueNodeIndex]) {
            cliqueNodeIndex++;
            if (cliqueNodeIndex == subclique.size()) {
                return true;
            }
        }
    }
    return false;
}

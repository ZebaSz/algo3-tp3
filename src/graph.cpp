#include <iostream>
#include "graph.h"

adjMatrix Graph::createAdjacencyMatrix(const graphInfo &input) {
    adjMatrix adjacencyMatrix(input.n, std::vector<bool>(input.n, false));
    for (size_t i = 0; i < input.edges.size(); i++) {
        adjacencyMatrix[input.edges[i].start][input.edges[i].end] = true;
        adjacencyMatrix[input.edges[i].end][input.edges[i].start] = true;
    }
    return adjacencyMatrix;
}

bool Graph::allAdjacentTo(const adjMatrix &graph, const nodeSet &subclique, const node node) {
    for (size_t i = 0; i < subclique.size(); i++){
        if (!graph[subclique[i]][node]) {
            return false;
        }
    }
    return true;
}

bool Graph::allAdjacentTo(const adjList &graph, const nodeSet &subclique, const node node) {
    std::vector<bool> cliqueElementsFound(graph.size(), false);
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

bool Graph::allAdjacentToOrd(const adjList &graph, const nodeSet &subclique, const node node) {
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




#include <iostream>
#include "graph.h"

adjMatrix Graph::createTriangularMatrix(const graphInfo &input) {
    adjMatrix adjacencyMatrix(input.n, std::vector<bool>(input.n, false));
    for (size_t i = 0; i < input.edges.size(); i++) {
        if(input.edges[i].start < input.edges[i].end) {
            adjacencyMatrix[input.edges[i].start][input.edges[i].end] = true;
        } else {
            adjacencyMatrix[input.edges[i].end][input.edges[i].start] = true;
        }
    }
    return adjacencyMatrix;
}

adjList Graph::createAdjacencyList(const graphInfo &input) {
    adjList adjacencyList;
    for (unsigned int i = 0; i < input.n; ++i) { // n nodes
        std::vector<node> v;
        adjacencyList.push_back(v);
    }
    for (size_t j = 0; j < input.edges.size(); ++j) { //add connections
        edge e = input.edges[j];
        insertSorted(adjacencyList[e.start], e.end);
        insertSorted(adjacencyList[e.end], e.start);
    }
    return adjacencyList;
}

void insertSorted(nodeSet &list, node n) {
    auto it = std::lower_bound( list.begin(), list.end(), n);
    list.insert(it, n);
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
    for (auto it = graph[node].begin(); it != graph[node].end(); ++it){
        cliqueElementsFound[*it] = true;
    }
    for (auto it = subclique.begin(); it != subclique.end(); ++it){
        if (!cliqueElementsFound[*it]) {
            return false;
        }
    }
    return true;
}

bool Graph::allAdjacentToExceptFor(const adjList &graph, const nodeSet &subclique, const node nodeToAdd, const node exception) {
    std::vector<bool> cliqueElementsFound(graph.size(), false);
    for (size_t i = 0; i < graph[nodeToAdd].size(); i++) {
        cliqueElementsFound[graph[nodeToAdd][i]] = true;
    }
    for (size_t i = 0; i < subclique.size(); i++) {
        if (!cliqueElementsFound[i] && i != exception) {
            return false;
        }
    }
    return true;
}

bool Graph::allAdjacentToExceptForDouble(const adjList &graph, const nodeSet &subclique, const node n1, const node n2, const node e1, const node e2) {
    std::vector<bool> cliqueElementsFound1(graph.size(), false);
    std::vector<bool> cliqueElementsFound2(graph.size(), false);
    for (size_t i = 0; i < graph[n1].size(); i++) {
        cliqueElementsFound1[graph[n1][i]] = true;
    }
    for (size_t i = 0; i < graph[n2].size(); i++) {
        cliqueElementsFound2[graph[n2][i]] = true;
    }
    for (size_t i = 0; i < subclique.size(); i++) {
        if ((!cliqueElementsFound1[i] || !cliqueElementsFound2[i]) && i != e1 && i != e2) {
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

node Graph::nodeWithMaxDegree(const adjList &graph) {
    node best = 0;
    for (node n = 1; n < graph.size() ; ++n) {
        if(graph[best].size() < graph[n].size()) {
            best = n;
        }
    }
    return best;
}


bool ::Graph::isAdjacentTo(const adjMatrix &graph, const node n1, const node n2) {
    if(n1 < n2) {
        return graph[n1][n2];
    } else {
        return graph[n2][n1];
    }
}

bool ::Graph::isAdjacentTo(const adjList &graph, const node n1, const node n2) {
    if (graph[n1].size() < graph[n2].size()) {
        return std::binary_search(graph[n1].begin(), graph[n1].end(), n2);
    } else {
        return std::binary_search(graph[n2].begin(), graph[n2].end(), n1);
    }
}

void ::Graph::sortByDegree(nodeSet nodesToSort, const adjList &graph) {
    std::sort(nodesToSort.begin(), nodesToSort.end(), greaterDegreeComparator(graph));
}

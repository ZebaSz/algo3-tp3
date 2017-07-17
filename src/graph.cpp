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

node Graph::nodeWithMaxDegree(const adjList &graph) {
    node best = 0;
    for (node n = 1; n < graph.size() ; ++n) {
        if(graph[best].size() < graph[n].size()) {
            best = n;
        }
    }
    return best;
}

void ::Graph::sortByDegree(nodeSet nodesToSort, const adjList &graph) {
    std::sort(nodesToSort.begin(), nodesToSort.end(), greaterDegreeComparator(graph));
}

graphInfo Graph::generatePatologicGraphForGreedy(unsigned int maxNodeDegree) {
    unsigned int maxCliqueSize = maxNodeDegree / 2;
    unsigned int n = (maxNodeDegree + 1) + maxCliqueSize + (maxNodeDegree - maxCliqueSize) * maxCliqueSize;
    edgeList edges;

    //El solsito el nodo, 0 tiene grado maxNodeDegree
    for (unsigned int i = 1; i <= maxNodeDegree; i++) {
        edges.push_back({0, i});
    }

    //Hago la frontera de la clique
    unsigned int frontierOffset = maxNodeDegree + maxCliqueSize + 1;
    for (unsigned int i = 1; i <= maxCliqueSize; i++) {
        unsigned int cliqueNode = maxNodeDegree + i;
        for (unsigned int j = 1; j <= (maxNodeDegree - maxCliqueSize); j++) {
            edges.push_back({cliqueNode, frontierOffset});
            frontierOffset++;
        }
    }

    //Cliqueo
    for (unsigned int i = 1; i < maxCliqueSize; i++) {
        unsigned int cliqueNode = maxNodeDegree + i;
        for (unsigned int j = i + 1; j <= maxCliqueSize; j++) {
            unsigned int cliqueNodePair = maxNodeDegree + j;
            edges.push_back({cliqueNode, cliqueNodePair});
        }
    }
    return { n, edges };
}

graphInfo Graph::generatePatologicGraphForGrasp(unsigned int maxNodeDegree, unsigned int amountOfMaxNodesDegree) {
    unsigned int maxCliqueSize = maxNodeDegree / 2;
    unsigned int n = (maxNodeDegree + 1) * amountOfMaxNodesDegree + maxCliqueSize + (maxNodeDegree - maxCliqueSize) * maxCliqueSize;
    edgeList edges;

    unsigned int offset = amountOfMaxNodesDegree;
    //El solsito el nodo, 0 tiene grado maxNodeDegree
    for (unsigned int i = 0; i < amountOfMaxNodesDegree; i++) {
        for (unsigned int j = 1; j <= maxNodeDegree; j++) {
            edges.push_back({i, offset});
            offset++;
        }
    }

    offset --;
    //Hago la frontera de la clique
    unsigned int frontierOffset = offset + maxCliqueSize + 1;
    for (unsigned int i = 1; i <= maxCliqueSize; i++) {
        unsigned int cliqueNode = offset + i;
        for (unsigned int j = 1; j <= (maxNodeDegree - maxCliqueSize); j++) {
            if(frontierOffset >= n) {
                edges.push_back({cliqueNode, frontierOffset});
            }
            edges.push_back({cliqueNode, frontierOffset});
            frontierOffset++;
        }
    }

    //Cliqueo
    for (unsigned int i = 1; i < maxCliqueSize; i++) {
        unsigned int cliqueNode = offset + i;
        for (unsigned int j = i + 1; j <= maxCliqueSize; j++) {
            unsigned int cliqueNodePair = offset + j;
            edges.push_back({cliqueNode, cliqueNodePair});
        }
    }
    return { n, edges };
}
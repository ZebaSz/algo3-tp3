#include <iostream>
#include "exact.h"
#include "Utils.h"

bool isClique(const adjMatrix& graph, const nodeSet& subclique, unsigned int node) {
    for (size_t i = 0; i < subclique.size(); i++){
        if(!graph[subclique[i]][node]) {
            return false;
        }
    }
    return true;
}

void expandCliques(const adjMatrix& graph, const std::vector<nodeSet>& subcliques,
                   std::vector<nodeSet>& cliques) {
    std::vector<nodeSet>::const_iterator it;
    for(it = subcliques.begin(); it != subcliques.end(); ++it) {
        for(unsigned int i = 0; i < graph.size(); ++i) {
            if(isClique(graph, *it, i)) {
                cliques.push_back(*it);
                cliques.back().push_back(i);
            }
        }
    }
}

std::vector<nodeSet> findAllCliques(const adjMatrix& graph) {
    std::vector< std::vector<nodeSet> > memo(graph.size() - 1);

    for (unsigned int i = 0; i < graph.size(); ++i) {
        memo[0].push_back(nodeSet(1,i));
    }

    for (size_t i = 1; i < memo.size(); ++i) {
        expandCliques(graph, memo[i-1], memo[i]);
    }

    std::vector<nodeSet> cliques;

    std::vector< std::vector<nodeSet> >::const_iterator it;
    for(it = memo.begin(); it != memo.end(); ++it) {
        Utils::addAll(cliques, *it);
    }
    return cliques;
}

adjMatrix createAdjacencyMatrix(unsigned int n, const edgeList &edges) {
    adjMatrix adjacencyMatrix(n, std::vector<bool>(n, false));
    for (size_t i = 0; i < edges.size(); i++) {
        if(edges[i].start < edges[i].end) {
            adjacencyMatrix[edges[i].start][edges[i].end] = true;
        } else {
            adjacencyMatrix[edges[i].end][edges[i].start] = true;
        }
    }
    return adjacencyMatrix;
}

unsigned int exactCMF(unsigned int n, const edgeList &edges) {
    std::vector<unsigned int> degree(n, 0);
    for (size_t i = 0; i < edges.size(); i++){
        degree[edges[i].start]++;
        degree[edges[i].end]++;
    }
    adjMatrix graph(createAdjacencyMatrix(n, edges));
    unsigned int maxDegree = 0;
    for (size_t i = 0; i < degree.size(); i++){
        if (degree[i] > maxDegree){
            maxDegree = degree[i];
        }
    }
    std::vector<nodeSet> cliques(findAllCliques(graph));
    unsigned int answer = 0;
    for (size_t i = 0; i < cliques.size(); i++){
        unsigned int count = 0;
        for (size_t j = 0; j < cliques[i].size(); ++j) {
            count += degree[cliques[i][j]] + 1 - cliques[i].size();
        }
        if (count > answer){
            answer = count;
        }
    }
    return answer;
}
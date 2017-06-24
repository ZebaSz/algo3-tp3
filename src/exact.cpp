#include <iostream>
#include "exact.h"
#include "Utils.h"

void expandCliques(const adjMatrix& graph, const std::vector<nodeSet>& subcliques,
                   std::vector<nodeSet>& cliques) {
    std::vector<nodeSet>::const_iterator it;
    for(it = subcliques.begin(); it != subcliques.end(); ++it) {
        for(unsigned int i = 0; i < graph.size(); ++i) {
            if(Graph::allAdjacentTo(graph, *it, i)) {
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


cliqueInfo exactCMF(const graphInfo &input) {
    std::vector<unsigned int> degree(input.n, 0);
    for (size_t i = 0; i < input.edges.size(); i++){
        degree[input.edges[i].start]++;
        degree[input.edges[i].end]++;
    }
    // We use a triangular matrix to avoid generating duplicated cliques
    adjMatrix graph(Graph::createAdjacencyMatrix(input));
    unsigned int maxDegree = 0;
    for (size_t i = 0; i < degree.size(); i++){
        if (degree[i] > maxDegree){
            maxDegree = degree[i];
        }
    }
    std::vector<nodeSet> cliques(findAllCliques(graph));

    size_t bestPos = 0;
    unsigned int bestCount = 0;
    for (size_t i = 0; i < cliques.size(); i++){
        unsigned int count = 0;
        for (size_t j = 0; j < cliques[i].size(); ++j) {
            count += degree[cliques[i][j]] + 1 - cliques[i].size();
        }
        if (count > bestCount){
            bestCount = count;
            bestPos = i;
        }
    }
    return {cliques[bestPos], bestCount};
}
#include <iostream>
#include "exact.h"

unsigned int exactCMF(unsigned int n, unsigned int m, const edgeList& edges){
    std::vector<unsigned int> degree(n, 0);
    for (size_t i = 0; i < edges.size(); i++){
        degree[edges[i].start]++;
        degree[edges[i].end]++;
    }
    adjMatrix adjacencyMatrix(createAdjacencyMatrix(n, m, edges));
    unsigned int maxDegree = 0;
    for (size_t i = 0; i < degree.size(); i++){
        if (degree[i] > maxDegree){
            maxDegree = degree[i];
        }
    }
    std::vector<nodeSet> cliques;
    for (size_t i = 1; i < maxDegree; i++){
        std::vector<nodeSet> nCliques(findCliques(i, n, adjacencyMatrix));
        cliques.insert(cliques.end(), nCliques.begin(), nCliques.end());
    }
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

std::vector<nodeSet> findCliques(size_t cliqueSize, int n, const adjMatrix &adjacencyMatrix){
    std::vector<nodeSet> cliques;
    for (int i = 0; i < n; i++) {
        bool hasCliques = true;
        nodeSet aNewClique;
        aNewClique.push_back(i);
        int j = i + 1;
        while (hasCliques) {
            int r = j;
            while (aNewClique.size() < cliqueSize && r < n) {
                if (adjacencyMatrix[i][r]){
                    aNewClique.push_back(r);
                }
                r++;
            }
            if (aNewClique.back() == i){
                hasCliques = false;
            }
            if (r < n && itsAClique(aNewClique, adjacencyMatrix)) {
                cliques.push_back(aNewClique);
            }
            j = aNewClique.back() + 1;
            aNewClique.pop_back();

        }
    }
    return cliques;
}

bool itsAClique(const nodeSet& clique, const adjMatrix& adjacencyMatrix){
    for (size_t i = 0; i < clique.size(); i++){
        for (size_t j = i + 1; j < clique.size(); j++){
            if (!adjacencyMatrix[i][j]){
                return false;
            }
        }
    }
    return true;
}

adjMatrix createAdjacencyMatrix(unsigned int n, unsigned int m, const edgeList& edges){
    adjMatrix adjacencyMatrix(n, std::vector<bool>(n, false));
    for (unsigned int i = 0; i < m; i++){
        adjacencyMatrix[edges[i].start][edges[i].end] = true;
        adjacencyMatrix[edges[i].end][edges[i].start] = true;
    }
    return adjacencyMatrix;
}
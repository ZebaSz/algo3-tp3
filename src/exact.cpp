#include <iostream>
#include "exact.h"

int exactCMF (int n, int m, const edgeList edges){
    int* degree = new int[n];
    int i;
    for (i = 0; i < m; i++){
        degree[edges[i].start]++;
        degree[edges[i].end]++;
    }
    int maxDegree = degree[0];
    for (i = 0; i < n; i++){
        if (degree[i] > maxDegree){
            maxDegree = degree[i];
        }
    }
    std::vector<std::vector<int>*>* cliques = new std::vector<std::vector<int>*>;
    for (i = 0; i < maxDegree; i++){
        cliques->push_back(findCliques(i, n, m, edges)); //Agregamos i elementos para cada clique, y un -1 al final
    }
    int answer = 0;
    for (i = 0; i < maxDegree; i++){
        int j = 0;
        int count = 0;
        while (cliques->at((unsigned long)i)->at((unsigned long)j) != -1){
            if ((j+1) % i == 0){
                if (count > answer){
                    answer = count;
                }
                count = 0;
            } else {
                count = count + degree[cliques->at((unsigned long)i)->at((unsigned long)j)] - i + 1;
            }
            j++;
        }
    }

    delete[] degree;
    for (i = 0; i < cliques->size(); i++){
        delete[] cliques->at(i);
    }
    delete[] cliques;

    return answer;
}

std::vector<int>* findCliques(int cliqueSize, int n, int m, const edgeList edges){
    std::vector<int>* cliques = new std::vector<int>;
    int** adjacencyMatrix = new int*[n];
    int i;
    for (i = 0; i < n; i++){
        adjacencyMatrix[i] = new int[n];
        adjacencyMatrix[i] = {0};
    }
    for (i = 0; i < m; i++){
        adjacencyMatrix[edges[i].start][edges[i].end] = 1;
        adjacencyMatrix[edges[i].end][edges[i].start] = 1;
    }
    bool hasCliques;
    for (i = 0; i < n; i++) {
        hasCliques = true;
        std::vector<int> aNewClique;
        aNewClique.push_back(i);
        int j = i;
        while (hasCliques) {
            int r = j;
            while (aNewClique.size() < cliqueSize && r < n) {
                if (adjacencyMatrix[i][r] == 1){
                    aNewClique.push_back(r);
                }
                r++;
            }
            if (aNewClique.back() == i){
                hasCliques = false;
            }
            if (r < n && itsAClique(aNewClique, adjacencyMatrix)) {
                for (int p = 0; p < aNewClique.size(); p++) {
                    cliques->push_back(aNewClique[p]);
                }
            }
            j = aNewClique.back();
            aNewClique.pop_back();

        }
    }
    cliques->push_back(-1);

    for (i = 0; i < n; i++){
        delete[] adjacencyMatrix[i];
    }
    delete[] adjacencyMatrix;

    return cliques;
}

bool itsAClique(const std::vector<int> clique, int** adjacencyMatrix){
    for (int i = 0; i < clique.size(); i++){
        for (int j = i; j < clique.size(); j++){
            if (!adjacencyMatrix[i][j]){
                return false;
            }
        }
    }
    return true;
}
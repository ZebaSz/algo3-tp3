#include <iostream>
#include "exact.h"

int exactCMF (int n, int m, const edgeList edges){
    int degree[n] = {0};
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
    int* cliques[n];
    for (i = 0; i < maxDegree; i++){
        cliques[i] = findCliques(i, m, edges); //Agregamos i elementos para cada clique, y un -1 al final
    }
    int answer = 0;
    for (i = 0; i < maxDegree; i++){
        int j = 0;
        int count = 0;
        while (cliques[i][j] != -1){
            if ((j+1) % i == 0){
                if (count > answer){
                    answer = count;
                }
                count = 0;
            } else {
                count = count + degree[cliques[i][j]] - i + 1;
            }
            j++;
        }
    }
    return answer;
}

int* findCliques(int cliqueSize, int m, const edgeList edges){
 //TODO tiene que encontrar todas las cliques de tamaño cliqueSize
}
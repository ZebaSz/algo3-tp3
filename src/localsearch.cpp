#include "localsearch.h"

cliqueInfo localSearchHeuristic(const graphInfo &inputGraph, cliqueInfo partialClique) {
    adjList adjacencyList = createAdjacencyList(inputGraph);
    nodeSet nodes; //TODO Seba asignacion por copia pls
    unsigned int outgoing; //TODO esto es un chikero

    if (partialClique.nodes.size() == 0){
        cliqueInfo aClique(greedyHeuristic(inputGraph, partialClique));
        nodes = aClique.nodes;
        outgoing = aClique.outgoing;
    } else {
        nodes = partialClique.nodes;
        outgoing = partialClique.outgoing;
    }
    cliqueInfo checkClique(nodes, outgoing);
    bool cliquesToCheck = true;
    int counter = 0;
    while (cliquesToCheck){
        counter++;
        std::vector<cliqueInfo> neighborSolutions;
        neighborSolutions.push_back(checkClique);
        for (unsigned int i = 0; i < checkClique.nodes.size(); i++){
            neighborSolutions.push_back(createNeighborSolution(inputGraph, checkClique, adjacencyList, i));
        }
        sortSolutions(neighborSolutions);
        if (neighborSolutions[0].nodes == checkClique.nodes){
            cliquesToCheck = false;
        } else {
            checkClique = neighborSolutions[0];
        }
    }
    return checkClique;
}

cliqueInfo createNeighborSolution(const graphInfo &inputGraph, cliqueInfo partialClique, adjList adjacencyList, unsigned int i){
    unsigned int bestResult = partialClique.outgoing;
    node erasedNode = partialClique.nodes[i];
    node newNode = erasedNode;
    partialClique.outgoing = (unsigned int)(partialClique.outgoing - adjacencyList[partialClique.nodes[i]].size()); //No consideramos el tam de la clique xq despues agregaremos otro nodo
    partialClique.nodes.erase(partialClique.nodes.begin() + i);
    for (unsigned int j = 0; j < inputGraph.n; j++){
        if (j != erasedNode && isClique(adjacencyList, partialClique.nodes, j)){
            unsigned int newOutgoing = (unsigned int)(partialClique.outgoing + adjacencyList[j].size());
            if (bestResult < newOutgoing){
                newNode = j;
            }
        }
    }
    if (newNode != erasedNode){
        partialClique.nodes.push_back(newNode);
        partialClique.outgoing += adjacencyList[newNode].size();
        return greedyHeuristic(inputGraph, partialClique);
    } else {
        partialClique.outgoing = 0; //Pasamos una solución basura
        return partialClique;
    }
}

void sortSolutions(std::vector<cliqueInfo>& neighborSolutions){
    unsigned int i = 0;
    while (i < (neighborSolutions.size() - 1)){
        if (neighborSolutions[i].outgoing < neighborSolutions[i+1].outgoing){
            std::swap(neighborSolutions[i], neighborSolutions[i+1]);
        } else {
            i++;
        }
    }
}

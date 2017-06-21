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
    partialClique.outgoing = (unsigned int)(partialClique.outgoing - adjacencyList[partialClique.nodes[i]].size() - 2 + (partialClique.nodes.size() * 2));
    partialClique.nodes.erase(partialClique.nodes.begin() + i);
    return greedyHeuristic(inputGraph, partialClique);
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

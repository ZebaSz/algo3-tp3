//
// Created by catofthecannals on 21/06/17.
//

#include "grasp.h"

cliqueInfo grasp(const adjList &inputGraph, const float percentageToKeep, const unsigned int iterations) {
    cliqueInfo bestClique(0,0);
    int i = 0;
    while(i < iterations){
        i++;
        cliqueInfo tempClique;  //TODO: aca irian las llamadas a local(randomGreedy())
                                //TODO: dejar de usar listas de incidencia como input y pasar todo a lista de adyacencia
        if(bestClique.outgoing < tempClique. outgoing) bestClique = tempClique;
    }
    return bestClique;
}

cliqueInfo randomGreedy(const adjList &inputGraph, const float percentageToKeep) {
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator (seed);
    nodeSet nodesToConsider;
    cliqueInfo partialClique(0,0);
    unsigned int i = 0;
    while(nodesToConsider.size() < inputGraph.size()){
        nodesToConsider.push_back(i);
        i++;
    }
    sortByDegree(nodesToConsider, inputGraph);
    eraseTail(nodesToConsider, percentageToKeep);
    std::uniform_int_distribution<int> distribution(0, nodesToConsider.size());
    node toAdd = distribution(generator);
    partialClique.nodes.push_back(toAdd);
    partialClique.outgoing += inputGraph[toAdd].size();
    return recurRandomGreedy(inputGraph, partialClique, inputGraph[toAdd], percentageToKeep);
}
cliqueInfo recurRandomGreedy(const adjList &inputGraph, cliqueInfo &partialClique, nodeSet nodesToConsider, const float percentageToKeep){
    if (nodesToConsider.size() == 0) return partialClique; //if nodes can't be added, terminate
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator (seed);
    sortByDegree(nodesToConsider, inputGraph);
    while(inputGraph[nodesToConsider.back()] < partialClique.nodes.size() * 2){ //TODO: asegurarse de que vector.back() devuelve el ultimo elemento
        nodesToConsider.pop_back(); //erase nodes that won't enlarge frontier size
    }
    vector<node>::iterator it = nodesToConsider.begin();
    for ( ; it != nodesToConsider.end(); ) {   //don't consider nodes that wouldn't form a clique
        if (isClique(inputGraph, partialClique, *(it))) {
            ++it;
        } else {
            it = nodesToConsider.erase(it);
        }
    }
    if (nodesToConsider.size() == 0) return partialClique; //if nodes can't be added, terminate

    int amountToConsider = nodes.size() * (1-percentageToKeep);
    std::uniform_int_distribution<int> distribution(0, amountToConsider);
    unsigned int index = distribution(generator);
    node toAdd = nodesToConsider[index];
    it = nodesToConsider.begin();
    nodesToConsider.erase(it + index);
    partialClique.nodes.push_back(toAdd);
    partialClique.outgoing += adjacencyList[toAdd].size() + 2 - partialClique.nodes.size() * 2; //TODO: no estoy seguro sobre esta aritmetica
    return recurRandomGreedy(inputGraph, partialClique, nodesToConsider, percentageToKeep);
}

void eraseTail(nodeSet nodes, const float percentageToKeep) {
    int amountToErase = nodes.size() * (1-percentageToKeep);
    while(amountToErase > 0) {
     nodes.pop_back();
        amountToErase--;
    }
}

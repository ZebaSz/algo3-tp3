//
// Created by catofthecannals on 21/06/17.
//

#include <iostream>
#include "grasp.h"

cliqueInfo grasp(const graphInfo &inputGraph, const float percentageToKeep, const unsigned int iterations) {
    return grasp(Graph::createAdjacencyList(inputGraph), percentageToKeep, iterations);
}

cliqueInfo grasp(const adjList &inputGraph, const float percentageToKeep, const unsigned int iterations) {
    cliqueInfo bestClique(0,0);
    int i = 0;
    while(i < iterations){
        i++;
        cliqueInfo tempClique = localSearchHeuristic(inputGraph, randomGreedy(inputGraph, percentageToKeep));
        if(bestClique.outgoing < tempClique. outgoing) bestClique = tempClique;
    }

    return bestClique;
}

cliqueInfo randomGreedy(const adjList &inputGraph, const float percentageToKeep) {
    nodeSet nodesToConsider;
    cliqueInfo partialClique(0,0);
    for (unsigned int i = 0; i < inputGraph.size(); i++) {
        nodesToConsider.push_back(i);
    }
    Graph::sortByDegree(nodesToConsider, inputGraph);
    unsigned int indexToAdd = randomNode(nodesToConsider, percentageToKeep);
    node toAdd = nodesToConsider[indexToAdd];
    partialClique.nodes.push_back(toAdd);
    partialClique.outgoing += inputGraph[toAdd].size();
    return recurRandomGreedy(inputGraph, partialClique, inputGraph[toAdd], percentageToKeep);
}

cliqueInfo recurRandomGreedy(const adjList &inputGraph, cliqueInfo &partialClique, nodeSet nodesToConsider, const float percentageToKeep){
    if (nodesToConsider.size() == 0) return partialClique; //if nodes can't be added, terminate

    Graph::sortByDegree(nodesToConsider, inputGraph);

    for (auto it = nodesToConsider.begin() ; it != nodesToConsider.end(); ) {   //don't consider nodes that wouldn't form a clique
        if (inputGraph[*it].size() >= partialClique.nodes.size() * 2 && Graph::allAdjacentTo(inputGraph, partialClique.nodes, *it)) {
            ++it;
        } else {
            it = nodesToConsider.erase(it);
        }
    }

    if (nodesToConsider.size() == 0) return partialClique; //if nodes can't be added, terminate

    unsigned int nodeIndexToAdd = randomNode(nodesToConsider, percentageToKeep);
    node toAdd = nodesToConsider[nodeIndexToAdd];
    partialClique.outgoing += inputGraph[toAdd].size() - partialClique.nodes.size() * 2; //TODO: no estoy seguro sobre esta aritmetica
    partialClique.nodes.push_back(toAdd);
    nodesToConsider.erase(nodesToConsider.begin() + nodeIndexToAdd);
    return recurRandomGreedy(inputGraph, partialClique, nodesToConsider, percentageToKeep);
}

node randomNode(const nodeSet &nodes, const float percentageToKeep) {
    unsigned int amountToConsider = (unsigned int) ((nodes.size() - 1) * (percentageToKeep));
    long seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator (seed);
    std::uniform_int_distribution<unsigned int> distribution(0, amountToConsider);
    return distribution(generator);
}

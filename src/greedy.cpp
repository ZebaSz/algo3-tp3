#include <algorithm>
#include "greedy.h"

cliqueInfo greedyHeuristic(const graphInfo &inputGraph){
    return greedyHeuristic(Graph::createAdjacencyList(inputGraph));
}

cliqueInfo greedyHeuristic(const adjList &adjacencyList) {
    // golosamente agregamos la de mayor grado
    cliqueInfo partialClique(0,0);
    node toAdd = Graph::nodeWithMaxDegree(adjacencyList);
    partialClique.nodes.push_back(toAdd);
    partialClique.outgoing = (unsigned int)adjacencyList[toAdd].size();
    return greedyHeuristic(adjacencyList, partialClique);
}

cliqueInfo greedyHeuristic(const graphInfo &inputGraph, cliqueInfo partialClique){
    return greedyHeuristic(Graph::createAdjacencyList(inputGraph), partialClique);
}

cliqueInfo greedyHeuristic(const adjList &adjacencyList, cliqueInfo partialClique) {
    nodeSet nodesToConsider = adjacencyList[partialClique.nodes[0]];
    std::sort(nodesToConsider.begin(), nodesToConsider.end(), greaterDegreeComparator(adjacencyList));
    for (size_t j = 0; j < nodesToConsider.size() ; ++j) {
        //if the node we wanna add is adjacent to every node in the clique and it enlarges the frontier, we add it
        if(Graph::allAdjacentTo(adjacencyList, partialClique.nodes, nodesToConsider[j]) && partialClique.nodes.size() * 2 < adjacencyList[nodesToConsider[j]].size()){

            //update frontier size
            partialClique.outgoing += adjacencyList[nodesToConsider[j]].size() - partialClique.nodes.size() * 2;
            partialClique.nodes.push_back(nodesToConsider[j]);
        }
    }
    return partialClique;
}
#include <algorithm>
#include "greedy.h"

cliqueInfo greedyHeuristic(const graphInfo &inputGraph, cliqueInfo partialClique){
    adjList adjacencyList = Graph::createAdjacencyList(inputGraph);
    if (partialClique.nodes.empty()) {
        node toAdd = Graph::nodeWithMaxDegree(adjacencyList);
        partialClique.nodes.push_back(toAdd);
        partialClique.outgoing += adjacencyList[toAdd].size();
    }
    nodeSet nodesToConsider = adjacencyList[partialClique.nodes[0]];
    std::sort(nodesToConsider.begin(), nodesToConsider.end(), greaterDegreeComparator(adjacencyList));
    for (size_t j = 0; j < nodesToConsider.size() ; ++j) {
        //if the node we wanna add is adjacent to every node in the clique and it enlarges the frontier, we add it
        if(Graph::allAdjacentTo(adjacencyList, partialClique.nodes, nodesToConsider[j]) && partialClique.nodes.size() * 2 < adjacencyList[nodesToConsider[j]].size()){
            partialClique.nodes.push_back(nodesToConsider[j]);
            //update frontier size
            partialClique.outgoing += adjacencyList[nodesToConsider[j]].size() + 2 - partialClique.nodes.size() * 2;
        }
    }
    return partialClique;
}

bool itsClique(const nodeSet subclique, const graphInfo& graph, unsigned int node){ //TODO esta recorriendo todas las aristas todas las veces
    bool ret = true;
    for (int i = 0; i < (int)subclique.size(); i++){
        bool found = false;
        for (int j = 0; j < graph.n; j++){
            edge e = graph.edges[j];
            if((e.start == subclique[i] && e.end == node) || (e.end == subclique[i] && e.start == node)){
                found = true;
            }
        }
        if (!found){
            ret = false;
        }
    }
    return ret;
}

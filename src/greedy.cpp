#include "greedy.h"

cliqueInfo greedyHeuristic(const graphInfo &inputGraph, cliqueInfo partialClique){
    adjList adjacencyList = Graph::createAdjacencyList(inputGraph);
    nodeSet nodesToConsider;
    node root = 0;
    if (partialClique.nodes.size() == 0){ //if starting from scratch, greedily choose the node that has the gratest frontier
        for (unsigned int i = 1; i < adjacencyList.size() ; ++i) {
            if(adjacencyList[root].size() < adjacencyList[i].size()) {
                root = i;
            }
        }
        partialClique.nodes.push_back(root);
        partialClique.outgoing += adjacencyList[root].size();
    } else {
        root = partialClique.nodes[0];  //if we have an input clique, any of its nodes suffices as a root
    }
    nodesToConsider = adjacencyList[root];
    sortByDegree(nodesToConsider, adjacencyList); //we want to first consider greedily adding nodes that will enlarge the clique's frontier
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

void sortByDegree(nodeSet& nodes, adjList& adjacencyList) {
    bool changesMade = true;
    while(changesMade){ //Bubble sort
        changesMade = false;
        for (size_t i = 0; i < nodes.size()-1; ++i) {
            //uses the degrees found in adjacencyList as a criteria to order
            if(adjacencyList[nodes[i]].size() < adjacencyList[nodes[i+1]].size()){
                std::swap(adjacencyList[nodes[i]], adjacencyList[nodes[i+1]]);
                changesMade = true;
            }
        }
    }
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

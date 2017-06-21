//
// Created by catofthecannals on 20/06/17.
//

#include "heuristics.h"

cliqueInfo greedyHeuristic(const graphInfo &inputGraph, cliqueInfo partialClique){
    adjList adjacencyList = createAdjacencyList(inputGraph);
    nodeSet nodesToConsider;
    node root = 0;
    if (partialClique.nodes.size() == 0){ //if starting from scratch, greedily choose the node that has the gratest frontier
        for (int i = 1; i < adjacencyList.size() ; ++i) {
            if(adjacencyList[root].size() < adjacencyList[i].size()) root = i;
        }
    } else {
        root = partialClique.nodes[0]; //if we have an input clique, any of its nodes suffices as a root
    }
    nodesToConsider = adjacencyList[root];
    sortByDegree(nodesToConsider, adjacencyList); //we want to first consider greedily adding nodes that will enlarge the clique's frontier
    for (size_t j = 0; j < nodesToConsider.size() ; ++j) {
        //if the node we wanna add is adjacent to every node in the clique and it enlarges the frontier, we add it
        if(isClique(adjacencyList,partialClique,nodesToConsider[j]) && partialClique.nodes.size() * 2 < adjacencyList[nodesToConsider[j]].size()){
            partialClique.nodes.push_back(nodesToConsider[j]);
            //update frontier size
            partialClique.outgoing += adjacencyList[nodesToConsider[j]].size() - partialClique.nodes.size() * 2;
        }
    }
}

void sortByDegree(nodeSet nodes, const adjList adjacencyList) {
    bool changesMade = true;
    while(changesMade){ //bubble sort! bubbles are kawai :D
        changesMade = false;
        for (size_t i = 0; i < nodes.size()-1; ++i) {
            //uses the degrees found in adjacencyList as a criteria to order
            if(adjacencyList[nodes[i]].size() < adjacencyList[nodes[i+1]].size()){
                std::swap(adjacencyList[nodes[i]].size(), adjacencyList[nodes[i+1]].size());
                changesMade = true;
            }
        }
    }
}

bool isClique(const adjList& graph, const nodeSet& subclique, unsigned int node) {
    for (size_t i = 0; i < subclique.size(); i++){ //for every node in the clique
        bool found = false;
        for (size_t j = 0; j < graph[i].size(); ++j) { //check whether or not it is adjacent to the new node
            if(graph[i][j] == node) found = true;
        }
        if(!found) return false;
    }
    return true;
}

adjList createAdjacencyList(const graphInfo &input) {
    adjList adjacencyList;
    for (int i = 0; i < input.n; ++i) { // n nodes
        std::vector<node> v;
        adjacencyList.push_back(v);
    }
    for (int j = 0; j < input.edges.size(); ++j) { //add connections
        edge e = input.edges[j];
        adjacencyList[e.start].push_back(e.end);
        adjacencyList[e.end].push_back(e.start);
    }
}

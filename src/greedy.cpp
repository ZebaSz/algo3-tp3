#include "greedy.h"

cliqueInfo greedyHeuristic(const graphInfo &inputGraph, cliqueInfo partialClique){
    adjList adjacencyList = createAdjacencyList(inputGraph);
    nodeSet nodesToConsider;
    node root = 0;
    if (partialClique.nodes.size() == 0){ //if starting from scratch, greedily choose the node that has the gratest frontier
        for (unsigned int i = 1; i < adjacencyList.size() ; ++i) {
            if(adjacencyList[root].size() < adjacencyList[i].size()) {
                root = i;
            }
        }
    } else {
        root = partialClique.nodes[0]; //if we have an input clique, any of its nodes suffices as a root
    }
    nodesToConsider = adjacencyList[root];
    sortByDegree(nodesToConsider, adjacencyList); //we want to first consider greedily adding nodes that will enlarge the clique's frontier
    for (int j = 0; j < (int)nodesToConsider.size() ; ++j) {
        //if the node we wanna add is adjacent to every node in the clique and it enlarges the frontier, we add it
        if(isClique(adjacencyList, partialClique.nodes, nodesToConsider[j]) && partialClique.nodes.size() * 2 < adjacencyList[nodesToConsider[j]].size()){
            partialClique.nodes.push_back(nodesToConsider[j]);
            //update frontier size
            partialClique.outgoing += adjacencyList[nodesToConsider[j]].size() - partialClique.nodes.size() * 2;
        }
    }
    return partialClique;
}

void sortByDegree(nodeSet nodes, adjList adjacencyList) {
    bool changesMade = true;
    while(changesMade){ //bubble sort! bubbles are kawai :D
        changesMade = false;
        for (int i = 0; i < nodes.size()-1; ++i) {
            //uses the degrees found in adjacencyList as a criteria to order
            if(adjacencyList[nodes[i]].size() < adjacencyList[nodes[i+1]].size()){
                std::swap(adjacencyList[nodes[i]], adjacencyList[nodes[i+1]]);
                changesMade = true;
            }
        }
    }
}

bool isClique(const adjList& graph, const nodeSet& subclique, unsigned int node) {
    for (int i = 0; i < (int)subclique.size(); i++){ //for every node in the clique
        bool found = false;
        for (int j = 0; j < (int)graph[i].size(); ++j) { //check whether or not it is adjacent to the new node
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
    return adjacencyList;
}

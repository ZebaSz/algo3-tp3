#include <algorithm>
#include <iostream>
#include "localsearch.h"

cliqueInfo localSearchHeuristic(const graphInfo &inputGraph) {
    return localSearchHeuristic(Graph::createAdjacencyList(inputGraph));
}

cliqueInfo localSearchHeuristic(const adjList &adjacencyList) {
    return localSearchHeuristic(adjacencyList, greedyHeuristic(adjacencyList));
}

cliqueInfo localSearchHeuristic(const adjList &adjacencyList, cliqueInfo partialClique) {
    bool isBetter = true;
    while (isBetter) {
        isBetter = false;
        cliqueInfo sol = findBestNeighborSolution(adjacencyList, partialClique);
        if (partialClique.outgoing < sol.outgoing) { //podriamos ver que pasa si no mejora pero queda igual
            isBetter = true;
            partialClique = sol;
        }
    }

    return partialClique;
}

cliqueInfo findBestNeighborSolution(const adjList &adjacencyList, cliqueInfo partialClique) {
    cliqueInfo add = localAdd(adjacencyList, partialClique);
    cliqueInfo remove = localRemove(adjacencyList, partialClique);
    cliqueInfo swap = localSwap(adjacencyList, partialClique);
    if (add.outgoing >= remove.outgoing && add.outgoing >= swap.outgoing) {
        return add;
    } else if (remove.outgoing >= add.outgoing && remove.outgoing >= swap.outgoing) {
        return remove;
    } else {
        return swap;
    }
}

cliqueInfo localAdd(const adjList &adjacencyList, cliqueInfo partialClique) {
    nodeSet nodesToConsider = adjacencyList[partialClique.nodes[0]];
    std::sort(nodesToConsider.begin(), nodesToConsider.end(), greaterDegreeComparator(adjacencyList));
    for (auto it = nodesToConsider.begin(); it != nodesToConsider.end(); ) {
        if (Graph::allAdjacentTo(adjacencyList, partialClique.nodes, *it)) {
            partialClique.nodes.push_back(*it);
            partialClique.outgoing += adjacencyList[*it].size() + 2 - partialClique.nodes.size() * 2;
            break;
        } else {
            ++it;
        }
    }
    return greedyHeuristic(adjacencyList, partialClique);
}

cliqueInfo localRemove(const adjList &adjacencyList, cliqueInfo partialClique) {
    auto toRemove = partialClique.nodes.begin();
    int bestStatus = 0; //Solo tomaremos una solucion si al quitar un nodo mejora
    for (auto it = partialClique.nodes.begin(); it != partialClique.nodes.end(); ++it) {
        int status = 2 * ((int) partialClique.nodes.size() - 1) - (int) adjacencyList[*it].size();
        if (status > bestStatus) {
            bestStatus = status;
            toRemove = it;
        }
    }

    if (bestStatus > 0) {
        partialClique.nodes.erase(toRemove);
        partialClique.outgoing = partialClique.outgoing + (unsigned int) bestStatus;
    }

    return greedyHeuristic(adjacencyList, partialClique);
}

cliqueInfo localSwap(const adjList &adjacencyList, cliqueInfo partialClique) {
    std::vector<node>::iterator toRemove;
    node toAdd;
    unsigned int best = 0;

    nodeSet toConsider;
    /*for (node n = 0; n < adjacencyList.size(); n++) {
        if(std::find(partialClique.nodes.begin(), partialClique.nodes.end(), n) == partialClique.nodes.end()) {
            toConsider.push_back(n);
        }
    }*/ //Si lo definimos así, la complejidad del for es O(N)
    for (size_t i = 0; i < partialClique.nodes.size(); i++){
        if (i == 0){ // toConsider lo definimos en base al nodo que sacamos, para reducir la complejidad
                    // Si lo definimos así, la complejidad del for es O(min(n,m))
            if (partialClique.nodes.size() > 1) {
                toConsider = adjacencyList[partialClique.nodes[i + 1]];
            }
        } else {
            toConsider = adjacencyList[partialClique.nodes[i - 1]];
        }
        for (auto ot = toConsider.begin(); ot != toConsider.end(); ++ot) {
            cliqueInfo testClique = partialClique;
            testClique.nodes.erase(testClique.nodes.begin() + i);
            if (Graph::allAdjacentTo(adjacencyList, testClique.nodes, *ot)){
                testClique.nodes.push_back(*ot);
                testClique.outgoing = 0;
                for (size_t j = 0; j < testClique.nodes.size(); j++){
                    testClique.outgoing += (unsigned int) (adjacencyList[testClique.nodes[j]].size() + 1 - testClique.nodes.size());
                }
                testClique = greedyHeuristic(adjacencyList, testClique);
                if (testClique.outgoing > best){
                    best = testClique.outgoing;
                    toRemove = partialClique.nodes.begin() + i;
                    toAdd = *ot;
                }
            }
        }
    }
    if (best > 0) {
        partialClique.outgoing = (unsigned int)(partialClique.outgoing - adjacencyList[*toRemove].size()  + adjacencyList[toAdd].size());
        partialClique.nodes.erase(toRemove);
        partialClique.nodes.push_back(toAdd);
    }
    return greedyHeuristic(adjacencyList, partialClique);
}

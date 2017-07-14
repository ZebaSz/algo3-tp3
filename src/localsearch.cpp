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

cliqueInfo localSwap2(const adjList &adjacencyList, cliqueInfo partialClique) { // TODO dejo la implementacion pero si no la usamos volemosla
    node toRemove1, toRemove2, toAdd1, toAdd2;
    bool changes = false;
    unsigned int best = 0;

    //if (partialClique.nodes.size() > 2) { //SE PUEDE MEJORAR PARA CASOS DE >= 2
        for (node r1 = 0; r1 < partialClique.nodes.size() - 1; r1++) {
            for (node r2 = r1 + 1; r2 < partialClique.nodes.size() - 1; r2++) {
                // stillInside es un nodo que sigue estando en la clique si sacamos r1 y r2, va a hacer el primero el segundo o el tercero (dependiendo si r1 o r2 son los primeros)
                node stillInside = 0;
                if (r1 == 0) {
                    stillInside = (r2 == 1) ? 2 : 1;
                }

                //Si el nodo que sigue dentro de la clique tiene al menos 2 mas nodos adyacentes que los de la clique
                //if (adjacencyList[partialClique.nodes[stillInside]].size() > partialClique.nodes.size() + 1) {
                for (node a1 = 0; a1 < adjacencyList[partialClique.nodes[stillInside]].size(); a1++){
                    for (node a2 = a1; a1 < adjacencyList[partialClique.nodes[stillInside]].size(); a1++) {
                        cliqueInfo testClique = partialClique;
                        testClique.nodes.erase(testClique.nodes.begin() + r2);
                        testClique.nodes.erase(testClique.nodes.begin() + r1);
                        if (Graph::isAdjacentTo(adjacencyList, a1, a2) &&
                            Graph::allAdjacentTo(adjacencyList, testClique.nodes, a1) &&
                            Graph::allAdjacentTo(adjacencyList, testClique.nodes, a2)){
                            testClique.nodes.push_back(a1);
                            testClique.nodes.push_back(a2);
                            testClique.outgoing = 0;
                            for (size_t i = 0; i < testClique.nodes.size(); i++){
                                testClique.outgoing += (unsigned int) (adjacencyList[testClique.nodes[i]].size() + 1 - testClique.nodes.size());
                            }
                            testClique = greedyHeuristic(adjacencyList, testClique);
                            if ((!changes || testClique.outgoing > best)){
                                toRemove1 = r1;
                                toRemove2 = r2;
                                toAdd1 = a1;
                                toAdd2 = a2;
                                changes = true;
                                best = testClique.outgoing;
                            }
                        }
                    }
                }
            }
        }
    //}
    if (changes) { //TODO creo que este if esta al pedo
        partialClique.nodes.erase(partialClique.nodes.begin() + toRemove2);
        partialClique.nodes.erase(partialClique.nodes.begin() + toRemove1);
        partialClique.nodes.push_back(toAdd1);
        partialClique.nodes.push_back(toAdd2);
        partialClique.outgoing = 0;
        for (size_t i = 0; i < partialClique.nodes.size(); i++){
            partialClique.outgoing = (unsigned int) (partialClique.outgoing + adjacencyList[partialClique.nodes[i]].size() + 1 - partialClique.nodes.size());
        }
    }

    return greedyHeuristic(adjacencyList, partialClique);
}

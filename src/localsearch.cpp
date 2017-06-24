#include <algorithm>
#include "localsearch.h"

cliqueInfo laDeRoniPorLasDudas(const graphInfo &inputGraph, cliqueInfo partialClique) {
    adjList adjacencyList = Graph::createAdjacencyList(inputGraph);
    if (partialClique.nodes.empty()) {
        partialClique = greedyHeuristic(adjacencyList, partialClique);
    }
    bool cliquesToCheck = true;
    while (cliquesToCheck) {
        cliquesToCheck = false;
        cliqueInfo betterSolution = partialClique;
        for (node j = 0; j < partialClique.nodes.size(); j++) {
            for (node i = (j + 1); i < partialClique.nodes.size(); i++) {
                cliqueInfo sol = createNeighborSolution(inputGraph, partialClique, adjacencyList, i, j);
                if (betterSolution.outgoing < sol.outgoing) {
                    cliquesToCheck = true;
                    betterSolution = sol;
                }
            }
        }
        partialClique = betterSolution;
    }
    return partialClique;
}

cliqueInfo localSearchHeuristic(const graphInfo &inputGraph, cliqueInfo partialClique) {
    adjList adjacencyList = Graph::createAdjacencyList(inputGraph);
    if (partialClique.nodes.empty()) {
        partialClique = greedyHeuristic(adjacencyList, partialClique);
    }
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
    int bestStatus = 0;
    for (auto it = partialClique.nodes.begin(); it != partialClique.nodes.end(); ++it) {
        int status = 2 * ((int) partialClique.nodes.size() - 1) - (int) adjacencyList[*it].size();
        if (status > bestStatus) {
            bestStatus = status;
            toRemove = it;
        }
    }

    if (bestStatus != 0) {
        partialClique.nodes.erase(toRemove);
        partialClique.outgoing = partialClique.outgoing + (unsigned int) bestStatus;
    }

    return greedyHeuristic(adjacencyList, partialClique);
}

cliqueInfo localSwap(const adjList &adjacencyList, cliqueInfo partialClique) {
    std::vector<node>::iterator toRemove;
    node toAdd;
    int best = 0;

    nodeSet toConsider;
    for (node n = 0; n < adjacencyList.size(); n++) {
        if(std::find(partialClique.nodes.begin(), partialClique.nodes.end(), n) == partialClique.nodes.end()) {
            toConsider.push_back(n);
        }
    }

    for (auto it = partialClique.nodes.begin(); it != partialClique.nodes.end(); ++it) {
        for (auto ot = toConsider.begin(); ot != toConsider.end(); ++ot) {
            int status = (int) adjacencyList[*ot].size() - (int) adjacencyList[*it].size();
            if (status > best && Graph::allAdjacentToExceptFor(adjacencyList, partialClique.nodes, *ot, *it)) {
                best = status;
                toRemove = it;
                toAdd = *ot;
            }
        }
    }
    if (best > 0) {
        partialClique.nodes.erase(toRemove);
        partialClique.nodes.push_back(toAdd);
    }
    return greedyHeuristic(adjacencyList, partialClique);
}

/*void swap(const adjList &adjacencyList, cliqueInfo &partialClique, std::vector<node>::iterator &toRemove, std::vector<node>::iterator &toAdd) {
    node nodeToRemove = *toRemove;
    node nodeToAdd = *toAdd;
    partialClique.insideNodes.erase(toRemove);
    partialClique.outsideNodes.erase(toAdd);
    partialClique.insideNodes.push_back(nodeToAdd);
    partialClique.outsideNodes.push_back(nodeToRemove);
}*/











cliqueInfo createNeighborSolution(const graphInfo &inputGraph, cliqueInfo partialClique, const adjList &adjacencyList,
                                  node i, node j){
    node bestResult = partialClique.outgoing;
    node firstErasedNode = partialClique.nodes[i];
    node secErasedNode = partialClique.nodes[j];
    node firstNewNode = firstErasedNode;
    node secNewNode = secErasedNode;
    partialClique.outgoing = 0; //Reiniciamos el contador de fronteras de la clique
    partialClique.nodes.erase(partialClique.nodes.begin() + j);
    partialClique.nodes.erase(partialClique.nodes.begin() + i - 1); //Ya sacamos un nodo, con j < i, asi que i se atrasó uno
    for (unsigned int y = 0; y < partialClique.nodes.size(); y++){
        partialClique.outgoing += (adjacencyList[partialClique.nodes[y]].size() - y);
    }
    partialClique.outgoing = (unsigned int)(partialClique.outgoing - partialClique.nodes.size());
    for (unsigned int v = 0; v < inputGraph.n; v++) {
        for (unsigned int w = (v + 1); w < inputGraph.n; w++) {
            if (((v != firstErasedNode && v != secErasedNode) || (w != firstErasedNode && w != secErasedNode)) &&
                isCliqueWithVariousNodes(inputGraph, partialClique.nodes, v, w)) {
                unsigned int newOutgoing = (unsigned int) (partialClique.outgoing + adjacencyList[v].size() +
                                                           adjacencyList[w].size() - (partialClique.nodes.size() * 3) - 3);
                cliqueInfo aClique(partialClique.nodes, newOutgoing);
                aClique.nodes.push_back(v);
                aClique.nodes.push_back(w);
                if (bestResult < greedyHeuristic(inputGraph, aClique).outgoing) {
                    bestResult = newOutgoing;
                    firstNewNode = v;
                    secNewNode = w;
                }
            }
        }
    }
    if ((firstNewNode != firstErasedNode) || (secNewNode != secErasedNode)) {
        partialClique.nodes.push_back(firstNewNode);
        partialClique.nodes.push_back(secNewNode);
        partialClique.outgoing = bestResult;
        return greedyHeuristic(inputGraph, partialClique);
    } else {
        partialClique.outgoing = 0; //Pasamos una solución basura
        return partialClique;
    }
}

bool isCliqueWithVariousNodes(const graphInfo &graph, const nodeSet& subclique, unsigned int v , unsigned int w){ //TODO esta recorriendo todas las aristas todas las veces
    if (itsClique(subclique, graph, v) && itsClique(subclique, graph, w)){
        for (unsigned int i = 0; i < graph.n; i++){
            edge e = graph.edges[i];
            if((e.start == v && e.end == w) || (e.end == v && e.start == w)){
                return true;
            }
        }
    }
    return false;
}



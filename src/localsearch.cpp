#include <algorithm>
#include "localsearch.h"

cliqueInfo localSearchHeuristic(const graphInfo &inputGraph, cliqueInfo partialClique) {
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

fullCliqueInfo localSearchHeuristic2(const graphInfo &inputGraph, fullCliqueInfo partialClique) {
    adjList adjacencyList = Graph::createAdjacencyList(inputGraph);

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


cliqueInfo findBestNeighborSolution(const adjList &adjacencyList, fullCliqueInfo partialClique) {
    fullCliqueInfo localAdd = localAdd(adjacencyList, partialClique);
    fullCliqueInfo localRemove = localRemove(adjacencyList, partialClique);
    //return min;
    return cliqueInfo(0, 0);
}

fullCliqueInfo localAdd(const adjList &adjacencyList, fullCliqueInfo partialClique) {
    std::sort(partialClique.outsideNodes.begin(), partialClique.outsideNodes.end(), greaterDegreeComparator(adjacencyList));
    for (auto it = partialClique.outsideNodes.begin(); it != partialClique.outsideNodes.end(); ) {
        if (Graph::allAdjacentTo(adjacencyList, partialClique.insideNodes, *it)) {
            partialClique.insideNodes.push_back(*it);
            partialClique.outgoing += adjacencyList[*it].size() + 2 - partialClique.insideNodes.size() * 2;
            partialClique.outsideNodes.erase(it);
            break;
        } else {
            ++it;
        }
    }
    return partialClique;
}

fullCliqueInfo localRemove(const adjList &adjacencyList, fullCliqueInfo partialClique) {
    auto toRemove = partialClique.insideNodes.begin();
    int bestStatus = 0;
    for (auto it = partialClique.insideNodes.begin(); it != partialClique.insideNodes.end(); ) {
        int status = 2 * ((int) partialClique.insideNodes.size() - 1) - (int) adjacencyList[*it].size();
        if (status > bestStatus) {
            bestStatus = status;
            toRemove = it;
        }
    }

    if (bestStatus != 0) {
        partialClique.outsideNodes.push_back(*toRemove);
        partialClique.insideNodes.erase(toRemove);
        partialClique.outgoing = partialClique.outgoing + (unsigned int) bestStatus;
    }

    return partialClique;
}












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
        for (int i = 0; i < graph.n; i++){
            edge e = graph.edges[i];
            if((e.start == v && e.end == w) || (e.end == v && e.start == w)){
                return true;
            }
        }
    }
    return false;
}



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
                if (betterSolution.outgoing <= sol.outgoing) {
                    cliquesToCheck = true;
                    betterSolution = sol;
                }
            }
        }
        partialClique = betterSolution;
    }
    return partialClique;
}

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
    cliqueInfo swap2 = localSwap2(adjacencyList, partialClique);

    if (add.outgoing >= remove.outgoing && add.outgoing >= swap.outgoing && add.outgoing >= swap2.outgoing) {
        return add;
    } else if (remove.outgoing >= add.outgoing && remove.outgoing >= swap.outgoing && remove.outgoing >= swap2.outgoing) {
        return remove;
    } else if (swap.outgoing >= add.outgoing && swap.outgoing >= remove.outgoing && swap.outgoing >= swap2.outgoing) {
        return swap;
    } else {
        return swap2;
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

cliqueInfo localSwap2(const adjList &adjacencyList, cliqueInfo partialClique) {
    node toRemove1, toRemove2, toAdd1, toAdd2;
    int best = 0;

    if (partialClique.nodes.size() > 2) { //SE PUEDE MEJORAR PARA CASOS DE >= 2
        for (node r1 = 0; r1 < partialClique.nodes.size() - 1; r1++) {
            for (node r2 = r1; r2 < partialClique.nodes.size(); r2++) {
                // stillInside es un nodo que sigue estando en la clique si sacamos r1 y r2, va a hacer el primero el segundo o el tercero (dependiendo si r1 o r2 son los primeros)
                node stillInside = 0;
                if (r1 == 0) {
                    stillInside = (r2 == 1) ? 2 : 1;
                }

                //Si el nodo que sigue dentro de la clique tiene al menos 2 mas nodos adyacentes que los de la clique
                if (adjacencyList[stillInside].size() > partialClique.nodes.size() + 1) {
                    for (auto a1 = adjacencyList[stillInside].begin(); a1 != adjacencyList[stillInside].end(); ++a1) {
                        for (auto a2 = a1; a2 != adjacencyList[stillInside].end(); ++a2) {
                            int status = (int) adjacencyList[*a1].size() + (int) adjacencyList[*a2].size() -  (int) adjacencyList[r1].size() - (int) adjacencyList[r2].size();
                            if (status > best && Graph::isAdjacentTo(adjacencyList, *a1, *a2) &&
                                    Graph::allAdjacentToExceptForDouble(adjacencyList, partialClique.nodes, *a1, *a2, r1, r2) ) {
                                toRemove1 = r1;
                                toRemove2 = r2;
                                toAdd1 = *a1;
                                toAdd2 = *a2;
                            }
                        }
                    }
                }
            }
        }
    }

    if (best > 0) {
        partialClique.nodes.erase(std::remove(partialClique.nodes.begin(), partialClique.nodes.end(), toRemove1), partialClique.nodes.end());
        partialClique.nodes.erase(std::remove(partialClique.nodes.begin(), partialClique.nodes.end(), toRemove2), partialClique.nodes.end());
        partialClique.nodes.push_back(toAdd1);
        partialClique.nodes.push_back(toAdd2);

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
        for (unsigned int i = 0; i < graph.n; i++){
            edge e = graph.edges[i];
            if((e.start == v && e.end == w) || (e.end == v && e.start == w)){
                return true;
            }
        }
    }
    return false;
}



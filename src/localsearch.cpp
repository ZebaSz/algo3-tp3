#include "localsearch.h"

cliqueInfo localSearchHeuristic(const graphInfo &inputGraph, cliqueInfo partialClique) {
    adjList adjacencyList = createAdjacencyList(inputGraph);
    nodeSet nodes; //TODO Seba asignacion por copia pls
    unsigned int outgoing; //TODO esto es un chikero

    if (partialClique.nodes.size() == 0){
        cliqueInfo aClique(greedyHeuristic(inputGraph, partialClique));
        nodes = aClique.nodes;
        outgoing = aClique.outgoing;
    } else {
        nodes = partialClique.nodes;
        outgoing = partialClique.outgoing;
    }
    cliqueInfo checkClique(nodes, outgoing);
    bool cliquesToCheck = true;
    while (cliquesToCheck){
        std::vector<cliqueInfo> neighborSolutions;
        neighborSolutions.push_back(checkClique);
        for (unsigned int j = 0; j < checkClique.nodes.size(); j++) {
            for (unsigned int i = (j + 1); i < checkClique.nodes.size(); i++) {
                neighborSolutions.push_back(createNeighborSolution(inputGraph, checkClique, adjacencyList, i, j));
            }
        }
        sortSolutions(neighborSolutions);
        for (int i = 0; i < neighborSolutions.size(); i++){
            Utils::log(INFO, "Solucion numero %d", i);
            Utils::log(INFO, " %d \n", neighborSolutions[i].outgoing);
        }
        if (neighborSolutions[0].nodes == checkClique.nodes){
            cliquesToCheck = false;
        } else {
            checkClique = neighborSolutions[0];
        }
    }
    return checkClique;
}

cliqueInfo createNeighborSolution(const graphInfo &inputGraph, cliqueInfo partialClique, adjList adjacencyList,
                                  unsigned int i, unsigned int j){
    unsigned int bestResult = partialClique.outgoing;
    node firstErasedNode = partialClique.nodes[i];
    node secErasedNode = partialClique.nodes[j];
    node firstNewNode = firstErasedNode;
    node secNewNode = secErasedNode;
    partialClique.outgoing = 0; //No consideramos el tam de la clique xq despues agregaremos otros nodos
    partialClique.nodes.erase(partialClique.nodes.begin() + j);
    partialClique.nodes.erase(partialClique.nodes.begin() + i - 1); //Ya sacamos un nodo, con j < i, asi que i se atrasó uno
    for (unsigned int y = 0; y < partialClique.nodes.size(); y++){
        partialClique.outgoing += (adjacencyList[partialClique.nodes[y]].size() - y);
    }
    partialClique.outgoing = (unsigned int)(partialClique.outgoing - partialClique.nodes.size());
    for (unsigned int v = 0; v < inputGraph.n; v++) {
        for (unsigned int w = (v + 1); w < inputGraph.n; w++) {
            if (((v != firstErasedNode && v != secErasedNode) || (w != firstErasedNode && w != secErasedNode)) &&
                isCliqueWithVariousNodes(adjacencyList, partialClique.nodes, v, w)) {
                unsigned int newOutgoing = (unsigned int) (partialClique.outgoing + adjacencyList[v].size() +
                                                           adjacencyList[w].size() - (partialClique.nodes.size() * 3) - 3);
                if (bestResult < newOutgoing) {
                    firstNewNode = v;
                    secNewNode = w;
                }
            }
        }
    }
    if ((firstNewNode != firstErasedNode) || (secNewNode != secErasedNode)) {
        Utils::log(INFO, "outgoing a %d", partialClique.outgoing);
        partialClique.nodes.push_back(firstNewNode); //TODO si pusheas primero el secNode, cambian los valores (!!!)
        partialClique.nodes.push_back(secNewNode);
        Utils::log(INFO, "outgoing b %d", partialClique.outgoing);
        partialClique.outgoing += adjacencyList[firstNewNode].size() + adjacencyList[secNewNode].size();
        Utils::log(INFO, "Solucion con %d y %d, nos da %d", firstNewNode, secNewNode, partialClique.outgoing); //TODO Aca ya se rompio
        Utils::log(INFO, "porque %d y %d", adjacencyList[firstNewNode].size(), adjacencyList[secNewNode].size());
        return greedyHeuristic(inputGraph, partialClique);
    } else {
        partialClique.outgoing = 0; //Pasamos una solución basura
        return partialClique;
    }
}

bool isCliqueWithVariousNodes(const adjList &graph, const nodeSet& subclique, unsigned int v , unsigned int w){
    if (isClique(graph, subclique, v) && isClique(graph, subclique, w)){
        for (int i = 0; i < (int)graph[v].size(); i++){
            if (graph[v][i] == w){
                return true;
            }
        }
    }
    return false;
}

void sortSolutions(std::vector<cliqueInfo>& neighborSolutions){
    for (unsigned int i = 0; i < neighborSolutions.size(); i++){
        for (unsigned int j = i + 1; j < neighborSolutions.size(); j++){
            while (j > 0 && neighborSolutions[j].outgoing > neighborSolutions[j-1].outgoing){
                std::swap(neighborSolutions[j], neighborSolutions[j-1]);
                j--;
            }
        }
    }
}


#include "localsearch.h"

cliqueInfo localSearchHeuristic(const graphInfo &inputGraph, cliqueInfo partialClique) {
    adjList adjacencyList = Graph::createAdjacencyList(inputGraph);
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


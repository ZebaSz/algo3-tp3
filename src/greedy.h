#ifndef ALGO3_TP3_GREEDY_H
#define ALGO3_TP3_GREEDY_H

#include "graph.h"
#include "clique.h"
#include "Utils.h"


cliqueInfo greedyHeuristic(const graphInfo &inputGraph);

cliqueInfo greedyHeuristic(const adjList &graph);
/**
 * greedily adds nodes to a clique if and only if adding a node yields a clique with a greater frontier
 * @param inputGraph
 * @param partialClique can be used to start the algorithm from any given clique
 * @return
 */
cliqueInfo greedyHeuristic(const graphInfo &inputGraph, cliqueInfo partialClique);

cliqueInfo greedyHeuristic(const adjList &graph, cliqueInfo partialClique);

#endif //ALGO3_TP3_GREEDY_H

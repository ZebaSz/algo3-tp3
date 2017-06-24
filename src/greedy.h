#ifndef ALGO3_TP3_GREEDY_H
#define ALGO3_TP3_GREEDY_H

#include "graph.h"
#include "clique.h"
#include "Utils.h"

/**
 * greedily adds nodes to a clique if and only if adding a node yields a clique with a greater frontier
 * @param inputGraph
 * @param partialClique can be used to start the algorithm from any given clique
 * @return
 */
cliqueInfo greedyHeuristic(const graphInfo &inputGraph, cliqueInfo partialClique);

cliqueInfo greedyHeuristic(const adjList &graph, cliqueInfo partialClique);


/**
 *
 * @param graph
 * @param subclique we want to expand
 * @param node we want to know if we can add
 * @return true if and only if node is adjacent to every node in subclique
 */
bool itsClique(const nodeSet subclique, const graphInfo& graph, unsigned int node);

#endif //ALGO3_TP3_GREEDY_H

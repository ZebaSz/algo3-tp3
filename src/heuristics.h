//
// Created by catofthecannals on 20/06/17.
//

#ifndef ALGO3_TP3_HEURISTICS_H
#define ALGO3_TP3_HEURISTICS_H

#include "graph.h"
#include "clique.h"
#include "exact.h"

/**
 * greedily adds nodes to a clique if and only if adding a node yields a clique with a greater frontier
 * @param inputGraph
 * @param partialClique can be used to start the algorithm from any given clique
 * @return
 */
cliqueInfo greedyHeuristic(const graphInfo &inputGraph, cliqueInfo partialClique);

/**
 * Creates an adjacency list
 * @param input incidence list
 * @return
 */
adjList createAdjacencyList(const graphInfo &input);

/**
 *
 * @param graph
 * @param subclique we want to expand
 * @param node we want to know if we can add
 * @return true if and only if node is adjacent to every node in subclique
 */
bool isClique(const adjList& graph, const nodeSet& subclique, unsigned int node);

/**
 *
 * @param nodes vector of nodes that will be ordered from higher to lower degree
 * @param adjacencyList this adjacency list will let us know the degree of every node
 */
void sortByDegree(nodeSet nodes, const adjList adjacencyList);
#endif //ALGO3_TP3_HEURISTICS_H

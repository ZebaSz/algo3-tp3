#ifndef ALGO3_TP3_LOCALSEARCH_H
#define ALGO3_TP3_LOCALSEARCH_H

#include "graph.h"
#include "clique.h"
#include "Utils.h"
#include "greedy.h" //TODO hay que hacer un .h que tome todas las funciones generales

/**
 * greedily adds nodes to a clique if and only if adding a node yields a clique with a greater frontier
 * @param inputGraph
 * @param partialClique can be used to start the algorithm from any given clique
 * @return
 */
cliqueInfo localSearchHeuristic(const graphInfo &inputGraph, cliqueInfo partialClique);

cliqueInfo createNeighborSolution(const graphInfo &inputGraph, cliqueInfo partialClique, adjList adjacencyList,
                                  unsigned int i, unsigned int j);

void sortSolutions(std::vector<cliqueInfo>& neighborSolutions);

bool isCliqueWithVariousNodes(const graphInfo &graph, const nodeSet& subclique, unsigned int v , unsigned int w);

#endif //ALGO3_TP3_LOCALSEARCH_H

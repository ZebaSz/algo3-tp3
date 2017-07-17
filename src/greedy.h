#ifndef ALGO3_TP3_GREEDY_H
#define ALGO3_TP3_GREEDY_H

#include "graph.h"
#include "clique.h"
#include "Utils.h"


cliqueInfo greedyHeuristic(const graphInfo &inputGraph);

cliqueInfo greedyHeuristic(const adjList &graph);

cliqueInfo greedyHeuristic(const adjList &graph, cliqueInfo partialClique);

#endif //ALGO3_TP3_GREEDY_H

//
// Created by catofthecannals on 21/06/17.
//

#ifndef ALGO3_TP3_GRASP_H
#define ALGO3_TP3_GRASP_H

#include "greedy.h"
#include "localsearch.h"
#include <random>
#include <chrono>

cliqueInfo grasp(const adjList &inputGraph, const float percentageToKeep, const unsigned int iterations);

cliqueInfo randomGreedy(const adjList &inputGraph, const float percentageToKeep);

cliqueInfo recurRandomGreedy(const adjList &inputGraph, cliqueInfo &partialClique, nodeSet nodesToConsider, const float percentageToKeep);

void eraseTail(nodeSet nodes, const float percentageToKeep);

#endif //ALGO3_TP3_GRASP_H

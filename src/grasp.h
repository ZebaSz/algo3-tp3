//
// Created by catofthecannals on 21/06/17.
//

#ifndef ALGO3_TP3_GRASP_H
#define ALGO3_TP3_GRASP_H

#include"greedy.h"
#include "localsearch.h"
#include <random>
#include <chrono>

typedef std::chrono::high_resolution_clock Time;
typedef std::chrono::microseconds ms;
typedef std::chrono::duration<float> fsec;

cliqueInfo grasp(const graphInfo &inputGraph, const float percentageToKeep, const unsigned int iterations, float inputTime);

cliqueInfo grasp(const adjList &inputGraph, const float percentageToKeep, const unsigned int iterations, float inputTime);

cliqueInfo randomGreedy(const adjList &inputGraph, const float percentageToKeep);

cliqueInfo recurRandomGreedy(const adjList &inputGraph, cliqueInfo &partialClique, nodeSet nodesToConsider, const float percentageToKeep);

node randomNode(const nodeSet &nodes, const float percentageToKeep);


#endif //ALGO3_TP3_GRASP_H

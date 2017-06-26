#include <iostream>
#include "Utils.h"
#include "greedy.h"

int main() {
    graphInfo graph(Utils::parseGraph(std::cin));
    Utils::printClique(greedyHeuristic(graph));
    return 0;
}
#include <iostream>
#include "Utils.h"
#include "localsearch.h"

int main() {
    graphInfo graph(Utils::parseGraph(std::cin));
    Utils::printClique(localSearchHeuristic(graph));
    return 0;
}
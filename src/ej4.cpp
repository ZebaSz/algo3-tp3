#include <iostream>
#include "Utils.h"
#include "grasp.h"

#define P 0.6
#define IT 50
#define T mus{1000}

int main() {
    graphInfo graph(Utils::parseGraph(std::cin));
    Utils::printClique(grasp(graph, P, IT, T));
    return 0;
}
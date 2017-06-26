#include <iostream>
#include "exact.h"
#include "Utils.h"

int main() {
    graphInfo graph(Utils::parseGraph(std::cin));
    Utils::printClique(exactCMF(graph));
    return 0;
}
#include <iostream>
#include "exact.h"
#include "Utils.h"

int main() {
    graphInfo graph(Utils::parseGraph(std::cin));
    cliqueInfo clique = exactCMF(graph);
    printf("%u %lu", clique.outgoing, clique.nodes.size());
    for(size_t i = 0; i < clique.nodes.size(); ++i) {
        printf(" %u", clique.nodes[i] + 1);
    }
    return 0;
}
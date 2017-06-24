#include <chrono>
#include <random>
#include <utility>
#include "grafGen.h"

/**
 * Generates a complete graph
 *
 * @param n the amount of nodes
 */
edgeList genKGraph(unsigned int n) {
    edgeList kGraph;
    for (unsigned int i = 0; i < n-1; ++i) {
        for (unsigned int j = i+1; j < n; ++j) {
            kGraph.push_back({i, j});
        }
    }
    return kGraph;
}

edgeList shuffleEdges(const edgeList &edges) {
    long seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator (seed);

    edgeList shuffled(edges);
    for (size_t i = 0; i < shuffled.size(); ++i) {
        std::uniform_int_distribution<size_t> distribution(i, shuffled.size() - 1);
        std::swap(shuffled[i], shuffled[distribution(generator)]);
    }
    return shuffled;
}

edgeList getSubgraph(unsigned int m, const edgeList& base) {
    edgeList shuffled = shuffleEdges(base);
    edgeList subgraph;
    for (unsigned int i = 0; i < m; ++i) {
        subgraph.push_back(shuffled[i]);
    }
    return subgraph;
}


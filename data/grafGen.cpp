#include <chrono>
#include <random>
#include <utility>
#include <cassert>
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

adjList createWithMaxDeg(unsigned int n, unsigned int m, unsigned int maxDeg) {
    if(maxDeg >= n || maxDeg > m) {
        throw graphGenException("Not enough nodes or edges for max degree " + maxDeg);
    }
    adjList res(n, nodeSet());
    unsigned int u = 0;
    unsigned int v = 1;
    for (unsigned int i = 0; i < m; ++i) {
        while(res[u].size() == maxDeg || v >= n) {
            ++u;
            v = u + 1;
            if(u >= n - 1) {
                throw graphGenException("Too many edges for max degree " + maxDeg);
            }
        }
        res[u].push_back(v);
        res[v++].push_back(u);
    }
    long seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator (seed);
    for (size_t i = 0; i < res.size(); ++i) {
        for (size_t j = 0; j < res[i].size(); ++j) {
            std::uniform_int_distribution<size_t> distribution(j, res[i].size() - 1);
            std::swap(res[i][j], res[i][distribution(generator)]);
        }
    }
    return res;
}

const char* graphGenException::what() const noexcept {
    return msg.c_str();
}

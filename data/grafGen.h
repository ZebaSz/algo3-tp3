#ifndef ALGO3_TP3_GRAFGEN_H
#define ALGO3_TP3_GRAFGEN_H

#include "../src/graph.h"

edgeList genKGraph(unsigned int n);
edgeList shuffleEdges(const edgeList &edges);
edgeList getSubgraph(unsigned int m, const edgeList &base);
adjList createWithMaxDeg(unsigned int n, unsigned int m, unsigned int maxDeg);

class graphGenException : std::exception {
public:
    graphGenException(const std::string&) : std::exception() {}

    virtual const char* what() const noexcept;

private:
    const std::string msg;
};

#endif //ALGO3_TP3_GRAFGEN_H

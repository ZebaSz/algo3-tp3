#ifndef ALGO3_TP2_GRAPH_H
#define ALGO3_TP2_GRAPH_H

#include <vector>

#define INF INT_MAX

struct edge {
    unsigned int start;
    unsigned int end;
};

typedef std::vector<edge> edgeList;

bool operator<(const edge&, const edge&);
bool operator>(const edge&, const edge&);
bool operator==(const edge&, const edge&);
bool operator!=(const edge&, const edge&);

#endif //ALGO3_TP2_GRAPH_H

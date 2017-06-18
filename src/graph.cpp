#include "graph.h"

bool operator<(const edge& e, const edge& f) {
    return e.weight < f.weight;
}

bool operator>(const edge& e, const edge& f) {
    return f < e;
}

bool operator==(const edge& e, const edge& f) {
    return e.start == f.start && e.end == f.end && e.weight == f.weight;
}

bool operator!=(const edge& e, const edge& f) {
    return !(e == f);
}

bool operator<(const adjacency& e, const adjacency& f) {
    return e.weight < f.weight;
}

bool operator>(const adjacency& e, const adjacency& f) {
    return f < e;
}

bool operator==(const adjacency& e, const adjacency& f) {
    return e.node == f.node && e.weight == f.weight;
}

bool operator!=(const adjacency& e, const adjacency& f) {
    return !(e == f);
}
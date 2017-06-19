#include "graph.h"

bool operator==(const edge& e, const edge& f) {
    return e.start == f.start && e.end == f.end;
}

bool operator!=(const edge& e, const edge& f) {
    return !(e == f);
}
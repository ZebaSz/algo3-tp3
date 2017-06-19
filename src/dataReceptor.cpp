#include <iostream>
#include "exact.h"

struct input {
    int n;
    int m;
    edgeList edges;
};

int main() {
    bool hasInput = true;
    std::vector<input> inputs;
    while(hasInput) {
        int n, m;

        std::cin >> n >> m;
        hasInput = n != -1 || m != -1;
        if(hasInput) {
            input in;
            in.n = n;
            in.m = m;
            for(int i = 0; i < m; ++i) {
                unsigned int c1, c2;
                int p;
                std::cin >> c1 >> c2;
                --c1;
                --c2;
                in.edges.push_back({c1, c2});
            }
            inputs.push_back(in);
        }
    }
    std::vector<input>::const_iterator it;
    for(it = inputs.begin(); it != inputs.end(); ++it) {
        std::cout << exactCMF(it->n, it->m, it->edges) << std::endl;
    }
    return 0;
}
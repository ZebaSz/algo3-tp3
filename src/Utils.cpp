#include <cstdarg>
#include <cstdio>
#include <iostream>
#include "Utils.h"

namespace Utils {

    void log(logLevel level, const char* format, ...) {
        if(CUR_LOG_LEVEL <= level) {
            va_list args;
            va_start(args, format);
            vprintf(format, args);
            std::cout << std::endl;
            va_end(args);
        }
    }

    graphInfo parseGraph(std::istream& is) {
        graphInfo info;
        is >> info.n;
        unsigned int m;
        is >> m;
        for(unsigned int i = 0; i < m; ++i) {
            node c1, c2;
            is >> c1 >> c2;
            --c1;
            --c2;
            info.edges.push_back({c1, c2});
        }
        return info;
    }

    cliqueInfo parseCliqueInfo(std::string filename) {
        std::ifstream file(filename);

        unsigned int f;
        size_t k;
        file >> f >> k;
        cliqueInfo info(k, f);
        for (size_t i = 0; i < k; ++i) {
            file >> info.nodes[i];
            --info.nodes[i];
        }

        file.close();

        return info;
    }

    void printClique(const cliqueInfo &clique) {
        printf("%u %lu", clique.outgoing, clique.nodes.size());
        for(size_t i = 0; i < clique.nodes.size(); ++i) {
            printf(" %u", clique.nodes[i] + 1);
        }
        printf("\n");
    }
}
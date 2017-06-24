#ifndef ALGO3_TP3_UTILS_H
#define ALGO3_TP3_UTILS_H

#include <vector>
#include <fstream>
#include "clique.h"

typedef int logLevel;
enum LOG_LEVEL {TRACE, DEBUG, INFO, WARN, ERROR, OFF};

#define CUR_LOG_LEVEL INFO

namespace Utils {
    void log(logLevel level, const char* format, ...);

    graphInfo parseGraph(std::istream& is);

    cliqueInfo parseCliqueInfo(std::string filename);

    template<typename T>
    void addAll(std::vector<T> &dest, const std::vector<T> &src) {
        dest.insert(dest.end(), src.begin(), src.end());
    }
}


#endif //ALGO3_TP3_UTILS_H

#ifndef ALGO3_TP2_UTILS_H
#define ALGO3_TP2_UTILS_H

#include <vector>

typedef int logLevel;
enum LOG_LEVEL {TRACE, DEBUG, INFO, WARN, ERROR, OFF};

#define CUR_LOG_LEVEL INFO

namespace Utils {
    void log(logLevel level, const char* format, ...);

    template<typename T>
    void addAll(std::vector<T> &dest, const std::vector<T> &src) {
        dest.insert(dest.end(), src.begin(), src.end());
    }
}


#endif //ALGO3_TP2_UTILS_H

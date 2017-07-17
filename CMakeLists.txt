cmake_minimum_required(VERSION 2.6)
project(algo3_tp3)

set(SOURCE_FILES src/Utils.cpp
        src/exact.cpp src/clique.h src/graph.cpp
        src/greedy.cpp
        src/localsearch.cpp
        src/grasp.cpp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -pedantic")

add_library(algo3-tp3-base ${SOURCE_FILES})

add_executable(ej1 src/ej1.cpp)
target_link_libraries (ej1 algo3-tp3-base)

add_executable(ej2 src/ej2.cpp)
target_link_libraries (ej2 algo3-tp3-base)

add_executable(ej3 src/ej3.cpp)
target_link_libraries (ej3 algo3-tp3-base)

add_executable(ej4 src/ej4.cpp)
target_link_libraries (ej4 algo3-tp3-base)

#add_subdirectory(test)

#add_subdirectory(data)

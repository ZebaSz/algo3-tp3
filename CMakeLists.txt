cmake_minimum_required(VERSION 2.6)
project(algo3_tp3)

#TODO agregar archivos fuente aqui
set(SOURCE_FILES src/Utils.cpp
        src/exact.cpp src/clique.h src/graph.cpp
        src/greedy.cpp
        src/localsearch.cpp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -pedantic")

add_library(algo3-tp3-base ${SOURCE_FILES})

#TODO agregar ejecutables entregables 
add_executable(exact src/dataReceptor.cpp)
target_link_libraries (exact algo3-tp3-base)

add_subdirectory(test)

add_subdirectory(data)

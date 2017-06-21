#ifndef ALGO3_TP3_EXACT_H
#define ALGO3_TP3_EXACT_H

#include "graph.h"
#include "clique.h"

/**
 * Returns whether adding a given node to a clique yields a new clique
 *
 * @param graph the graph as an adjacency matrix
 * @param subclique a clique within the graph
 * @param node a node in the graph
 * @return true if the subclique plus the node is a valid clique in the graph
 */
bool isClique(const adjMatrix& graph, const nodeSet& subclique, unsigned int node);

/**
 * Gets all cliques of size k+1 for a given set of cliques of size k
 *
 * @param graph the graph as an adjacency matrix
 * @param subcliques a list of unique cliques of size k
 * @param cliques the list of cliques of size k+1 to output
 */
void expandCliques(const adjMatrix& graph, const std::vector<nodeSet>& subcliques,
                   std::vector<nodeSet>& cliques);

/**
 * Finds all cliques for a given graph
 *
 * @param graph the graph as an adjacency matrix
 * @return a list of all unique cliques
 */
std::vector<nodeSet> findAllCliques(const adjMatrix& graph);

/**
 * Creates a triangular adjacency matrix
 * Only half of the matrix is filled
 *
 * @param n the number of vertices
 * @param input the graph as a list of edges
 * @return the graph as an adjacency matrix
 */
adjMatrix createAdjacencyMatrix(const graphInfo &input);



/**
 * Finds the clique with maximum outgoing edges for a given graph
 *
 * @param n the number of vertices
 * @param input the graph as a list of edges
 * @return the maximum number of outgoing edges for all cliques in the graph
 */
cliqueInfo exactCMF(const graphInfo &input);

#endif //ALGO3_TP3_EXACT_H
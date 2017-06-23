#ifndef ALGO3_TP2_GRAPH_H
#define ALGO3_TP2_GRAPH_H

#include <vector>

typedef unsigned int node;
typedef std::vector<unsigned int> nodeSet;
typedef std::vector< std::vector< bool > > adjMatrix;
typedef std::vector< std::vector< node > > adjList;

struct edge {
    node start;
    node end;
};

typedef std::vector<edge> edgeList;

struct graphInfo {
    unsigned int n;
    edgeList edges;
};

namespace Graph {

    /**
     * Creates an adjacency matrix
     *
     * @param n the number of vertices
     * @param input the graph as a list of edges
     * @return the graph as an adjacency matrix
     * @complexity O(|E|)
     */
    adjMatrix createAdjacencyMatrix(const graphInfo &input);


    /**
     * Creates an adjacency list
     * @param input incidence list
     * @return the grapsh as an adjacency list
     * @complexity O(|V| + |E|)
     */
    adjList createAdjacencyList(const graphInfo &input);

    /**
     * Returns whether adding a given node to a clique yields a new clique
     *
     * @info Esta es la nueva isClique
     * @param graph the graph as an adjacency matrix
     * @param subclique a clique within the graph
     * @param node a node in the graph
     * @return true if the subclique plus the node is a valid clique in the graph
     * @complexity O(|subclique|))
     */
    bool allAdjacentTo(const adjMatrix& graph, const nodeSet& subclique, const node node);
    bool allAdjacentTo(const adjList& graph, const nodeSet& subclique, const node node);

    /**
     * @precondition La lista de adyacencias y el la lista de la subclique tiene que estar ordenado
     * @param graph
     * @param subclique
     * @param node
     * @return Si el nodo es adyacente a todos los nodos de la subclique
     * @complexity O(|adj(node)|))
     */
    bool allAdjacentToOrd(const adjList &graph, const nodeSet &subclique, const node node);

}
#endif //ALGO3_TP2_GRAPH_H

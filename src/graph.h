#ifndef ALGO3_TP3_GRAPH_H
#define ALGO3_TP3_GRAPH_H
#include <algorithm>
#include <vector>

typedef unsigned int node;
typedef std::vector<node> nodeSet;
typedef std::vector< std::vector< bool > > adjMatrix;
typedef std::vector< std::vector< node > > adjList;

struct greaterDegreeComparator {
    greaterDegreeComparator(const adjList &l) : list(l) {}

    bool operator()(const node &n1, const node &n2) {
        return list[n1].size() > list[n2].size();
    }
    const adjList &list;
};

struct edge {
    node start;
    node end;
};

typedef std::vector<edge> edgeList;

struct graphInfo {
    unsigned int n;
    edgeList edges;
};

void insertSorted(nodeSet &list, node n); //Se usa para crear la lista de adj

namespace Graph {

    /**
     * Creates a triangular adjacency matrix
     * For a < b, the matrix will contain edge (a, b) but not (b, a)
     *
     * @param n the number of vertices
     * @param input the graph as a list of edges
     * @return the graph as an adjacency matrix
     * @complexity O(|E|)
     */
    adjMatrix createTriangularMatrix(const graphInfo &input);

    /**
     * Creates an adjacency list
     * @param input incidence list
     * @return the graph as an adjacency list
     * @complexity O(|V| + |E|)
     */
    adjList createAdjacencyList(const graphInfo &input);


    bool isAdjacentTo(const adjList& graph, const node n1, const node n2);

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
     * Search one of the nodes with max degree
     * @param graph
     * @return the node with max degree
     * @complexity O(|V|)
     */
    node nodeWithMaxDegree(const adjList &graph);

    void sortByDegree(nodeSet nodesToSort, const adjList &graph);

}
#endif //ALGO3_TP3_GRAPH_H

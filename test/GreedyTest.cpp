#include "AbstractTest.h"
#include "../src/greedy.h"

class GreedyTest : public AbstractTest {
};

TEST_F(GreedyTest, k4) {
    ASSERT_EQ(greedyHeuristic(k4).outgoing, (unsigned int)4);
}

TEST_F(GreedyTest, k4PlusTwoEdges) {
    ASSERT_EQ(greedyHeuristic(k4plus).outgoing, (unsigned int)6);
}

TEST_F(GreedyTest, adjacencyLust) {
    graphInfo graph;
    graph.n = 10;
    graph.edges.push_back({0,1});
    graph.edges.push_back({1,2});
    graph.edges.push_back({2,0});
    graph.edges.push_back({2,3});
    graph.edges.push_back({4,5});
    graph.edges.push_back({5,6});
    graph.edges.push_back({6,4});
    graph.edges.push_back({6,3});
    graph.edges.push_back({3,7});
    graph.edges.push_back({7,8});
    graph.edges.push_back({8,9});
    graph.edges.push_back({9,7});
    adjList aj = Graph::createAdjacencyList(graph);
    ASSERT_EQ(aj.size(), (size_t)10); //#nodes
    ASSERT_EQ(aj[0].size(), (size_t)2); //degree of first node
    ASSERT_EQ(aj[1].size(), (size_t)2); //degree of second node
    ASSERT_EQ(aj[0][0], (unsigned int)1); //0 and 1 are adjacent
    ASSERT_EQ(aj[0][1], (unsigned int)2); //0 and 2 are adjacent
}

TEST_F(GreedyTest, sortNodesByDegree) {
    graphInfo graph;
    graph.n = 10;
    graph.edges.push_back({0,1});
    graph.edges.push_back({1,2});
    graph.edges.push_back({2,0});
    graph.edges.push_back({2,3});
    graph.edges.push_back({4,5});
    graph.edges.push_back({5,6});
    graph.edges.push_back({6,4});
    graph.edges.push_back({6,3});
    graph.edges.push_back({3,7});
    graph.edges.push_back({7,8});
    graph.edges.push_back({8,9});
    graph.edges.push_back({9,7});
    adjList al = Graph::createAdjacencyList(graph);
    // node | degree    1 2     2 2     3 3     4 3     5 2     6 2     7 3     8 3     9 2     10 2
    nodeSet ns;
    for(unsigned int i = 0; i < al.size(); i++){
        ns.push_back(i);
    }
    std::sort(ns.begin(), ns.end(), greaterDegreeComparator(al));
    ASSERT_EQ(al[ns[0]].size(), (size_t)3);
    ASSERT_EQ(al[ns[1]].size(), (size_t)3);
    ASSERT_EQ(al[ns[2]].size(), (size_t)3);
    ASSERT_EQ(al[ns[3]].size(), (size_t)3);
    ASSERT_EQ(al[ns[4]].size(), (size_t)2);
    ASSERT_EQ(al[ns[5]].size(), (size_t)2);
    ASSERT_EQ(al[ns[6]].size(), (size_t)2);
    ASSERT_EQ(al[ns[7]].size(), (size_t)2);
    ASSERT_EQ(al[ns[8]].size(), (size_t)2);
    ASSERT_EQ(al[ns[9]].size(), (size_t)2);
}

TEST_F(GreedyTest, cliqueDetection) {
    adjList al = Graph::createAdjacencyList(k4plus);
    nodeSet ns;
    ns.push_back(0);
    ns.push_back(1);
    ns.push_back(2);
    ASSERT_TRUE(Graph::allAdjacentTo(al, ns, 3));
    ASSERT_FALSE(Graph::allAdjacentTo(al, ns, 4));
}

TEST_F(GreedyTest, allSmall) {
    std::vector<testcase> tests(getTests(true));
    for (size_t i = 0; i < tests.size(); ++i) {
        cliqueInfo result = greedyHeuristic(tests[i].input);
        ASSERT_LE(result.outgoing, tests[i].output.outgoing) << "Caso small-" << i;
        if(result.outgoing == tests[i].output.outgoing) {
            Utils::log(INFO, "Passed test %d", i);
        }
    }
}

TEST_F(GreedyTest, allHuge) {
    std::vector<testcase> tests(getTests(false));
    for (size_t i = 0; i < tests.size(); ++i) {
        cliqueInfo result = greedyHeuristic(tests[i].input);
        ASSERT_LE(result.outgoing, tests[i].output.outgoing) << "Caso huge-" << i;
        if(result.outgoing == tests[i].output.outgoing) {
            Utils::log(INFO, "Passed test %d", i);
        }
    }
}
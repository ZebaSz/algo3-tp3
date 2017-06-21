#include "AbstractTest.h"
#include "../src/greedy.h"

class GreedyTest : public AbstractTest {
};

TEST_F(GreedyTest, k4) {
    cliqueInfo testClique(0,0);
    ASSERT_EQ(greedyHeuristic(k4, testClique).outgoing, (unsigned int)4);
}

TEST_F(GreedyTest, k4PlusTwoEdges) {
    cliqueInfo testClique(0,0);
    ASSERT_EQ(greedyHeuristic(k4plus, testClique).outgoing, (unsigned int)6);
}
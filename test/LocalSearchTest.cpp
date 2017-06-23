#include "AbstractTest.h"
#include "../src/localsearch.h"

class LocalSearchTest : public AbstractTest {
};

TEST_F(LocalSearchTest, k4) {
    cliqueInfo testClique(0,0);
    ASSERT_EQ(localSearchHeuristic(k4, testClique).outgoing, (unsigned int)4);
}

TEST_F(LocalSearchTest, k4PlusTwoEdges) {
    cliqueInfo testClique(0,0);
    ASSERT_EQ(localSearchHeuristic(k4plus, testClique).outgoing, (unsigned int)6);
}

TEST_F(LocalSearchTest, allSmall) {
    cliqueInfo testClique(0,0);
    std::vector<testcase> tests(getTests(true));
    for (size_t i = 0; i < tests.size(); ++i) {
        if(localSearchHeuristic(tests[i].input, testClique).outgoing == tests[i].output.outgoing) {
            Utils::log(INFO, "Passed test %d", i);
        }
    }
    ASSERT_EQ(localSearchHeuristic(tests[0].input, testClique).outgoing, tests[0].output.outgoing);
}
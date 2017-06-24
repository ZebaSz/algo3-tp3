#include "AbstractTest.h"
#include "../src/localsearch.h"

class LocalSearchTest : public AbstractTest {
};

TEST_F(LocalSearchTest, k4) {
    ASSERT_EQ(localSearchHeuristic(k4).outgoing, (unsigned int)4);
}

TEST_F(LocalSearchTest, k4PlusTwoEdges) {
    ASSERT_EQ(localSearchHeuristic(k4plus).outgoing, (unsigned int)6);
}

TEST_F(LocalSearchTest, allSmall) {
    std::vector<testcase> tests(getTests(true));
    for (size_t i = 0; i < tests.size(); ++i) {
        cliqueInfo result = localSearchHeuristic(tests[i].input);
        ASSERT_LE(result.outgoing, tests[i].output.outgoing) << "Caso small-" << i;
        if(result.outgoing == tests[i].output.outgoing) {
            Utils::log(INFO, "Passed test %d", i);
        } else {
            Utils::log(INFO, "Test %d, difference: %d", i, tests[i].output.outgoing - result.outgoing);
        }
    }
}

TEST_F(LocalSearchTest, allHuge) {
    std::vector<testcase> tests(getTests(false));
    for (size_t i = 0; i < tests.size(); ++i) {
        cliqueInfo result = localSearchHeuristic(tests[i].input);
        ASSERT_LE(result.outgoing, tests[i].output.outgoing) << "Caso huge-" << i;
        if(result.outgoing == tests[i].output.outgoing) {
            Utils::log(INFO, "Passed test %d", i);
        } else {
            Utils::log(INFO, "Test %d, difference: %d", i, tests[i].output.outgoing - result.outgoing);
        }
    }
}
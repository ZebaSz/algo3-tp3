#include "AbstractTest.h"
#include "../src/grasp.h"

class GraspTest : public AbstractTest {
};

TEST_F(GraspTest, k4) {
    ASSERT_EQ(grasp(k4, 0.1, 10).outgoing, (unsigned int)4);
    ASSERT_EQ(grasp(k4, 0.3, 10).outgoing, (unsigned int)4);
    ASSERT_EQ(grasp(k4, 0.5, 10).outgoing, (unsigned int)4);
    ASSERT_EQ(grasp(k4, 0.7, 10).outgoing, (unsigned int)4);
}

TEST_F(GraspTest, k4PlusTwoEdges) {
    ASSERT_EQ(grasp(k4plus, 0.1, 10).outgoing, (unsigned int)6);
    ASSERT_EQ(grasp(k4plus, 0.3, 10).outgoing, (unsigned int)6);
    ASSERT_EQ(grasp(k4plus, 0.5, 10).outgoing, (unsigned int)6);
    ASSERT_EQ(grasp(k4plus, 0.7, 10).outgoing, (unsigned int)6);
}
/*
TEST_F(GraspTest, allSmall) {
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

TEST_F(GraspTest, allHuge) {
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
}*/
#include "AbstractTest.h"
#include "../src/grasp.h"

class GraspTest : public AbstractTest {
};

TEST_F(GraspTest, k4) {
    ASSERT_EQ(grasp(k4, 0.1, 10, mus{0}).outgoing, (unsigned int)4);
    ASSERT_EQ(grasp(k4, 0.3, 10, mus{0}).outgoing, (unsigned int)4);
    ASSERT_EQ(grasp(k4, 0.5, 10, mus{0}).outgoing, (unsigned int)4);
    ASSERT_EQ(grasp(k4, 0.7, 10, mus{0}).outgoing, (unsigned int)4);
}

TEST_F(GraspTest, k4TimeLimit) {
    ASSERT_EQ(grasp(k4, 0.1, 0, mus{10000}).outgoing, (unsigned int)4);
    ASSERT_EQ(grasp(k4, 0.3, 0, mus{10000}).outgoing, (unsigned int)4);
    ASSERT_EQ(grasp(k4, 0.5, 0, mus{10000}).outgoing, (unsigned int)4);
    ASSERT_EQ(grasp(k4, 0.7, 0, mus{10000}).outgoing, (unsigned int)4);
}

TEST_F(GraspTest, k4PlusTwoEdges) {
    ASSERT_EQ(grasp(k4plus, 0.1, 10, mus{0}).outgoing, (unsigned int)6);
    ASSERT_EQ(grasp(k4plus, 0.3, 10, mus{0}).outgoing, (unsigned int)6);
    ASSERT_EQ(grasp(k4plus, 0.5, 10, mus{0}).outgoing, (unsigned int)6);
    ASSERT_EQ(grasp(k4plus, 0.7, 10, mus{0}).outgoing, (unsigned int)6);
}

TEST_F(GraspTest, allSmall) {
    std::vector<testcase> tests(getTests(true));
    for (size_t i = 0; i < tests.size(); ++i) {
        cliqueInfo result = grasp(tests[i].input, 0.1, 10, mus{0});
        ASSERT_LE(result.outgoing, tests[i].output.outgoing) << "Caso small-" << i;
        //ASSERT_GE(result.outgoing, localSearchHeuristic(tests[i].input).outgoing) << "Caso small-" << i;
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
        cliqueInfo result = grasp(tests[i].input, 0.3, 10, mus{0});
        nodeSet resultNodes = result.nodes;
        ASSERT_LE(result.outgoing, tests[i].output.outgoing) << "Caso huge-" << i;
        //ASSERT_GE(result.outgoing, localSearchHeuristic(tests[i].input).outgoing) << "Caso huge-" << i;
        if(result.outgoing == tests[i].output.outgoing) {
            Utils::log(INFO, "Passed test %d", i);
        } else {
            Utils::log(INFO, "Test %d, difference: %d", i, tests[i].output.outgoing - result.outgoing);
        }
    }
}

TEST_F(GraspTest, allHugeTimeLimit) {
    std::vector<testcase> tests(getTests(false));
    for (size_t i = 0; i < tests.size(); ++i) {
        cliqueInfo result = grasp(tests[i].input, 0.3, 0, mus{100});
        nodeSet resultNodes = result.nodes;
        ASSERT_LE(result.outgoing, tests[i].output.outgoing) << "Caso huge-" << i;
        //ASSERT_GE(result.outgoing, localSearchHeuristic(tests[i].input).outgoing) << "Caso huge-" << i;
        if(result.outgoing == tests[i].output.outgoing) {
            Utils::log(INFO, "Passed test %d", i);
        } else {
            Utils::log(INFO, "Test %d, difference: %d", i, tests[i].output.outgoing - result.outgoing);
        }
    }
}
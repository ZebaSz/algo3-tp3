#include <gtest/gtest.h>
#include "../src/graph.h"
#include "../src/exact.h"
#include "AbstractTest.h"

class ExactText : public AbstractTest {
};

TEST_F(ExactText, k4) {
    edges.push_back({0,1});
    edges.push_back({0,2});
    edges.push_back({0,3});
    edges.push_back({1,2});
    edges.push_back({1,3});
    edges.push_back({2,3});

    n = 4;

    ASSERT_EQ(exactCMF({n, edges}).outgoing, (unsigned int)4);
}

TEST_F(ExactText, k4PlusTwoEdges) {
    edges.push_back({0,1});
    edges.push_back({0,2});
    edges.push_back({0,3});
    edges.push_back({1,2});
    edges.push_back({1,3});
    edges.push_back({2,3});
    edges.push_back({3,4});
    edges.push_back({3,5});

    n = 6;

    ASSERT_EQ(exactCMF({n, edges}).outgoing, (unsigned int)6);
}

TEST_F(ExactText, allSmall) {
    std::vector<testcase> tests(getTests(true));
    for (size_t i = 0; i < tests.size(); ++i) {
        ASSERT_EQ(exactCMF(tests[i].input).outgoing, tests[i].output.outgoing);
        Utils::log(DEBUG, "Passed test %d", i);
    }
}

TEST_F(ExactText, allHuge) {
    std::vector<testcase> tests(getTests(false));
    for (size_t i = 0; i < tests.size(); ++i) {
        ASSERT_EQ(exactCMF(tests[i].input).outgoing, tests[i].output.outgoing);
        Utils::log(DEBUG, "Passed test %d", i);
    }
}
#include <gtest/gtest.h>
#include "../src/graph.h"
#include "../src/exact.h"

class ExactText : public ::testing::Test {
protected:
    unsigned int n;
    edgeList edges;
};

TEST_F(ExactText, k4) {
    edges.push_back({0,1});
    edges.push_back({0,2});
    edges.push_back({0,3});
    edges.push_back({1,2});
    edges.push_back({1,3});
    edges.push_back({2,3});

    n = 4;

    ASSERT_EQ(exactCMF(n, edges), (unsigned int)4);
}
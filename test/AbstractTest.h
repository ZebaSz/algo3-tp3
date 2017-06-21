#ifndef ALGO3_TP3_ABSTRACTTEST_H
#define ALGO3_TP3_ABSTRACTTEST_H

#include <gtest/gtest.h>
#include <dirent.h>
#include "../src/graph.h"
#include "../src/clique.h"
#include "../src/Utils.h"

struct testcase {
    graphInfo input;
    cliqueInfo output;
};

class AbstractTest : public ::testing::Test {
protected:
    graphInfo k4;
    graphInfo k4plus;

    virtual void SetUp();

    std::vector<testcase> getTests(bool small);
};

#endif //ALGO3_TP3_ABSTRACTTEST_H

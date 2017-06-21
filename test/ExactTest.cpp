#include "AbstractTest.h"
#include "../src/exact.h"

class ExactText : public AbstractTest {
};

TEST_F(ExactText, k4) {
    ASSERT_EQ(exactCMF(k4).outgoing, (unsigned int)4);
}

TEST_F(ExactText, k4PlusTwoEdges) {
    ASSERT_EQ(exactCMF(k4plus).outgoing, (unsigned int)6);
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
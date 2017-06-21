#include "AbstractTest.h"
#include "boost/filesystem.hpp"

#define SMALLDIR "chicos"
#define BIGDIR "enormes"
#define IN_FILEEXT ".in"
#define OUT_FILEEXT ".out"

void AbstractTest::SetUp() {
    k4.n = 4;

    k4.edges.push_back({0,1});
    k4.edges.push_back({0,2});
    k4.edges.push_back({0,3});
    k4.edges.push_back({1,2});
    k4.edges.push_back({1,3});
    k4.edges.push_back({2,3});

    k4plus.n = 6;
    k4plus.edges.insert(k4plus.edges.end(), k4.edges.begin(), k4.edges.end());
    k4plus.edges.push_back({3,4});
    k4plus.edges.push_back({3,5});
}

std::vector<testcase> AbstractTest::getTests(bool small) {
    std::vector<testcase> tests;
    std::string dirname = small ? SMALLDIR : BIGDIR;

    if(boost::filesystem::exists(dirname)) {
        boost::filesystem::directory_iterator end_itr;
        for (boost::filesystem::directory_iterator itr(dirname); itr != end_itr; ++itr) {
            if (itr->path().extension() == OUT_FILEEXT) {
                std::string outputName = itr->path().string();
                std::string inputName = outputName.substr(0, outputName.size() - 4) + IN_FILEEXT;

                std::ifstream inputFile(inputName);
                tests.push_back({Utils::parseGraph(inputFile), Utils::parseCliqueInfo(outputName)});
                inputFile.close();
            }
        }
    }
    return tests;
}
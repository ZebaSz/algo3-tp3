#include "AbstractTest.h"
#include "boost/filesystem.hpp"

#define SMALLDIR "chicos"
#define BIGDIR "enormes"
#define IN_FILEEXT ".in"
#define OUT_FILEEXT ".out"

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
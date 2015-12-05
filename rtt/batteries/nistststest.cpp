#include "nistststest.h"

namespace rtt {
namespace batteries {

NistStsTest::NistStsTest(std::string name, std::string dir, int testCount) :
    logicalName(name) , resultDir(dir) , subTestCount(testCount) {

    testLog = Utils::readFileToString(resultDir + "stats.txt");

    if(testCount == 1) {
        /* only file results.txt will be processed */
        std::vector<float> pVals = readPVals(resultDir + "results.txt");
        testPValues.push_back(pVals);
    } else {
        /* multiple dataX.txt files will be processed */
        for(int i = 1 ; i <= testCount ; ++i) {
            std::stringstream resultFileName;
            resultFileName << resultDir << "data" << i << ".txt";
            std::vector<float> pVals = readPVals(resultFileName.str());
            testPValues.push_back(pVals);
        }
    }
}

std::vector<float> NistStsTest::readPVals(std::string fileName) {
    std::ifstream pValFile(fileName);
    if(!pValFile.is_open())
        throw std::runtime_error("can't open file: " + fileName);
    std::string strPVal;
    float pVal;
    std::vector<float> pVal_v;

    /* File is read line by line */
    /* Each line should be one p-value */
    while(std::getline(pValFile , strPVal)) {
        pVal = Utils::strtof(strPVal);
        if(pVal < 0 || pVal > 1)
            throw std::runtime_error("file: " + fileName + " contains p-value"
                                     "that is not in <0,1> interval");
        pVal_v.push_back(pVal);
    }
    return pVal_v;
}

} // namespace batteries
} // namespace rtt


#include "rtt/batteries/dieharder/test-dh.h"

namespace rtt {
namespace batteries {
namespace dieharder {

std::unique_ptr<Test> Test::getInstance(int testIndex , const GlobalContainer & container) {
    std::unique_ptr<Test> t (new Test(testIndex , container));

    t->logicName = std::get<0>(TestConstants::getDieharderTestData(
                                   t->battId , t->testId));
    return t;
}

std::vector<std::string> Test::getTestUserSettings() const {
    raiseBugException("implementation underway");

}

std::vector<std::vector<std::string> > Test::getTestsParameters() const {
    /* Nothing interesting */
    return {};
}

std::vector<std::string> Test::getStatistics() const {
    return {"Kolmogorov-Smirnov"};
}

/*
                     __                       __
                    |  \                     |  \
  ______    ______   \$$ __     __  ______  _| $$_     ______
 /      \  /      \ |  \|  \   /  \|      \|   $$ \   /      \
|  $$$$$$\|  $$$$$$\| $$ \$$\ /  $$ \$$$$$$\\$$$$$$  |  $$$$$$\
| $$  | $$| $$   \$$| $$  \$$\  $$ /      $$ | $$ __ | $$    $$
| $$__/ $$| $$      | $$   \$$ $$ |  $$$$$$$ | $$|  \| $$$$$$$$
| $$    $$| $$      | $$    \$$$   \$$    $$  \$$  $$ \$$     \
| $$$$$$$  \$$       \$$     \$     \$$$$$$$   \$$$$   \$$$$$$$
| $$
| $$
 \$$
*/

void Test::processBatteryOutput() {
//    static const std::regex RE_PSAMPLE_VALUE {"\\+\\+\\+\\+([01]\\.[0-9]+?)\\+\\+\\+\\+\\n"};

//    auto testLog = batteryOutput.getStdOut();
//    auto begin = std::sregex_iterator(testLog.begin() ,
//                                      testLog.end() ,
//                                      RE_PSAMPLE_VALUE);
//    auto end = std::sregex_iterator();

//    int pValCount = std::distance(begin , end);
//    if(pValCount == 0) {
//        logger->warn(objectInfo + Strings::TEST_ERR_NO_PVALS_EXTRACTED);
//        return;
//    }

//    if(pValCount % pSampleCount != 0) {
//        logger->warn(objectInfo + Strings::TEST_ERR_PVALS_BAD_COUNT);
//        return;
//    }

//    subTestsCount = pValCount / pSampleCount;
//    tTestPvals pSamples;

//    for(int subTestIndex = 0 ; subTestIndex < subTestsCount ; ++subTestIndex) {
//        for(int i = 0 ; i < pSampleCount ; ++i) {
//            std::smatch match = *begin;
//            pSamples.push_back(Utils::strtod(match[1].str()));
//            ++begin;
//        }
//        results.push_back(std::move(pSamples));
//        pSamples.clear();
//    }
}

} // namespace dieharder
} // namespace batteries
} // namespace rtt


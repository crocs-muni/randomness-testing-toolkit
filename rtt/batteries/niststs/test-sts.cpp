#include "test-sts.h"

#include "rtt/batteries/niststs/variant-sts.h"

namespace rtt {
namespace batteries {
namespace niststs {

std::unique_ptr<Test> Test::getInstance(int testIndex,
                                        const GlobalContainer & cont) {
    std::unique_ptr<Test> t (new Test(testIndex , cont));

    t->logicName = std::get<0>(TestConstants::getNistStsTestData(
                                   t->battId , t->testId));
    t->testDir_mux = std::make_unique<std::mutex>();

    for(const std::unique_ptr<IVariant> & var : t->variants) {
        Variant * stsVar = dynamic_cast<Variant*>(var.get());
        stsVar->setTestDir_mux(t->testDir_mux.get());
    }

    return t;
}

std::vector<std::string> Test::getTestUserSettings() const {
    raiseBugException("implementation underway");
    std::vector<std::vector<std::string>> rval;
    for(const auto & var : variants)
        rval.push_back(var->getUserSettings());

    //return rval;
}

std::vector<std::vector<std::string> > Test::getTestsParameters() const {
    /* Nothing interesting */
    return {};
}

std::vector<std::string> Test::getStatistics() const {
    return { "Chi-square" , "Proportion" };
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

std::string Test::createArgs() const {
    raiseBugException("implementation underway");
}

std::string Test::createInput() const {
    raiseBugException("implementation underway");
}

void Test::processBatteryOutput() {
//    try {
//        auto testLog = Utils::readFileToString(resultSubDir + "stats.txt");
//        batteryOutput.appendStdOut(testLog);

//        if(testId == 12 ||  /* Random excursions */
//           testId == 13 ) { /* Random excursions variant */
//            /* Random excursions tests are exceptions (of course they are)
//             * p-values must be read directly from log and their count must
//             * be divisible by subTestCount. Otherwise something happened. */
//            static const std::regex RE_PVALUE {"p[\\-_]value = ([0|1]?\\.[0-9]+?)\\n"};
//            auto begin = std::sregex_iterator(testLog.begin() , testLog.end() , RE_PVALUE);
//            auto end = std::sregex_iterator();
//            int pValCount = std::distance(begin , end);
//            if(pValCount == 0) {
//                logger->warn(objectInfo + Strings::TEST_ERR_NO_PVALS_EXTRACTED);
//                //streamCount = "0";
//                return;
//            }

//            if(pValCount % subTestCount != 0) {
//                logger->warn(objectInfo + Strings::TEST_ERR_PVALS_BAD_COUNT);
//                return;
//            }
//            int strCount = pValCount / subTestCount;
//            streamCount = Utils::itostr(strCount);

//            tTestPvals allResults;
//            for( ; begin != end ; ++begin) {
//                std::smatch match = *begin;
//                allResults.push_back(Utils::strtod(match[1].str()));
//            }

//            tTestPvals testResults;
//            for(int test = 0 ; test < subTestCount ; ++test) {
//                for(int i = test ; i < pValCount ; i += subTestCount)
//                    testResults.push_back(allResults.at(i));

//                results.push_back(std::move(testResults));
//                testResults.clear();
//            }
//        } else {
//            if(subTestCount == 1) {
//                /* Only file results.txt will be processed */
//                tTestPvals pVals = readPvals(resultSubDir + "results.txt");
//                results.push_back(pVals);
//            } else {
//                /* Multiple dataX.txt files will be processed */
//                std::stringstream fName;
//                tTestPvals pVals;
//                for(int i = 1 ; i <= subTestCount ; ++i) {
//                    fName << resultSubDir << "data" << i << ".txt";
//                    pVals = std::move(readPvals(fName.str()));
//                    results.push_back(pVals);
//                    pVals.clear();
//                    fName.str("");fName.clear();
//                }
//            }
//        }

//        /* Preppending output from test run to test run */
//    } catch (std::runtime_error ex) {
//        logger->warn(objectInfo + Strings::TEST_ERR_EXCEPTION_DURING_THREAD + ex.what());
//    }
}

tTestPvals Test::readPvals(const std::string & fileName) {
    std::ifstream pValFile(fileName);
    if(!pValFile.is_open())
            throw std::runtime_error("can't open file: " + fileName);

    std::string strPval;
    float pVal;
    tTestPvals vecPval;

    /* File is read line by line */
    /* Each line should be one p-value */
    while(std::getline(pValFile , strPval)) {
        pVal = Utils::strtod(strPval);
        if(pVal < 0 || pVal > 1)
            throw std::runtime_error(Strings::TEST_ERR_PVAL_OUTSIDE_INTERVAL + fileName);
        /* This silly condition is here for random excursions test */
        /* Because when you can't apply test it is feasible to give 0 as answer *rolls eyes* */
        if(pVal == 0 && (testId == 12 || testId == 13))
            continue;

        vecPval.push_back(pVal);
    }
    return vecPval;
}

} // namespace niststs
} // namespace batteries
} // namespace rtt

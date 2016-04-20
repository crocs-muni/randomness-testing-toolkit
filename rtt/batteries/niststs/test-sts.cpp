#include "test-sts.h"

namespace rtt {
namespace batteries {
namespace niststs {

std::unique_ptr<Test> Test::getInstance(int testIndex,
                                        const Globals & globals) {
    std::unique_ptr<Test> t (new Test());
    t->cliOptions = globals.getCliOptions();
    t->toolkitSettings = globals.getToolkitSettings();
    t->batteryConfiguration = globals.getBatteryConfiguration();
    t->testIndex = testIndex;
    t->battery = t->cliOptions->getBattery();
    t->objectInfo = Constants::batteryToString(t->battery) +
                       " - test " + Utils::itostr(testIndex);

    std::tie(t->logicName ,
             t->resultSubDir,
             t->subTestCount,
             t->adjustableBlockLen) =
            TestConstants::getNistStsTestData(t->battery , t->testIndex);

    /* Binary data path */
    t->binaryDataPath = t->cliOptions->getBinFilePath();
    if(t->binaryDataPath.empty())
        raiseBugException("empty input binary data");
    /* NIST STS executable path */
    t->executablePath = t->toolkitSettings->getBinaryBattery(t->battery);
    if(t->executablePath.empty())
        raiseBugException("empty executable binary");
    /* Stream size */
    t->streamSize = t->batteryConfiguration->getNiststsTestStreamSize(testIndex);
    if(t->streamSize.empty())
        t->streamSize = t->batteryConfiguration->getNiststsDefaultStreamSize();
    if(t->streamSize.empty())
        throw RTTException(t->objectInfo , "stream size not set");
    /* Count of streams */
    t->streamCount = t->batteryConfiguration->getNiststsTestStreamCount(testIndex);
    if(t->streamCount.empty())
        t->streamCount = t->batteryConfiguration->getNiststsDefaultStreamCount();
    if(t->streamCount.empty())
        throw RTTException(t->objectInfo , "stream count not set");
    /* Block length */
    t->blockLength = t->batteryConfiguration->getNiststsTestBlockLength(testIndex);

    return t;
}

void Test::appendTestLog(std::string & batteryLog) const {
    if(!executed)
        throw RTTException(objectInfo , "test wasn't executed, can't provide logs");

    batteryLog.append(outputLog);
    batteryLog.append(testLog);
}

int Test::getTestIndex() const {
    return testIndex;
}

void Test::execute() {
    /* This method is turned into thread.
     * Will deadlock if run without main thread. */

    /* Cleaning the test result directory */
    Utils::rmDirFiles(resultSubDir);
    outputLog = TestRunner::executeBinary(executablePath ,
                                          createArgs() ,
                                          createInput());
    //try {
        parseStoreResults();
    //} catch (std::runtime_error ex) {
    //    std::cout << "[ERROR] An exception was thrown "
    //                 "during thread execution: " << ex.what() << std::endl;
    //}

    executed = true;
}

std::string Test::getLogicName() const {
    return logicName;
}

std::vector<std::string> Test::getParameters() const {
    std::stringstream parameters;
    parameters << "Stream size: " << streamSize << std::endl;
    parameters << "Stream count: " << streamCount << std::endl;
    if(!blockLength.empty() && adjustableBlockLen)
        parameters << "Block length: " << blockLength;

    return Utils::split(parameters.str() , '\n');
}

std::vector<std::string> Test::getStatistics() const {
    return {"Chi-square" , "Proportion"};
}

std::vector<tTestPvals> Test::getResults() const {
    if(!executed)
        throw RTTException(objectInfo , "test wasn't executed, can't provide results");
        //throw std::runtime_error("can't return results before execution of test");

    return results;
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
    std::stringstream arguments;
    arguments << "assess " << streamSize << " -fast";
    return arguments.str();
}

std::string Test::createInput() const {
    /* 'Beautiful' creation of input that will be sent to */
    /* sts over pipe, so that it will have proper settings. */
    std::stringstream inputSequence;
    /* Choosing input file generator */
    inputSequence << "0 ";
    /* Choosing file */
    inputSequence << binaryDataPath << " ";
    /* I don't want to execute all tests */
    inputSequence << "0 ";
    /* Specifying which test I want to execute */
    std::string tmp(15 , '0');
    tmp[testIndex - 1] = '1';
    inputSequence << tmp << " ";
    /* Setting blocksize of a test */
    /* If it's not possible, this setting is ommited */
    if(adjustableBlockLen) {
        if(blockLength.empty()) {
            /* Not adjusting anything, just entering 0 */
            /* to continue */
            inputSequence << "0 ";
        } else {
            /* Adjusting the block size */
            /* Always ruuning just one test, its index is always 1 */
            inputSequence << "1 ";
            /* Entering actual value of new block size */
            inputSequence << blockLength << " ";
            /* Entering 0 to continue */
            inputSequence << "0 ";
        }
    }
    /* Specifying stream count */
    inputSequence << streamCount << " ";
    /* Setting input file type as binary */
    inputSequence << "1";
    /* Confirm input with newline */
    inputSequence << std::endl;
    return inputSequence.str();
}

void Test::parseStoreResults() {
    try {
        testLog = Utils::readFileToString(resultSubDir + "stats.txt");

        if(testIndex == 12 || /* Random excursions */
           testIndex == 13    /* Random excursions variant */) {
            /* Random excursions tests are exceptions (of course they are)
             * p-values must be read directly from log and their count must
             * be divisible by subtestcount. Otherwise something happened. */
            static const std::regex RE_PVALUE {"p[\\-_]value = ([0|1]?\\.[0-9]+?)\\n"};
            auto begin = std::sregex_iterator(testLog.begin() , testLog.end() , RE_PVALUE);
            auto end = std::sregex_iterator();
            int pValCount = std::distance(begin , end);
            if(pValCount == 0) {
                std::cout << "[WARNING] No pValues were extracted." << std::endl;
                streamCount = "0";
                return;
            }

            if(pValCount % subTestCount != 0) {
                std::cout << "[WARNING] " << objectInfo << ": p-values can't be extracted from log: "
                             "Number of p-values is not divisible by number of repetitions." << std::endl;
                return;
                //throw std::runtime_error("can't extract p-values from log: number of"
                //                         " p-value is not divisible by repetitions");
            }
            int strCount = pValCount / subTestCount;
            streamCount = Utils::itostr(strCount);

            tTestPvals allResults;
            for( ; begin != end ; ++begin) {
                std::smatch match = *begin;
                allResults.push_back(Utils::strtod(match[1].str()));
            }

            tTestPvals testResults;
            for(int test = 0 ; test < subTestCount ; ++test) {
                for(int i = test ; i < pValCount ; i += subTestCount)
                    testResults.push_back(allResults.at(i));

                results.push_back(std::move(testResults));
                testResults.clear();
            }
        } else {
            if(subTestCount == 1) {
                /* Only file results.txt will be processed */
                tTestPvals pVals = readPvals(resultSubDir + "results.txt");
                results.push_back(pVals);
            } else {
                /* Multiple dataX.txt files will be processed */
                std::stringstream fName;
                tTestPvals pVals;
                for(int i = 1 ; i <= subTestCount ; ++i) {
                    fName << resultSubDir << "data" << i << ".txt";
                    pVals = std::move(readPvals(fName.str()));
                    results.push_back(pVals);
                    pVals.clear();
                    fName.str("");fName.clear();
                }
            }
        }
    } catch (std::runtime_error ex) {
        throw RTTException(objectInfo , ex.what());
    }
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
            throw std::runtime_error("file: " + fileName + " contains p-value"
                                     "that is not in <0,1> interval");
        /* This silly condition is here for random excursions test */
        /* Because when you can't apply test it is feasible to give 0 as answer *eyeroll* */
        if(pVal == 0 && (testIndex == 12 || testIndex == 13))
            continue;

        vecPval.push_back(pVal);
    }
    return vecPval;
}

} // namespace niststs
} // namespace batteries
} // namespace rtt


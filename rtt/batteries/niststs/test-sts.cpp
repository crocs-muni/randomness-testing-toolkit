#include "test-sts.h"

namespace rtt {
namespace batteries {
namespace niststs {

/* Constant definition */
const std::string Test::XPATH_BINARY_PATH           = "NIST_STS_SETTINGS/BINARY_PATH";
const std::string Test::XPATH_OUTPUT_DIRECTORY      = "NIST_STS_SETTINGS/DEFAULT_OUTPUT_DIRECTORY";
const std::string Test::XPATH_DEFAULT_STREAM_SIZE   = "NIST_STS_SETTINGS/DEFAULT_STREAM_SIZE";
const std::string Test::XPATH_DEFAULT_STREAM_COUNT  = "NIST_STS_SETTINGS/DEFAULT_STREAM_COUNT";
const std::string Test::XPATH_TEST_STREAM_SIZE      = "STREAM_SIZE";
const std::string Test::XPATH_TEST_STREAM_COUNT     = "STREAM_COUNT";
const std::string Test::XPATH_TEST_BLOCK_LENGTH     = "BLOCK_LENGTH";
const std::string Test::XPATH_TESTS_SETTINGS        = "NIST_STS_SETTINGS/TESTS_SETTINGS";
const std::string Test::XPATH_ATTRIBUTE_TEST_INDEX  = "test";

const std::string Test::PATH_MAIN_RESULT_DIR        = "experiments/AlgorithmTesting/";

const tTestInfo Test::INFO_FREQ                 { 1, "Frequency (monobits) test" , Test::PATH_MAIN_RESULT_DIR + "Frequency/", 1, false};
const tTestInfo Test::INFO_BLOCKFREQ            { 2, "Test For Frequency Within A Block" , Test::PATH_MAIN_RESULT_DIR + "BlockFrequency/", 1, true};
const tTestInfo Test::INFO_CUSUMS               { 3, "Cumulative Sum (Cusum) Test" , Test::PATH_MAIN_RESULT_DIR + "CumulativeSums/", 2, false};
const tTestInfo Test::INFO_RUNS                 { 4, "Runs Test" , Test::PATH_MAIN_RESULT_DIR + "Runs/", 1, false};
const tTestInfo Test::INFO_LONGESTRUN           { 5, "Test for the Longest Run of Ones in a Block" , Test::PATH_MAIN_RESULT_DIR + "LongestRun/", 1, false};
const tTestInfo Test::INFO_RANK                 { 6, "Random Binary Matrix Rank Test" , Test::PATH_MAIN_RESULT_DIR + "Rank/", 1, false};
const tTestInfo Test::INFO_FFT                  { 7, "Discrete Fourier Transform (Spectral) Test" , Test::PATH_MAIN_RESULT_DIR + "FFT/", 1, false};
const tTestInfo Test::INFO_NONOVERTEMP          { 8, "Non-overlapping (Aperiodic) Template Matching Test" ,
                                                  Test::PATH_MAIN_RESULT_DIR + "NonOverlappingTemplate/", 148, true};
const tTestInfo Test::INFO_OVERTEMP             { 9, "Overlapping (Periodic) Template Matching Test" , Test::PATH_MAIN_RESULT_DIR + "OverlappingTemplate/", 1, true};
const tTestInfo Test::INFO_UNIVERSAL            {10, "Maurer's Universal Statistical Test" , Test::PATH_MAIN_RESULT_DIR + "Universal/", 1, false};
const tTestInfo Test::INFO_APPROXENT            {11, "Approximate Entropy Test" , Test::PATH_MAIN_RESULT_DIR + "ApproximateEntropy/", 1, true};
const tTestInfo Test::INFO_RNDEXCURSIONS        {12, "Random Excursions Test" , Test::PATH_MAIN_RESULT_DIR + "RandomExcursions/", 8, false};
const tTestInfo Test::INFO_RNDEXCURSIONSVAR     {13, "Random Excursions Variant Test" , Test::PATH_MAIN_RESULT_DIR + "RandomExcursionsVariant/", 18, false};
const tTestInfo Test::INFO_SERIAL               {14, "Serial Test" , Test::PATH_MAIN_RESULT_DIR + "Serial/", 2, true};
const tTestInfo Test::INFO_LINEARCOMPLEXITY     {15, "Linear Complexity Test" , Test::PATH_MAIN_RESULT_DIR + "LinearComplexity/", 1, true};

std::unique_ptr<Test> Test::getInstance(int testIndex,
                                        const Globals & globals) {
    std::unique_ptr<Test> t (new Test());
    t->cliOptions = globals.getCliOptions();
    t->toolkitSettings = globals.getToolkitSettings();
    t->batteryConfiguration = globals.getBatteryConfiguration();

    t->battery = t->cliOptions->getBattery();
    t->objectInfo = Constants::batteryToString(t->battery) +
                       " - test " + Utils::itostr(testIndex);
    tTestInfo testInfo;

    if(testIndex == std::get<0>(INFO_FREQ))             testInfo = INFO_FREQ; else
    if(testIndex == std::get<0>(INFO_BLOCKFREQ))        testInfo = INFO_BLOCKFREQ; else
    if(testIndex == std::get<0>(INFO_CUSUMS))           testInfo = INFO_CUSUMS; else
    if(testIndex == std::get<0>(INFO_RUNS))             testInfo = INFO_RUNS; else
    if(testIndex == std::get<0>(INFO_LONGESTRUN))       testInfo = INFO_LONGESTRUN; else
    if(testIndex == std::get<0>(INFO_RANK))             testInfo = INFO_RANK; else
    if(testIndex == std::get<0>(INFO_FFT))              testInfo = INFO_FFT; else
    if(testIndex == std::get<0>(INFO_NONOVERTEMP))      testInfo = INFO_NONOVERTEMP; else
    if(testIndex == std::get<0>(INFO_OVERTEMP))         testInfo = INFO_OVERTEMP; else
    if(testIndex == std::get<0>(INFO_UNIVERSAL))        testInfo = INFO_UNIVERSAL; else
    if(testIndex == std::get<0>(INFO_APPROXENT))        testInfo = INFO_APPROXENT; else
    if(testIndex == std::get<0>(INFO_RNDEXCURSIONS))    testInfo = INFO_RNDEXCURSIONS; else
    if(testIndex == std::get<0>(INFO_RNDEXCURSIONSVAR)) testInfo = INFO_RNDEXCURSIONSVAR; else
    if(testIndex == std::get<0>(INFO_SERIAL))           testInfo = INFO_SERIAL; else
    if(testIndex == std::get<0>(INFO_LINEARCOMPLEXITY)) testInfo = INFO_LINEARCOMPLEXITY; else
        //throw std::runtime_error("unknown test constant in NIST STS: " + Utils::itostr(testIndex));
        throw RTTException(t->objectInfo , "unknown test constants");


    std::tie(t->testIndex ,
             t->logicName ,
             t->resultSubDir ,
             t->subTestCount ,
             t->adjustableBlockLen) = testInfo;

    /* Getting default values from XML */
    t->binaryDataPath = t->cliOptions->getBinFilePath();
    if(t->binaryDataPath.empty())
        raiseBugException("empty input binary data");
        //throw RTTException(t->objectInfo , "path to input data can't be empty");
        //throw std::runtime_error("path to input data can't be empty");
    t->executablePath = t->toolkitSettings->getBinaryBattery(t->battery);
    if(t->executablePath.empty())
        raiseBugException("empty executable binary");
                //throw RTTException(t->objectInfo , "tag " + XPATH_BINARY_PATH + " can't be empty");
        //throw std::runtime_error("tag " + XPATH_BINARY_PATH + " can't be empty");

    /* Getting test specific settings from XML */
//    TiXmlNode * testsSettingsNode = getXMLChildNodeWithAttValue(
//                    getXMLElement(globals , XPATH_TESTS_SETTINGS),
//                    XPATH_ATTRIBUTE_TEST_INDEX,
//                    Utils::itostr(t->testIndex)
//                );

//    t->streamSize = ITest::getTestOrDefOpt(globals , testsSettingsNode ,
//                                           XPATH_DEFAULT_STREAM_SIZE ,
//                                           XPATH_TEST_STREAM_SIZE);
//    t->streamCount = ITest::getTestOrDefOpt(globals , testsSettingsNode ,
//                                               XPATH_DEFAULT_STREAM_COUNT ,
//                                               XPATH_TEST_STREAM_COUNT);
//    t->blockLength = getXMLElementValue(testsSettingsNode ,
//                                           XPATH_TEST_BLOCK_LENGTH);

//    if(t->streamSize.empty()) {
//        throw RTTException(t->objectInfo , "stream size not set");
//        //throw std::runtime_error("tag " + XPATH_DEFAULT_STREAM_SIZE + " can't be empty"
//        //                         " without setting stream size in tests settings.");
//    }
//    if(t->streamCount.empty()) {
//        throw RTTException(t->objectInfo , "stream count not set");
//        //throw std::runtime_error("tag " + XPATH_DEFAULT_STREAM_COUNT + " can't be empty"
//        //                         " without setting stream count in tests settings.");
//    }
    t->streamSize = t->batteryConfiguration->getNiststsTestStreamSize(testIndex);
    if(t->streamSize.empty())
        t->streamSize = t->batteryConfiguration->getNiststsDefaultStreamSize();
    if(t->streamSize.empty())
        throw RTTException(t->objectInfo , "stream size not set");

    t->streamCount = t->batteryConfiguration->getNiststsTestStreamCount(testIndex);
    if(t->streamCount.empty())
        t->streamCount = t->batteryConfiguration->getNiststsDefaultStreamCount();
    if(t->streamCount.empty())
        throw RTTException(t->objectInfo , "stream count not set");

    t->blockLength = t->batteryConfiguration->getNiststsTestBlockLength(testIndex);

    return t;
}

void Test::appendTestLog(std::string & batteryLog) const {
    if(!executed)
        throw RTTException(objectInfo , "test wasn't executed, can't provide logs");
        //throw std::runtime_error("test " + Utils::itostr(static_cast<int>(testIndex)) + ""
        //                         " wasn't yet executed, can't provide test log");
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

        if(testIndex == std::get<0>(INFO_RNDEXCURSIONS) ||
           testIndex == std::get<0>(INFO_RNDEXCURSIONSVAR)) {
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


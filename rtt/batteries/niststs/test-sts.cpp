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

Test Test::getInstance(int testIndex,
                       TiXmlNode * cfgRoot,
                       const CliOptions &options) {
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
        throw std::runtime_error("unknown test constant in NIST STS: " + Utils::itostr(testIndex));

    Test test;

    std::tie(test.testIndex ,
             test.logicName ,
             test.resultSubDir ,
             test.subTestCount ,
             test.adjustableBlockLen) = testInfo;

    //test.testIndex = testIndex;
    /* Getting default values from XML */
    test.binaryDataPath = options.getBinFilePath();
    if(test.binaryDataPath.empty())
        throw std::runtime_error("path to input data can't be empty");
    test.executablePath = getXMLElementValue(cfgRoot , XPATH_BINARY_PATH);
    if(test.executablePath.empty())
        throw std::runtime_error("tag " + XPATH_BINARY_PATH + " can't be empty");

    /* Getting test specific settings from XML */
    TiXmlNode * testsSettingsNode = getXMLChildNodeWithAttValue(
                    getXMLElement(cfgRoot , XPATH_TESTS_SETTINGS),
                    XPATH_ATTRIBUTE_TEST_INDEX,
                    Utils::itostr(test.testIndex)
                );

    test.streamSize = TestUtils::getTestOrDefOpt(cfgRoot , testsSettingsNode ,
                                              XPATH_DEFAULT_STREAM_SIZE ,
                                              XPATH_TEST_STREAM_SIZE);
    test.streamCount = TestUtils::getTestOrDefOpt(cfgRoot , testsSettingsNode ,
                                               XPATH_DEFAULT_STREAM_COUNT ,
                                               XPATH_TEST_STREAM_COUNT);
    test.blockLength = getXMLElementValue(testsSettingsNode , XPATH_TEST_BLOCK_LENGTH);

    if(test.streamSize.empty()) {
        throw std::runtime_error("tag " + XPATH_DEFAULT_STREAM_SIZE + " can't be empty"
                                 " without setting stream size in tests settings.");
    }
    if(test.streamCount.empty()){
            throw std::runtime_error("tag " + XPATH_DEFAULT_STREAM_COUNT + " can't be empty"
                                     " without setting stream count in tests settings.");
    }

    return test;
}

void Test::appendTestLog(std::string & batteryLog) {
    if(!executed)
        throw std::runtime_error("test " + Utils::itostr(static_cast<int>(testIndex)) + ""
                                 " wasn't yet executed, can't provide test log");
    batteryLog.append(outputLog);
    batteryLog.append(testLog);
}

void Test::execute() {
    std::cout << "Executing test " << testIndex << " in battery "
              << Constants::batteryToString(Constants::BATTERY_NIST_STS) << std::endl;
    outputLog = TestUtils::executeBinary(executablePath ,
                                         createArgs() ,
                                         createInput());
    parseStoreResults();
    executed = true;
}

std::string Test::getLogicName() const {
    return logicName;
}

std::vector<std::string> Test::getSettings() const {
    std::stringstream parameters;
    parameters << "Stream size: " << streamSize << std::endl;
    parameters << "Stream count: " << streamCount << std::endl;
    if(!blockLength.empty() && adjustableBlockLen)
        parameters << "Block length: " << blockLength;

    return Utils::split(parameters.str() , '\n');
}

std::vector<tTestPvals> Test::getResults() const {
    if(!executed)
        throw std::runtime_error("can't return results before execution of test");

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
    arguments << "assess " << streamSize;
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

        if(pValCount % subTestCount != 0)
            throw std::runtime_error("can't extract p-values from log: number of"
                                     " p-value is not divisible by repetitions");
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


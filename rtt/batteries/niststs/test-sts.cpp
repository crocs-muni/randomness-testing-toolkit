#include "test-sts.h"

namespace rtt {
namespace batteries {
namespace niststs {

std::mutex outputFile_mux;

std::unique_ptr<Test> Test::getInstance(int testIndex,
                                        const GlobalContainer & container) {
    std::unique_ptr<Test> t (new Test(testIndex , container));

    std::tie(t->logicName ,
             t->resultSubDir,
             t->subTestCount,
             t->adjustableBlockLen) =
            TestConstants::getNistStsTestData(t->battery , t->testIndex);

    /* Stream size */
    t->streamSize = t->batteryConfiguration->getNiststsTestStreamSize(testIndex);
    if(t->streamSize.empty())
        t->streamSize = t->batteryConfiguration->getNiststsDefaultStreamSize();
    if(t->streamSize.empty())
        throw RTTException(t->objectInfo , Strings::TEST_ERR_STREAM_SIZE_NOT_SET);
    /* Count of streams */
    t->streamCount = t->batteryConfiguration->getNiststsTestStreamCount(testIndex);
    if(t->streamCount.empty())
        t->streamCount = t->batteryConfiguration->getNiststsDefaultStreamCount();
    if(t->streamCount.empty())
        throw RTTException(t->objectInfo , Strings::TEST_ERR_STREAM_COUNT_NOT_SET);
    /* Block length */
    t->blockLength = t->batteryConfiguration->getNiststsTestBlockLength(testIndex);

    return t;
}

void Test::execute() {
    /* This method is turned into thread.
     * Will deadlock if run without main thread. */

    /* Cleaning the test result directory */
    Utils::rmDirFiles(resultSubDir);
    //outputLog = TestRunner::executeBinary(logger, objectInfo, executablePath,
    //                                      createArgs(), createInput());
    batteryOutput = TestRunner::executeBinary(logger, objectInfo,
                                              executablePath, createArgs(), createInput());

    //outputLog = output.getStdOut();
    //outputLog.append(output.getStdErr());
    parseStoreResults();
    //auto errors = output.getErrors();
    //auto warnings = output.getWarnings();

    batteryOutput.doDetection();
    if(!batteryOutput.getStdErr().empty())
        logger->warn(objectInfo + ": execution of test produced error output. Inspect logs.");
    if(!batteryOutput.getErrors().empty())
        logger->warn(objectInfo + ": test output contains errors.");
    if(!batteryOutput.getWarnings().empty())
        logger->warn(objectInfo + ": test output contains warnings.");


    /* Store test output into file */
    std::unique_lock<std::mutex> outputFile_lock(outputFile_mux);
    Utils::appendStringToFile(logFilePath , batteryOutput.getStdOut());
    Utils::appendStringToFile(logFilePath , batteryOutput.getStdErr());
    outputFile_lock.unlock();

    executed = true;
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
        auto testLog = Utils::readFileToString(resultSubDir + "stats.txt");
        batteryOutput.appendStdOut(testLog);

        if(testIndex == 12 ||  /* Random excursions */
           testIndex == 13 ) { /* Random excursions variant */
            /* Random excursions tests are exceptions (of course they are)
             * p-values must be read directly from log and their count must
             * be divisible by subTestCount. Otherwise something happened. */
            static const std::regex RE_PVALUE {"p[\\-_]value = ([0|1]?\\.[0-9]+?)\\n"};
            auto begin = std::sregex_iterator(testLog.begin() , testLog.end() , RE_PVALUE);
            auto end = std::sregex_iterator();
            int pValCount = std::distance(begin , end);
            if(pValCount == 0) {
                logger->warn(objectInfo + Strings::TEST_ERR_NO_PVALS_EXTRACTED);
                streamCount = "0";
                return;
            }

            if(pValCount % subTestCount != 0) {
                logger->warn(objectInfo + Strings::TEST_ERR_PVALS_BAD_COUNT);
                return;
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

        /* Preppending output from test run to test run */
        //testLog = outputLog.append(testLog);
    } catch (std::runtime_error ex) {
        logger->warn(objectInfo + Strings::TEST_ERR_EXCEPTION_DURING_THREAD + ex.what());
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
            //throw std::runtime_error("file: " + fileName + " contains p-value"
            //                         "that is not in <0,1> interval");
            throw std::runtime_error(Strings::TEST_ERR_PVAL_OUTSIDE_INTERVAL + fileName);
        /* This silly condition is here for random excursions test */
        /* Because when you can't apply test it is feasible to give 0 as answer *rolls eyes* */
        if(pVal == 0 && (testIndex == 12 || testIndex == 13))
            continue;

        vecPval.push_back(pVal);
    }
    return vecPval;
}

} // namespace niststs
} // namespace batteries
} // namespace rtt

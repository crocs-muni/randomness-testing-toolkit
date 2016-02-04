#include "test-sts.h"

namespace rtt {
namespace batteries {
namespace niststs {

/* Constant definition */
const std::string Test::XPATH_BINARY_PATH =
        "NIST_STS_SETTINGS/BINARY_PATH";
const std::string Test::XPATH_OUTPUT_DIRECTORY =
        "NIST_STS_SETTINGS/DEFAULT_OUTPUT_DIRECTORY";
const std::string Test::XPATH_STREAM_SIZE_DEFAULT =
        "NIST_STS_SETTINGS/DEFAULT_STREAM_SIZE";
const std::string Test::XPATH_STREAM_COUNT_DEFAULT =
        "NIST_STS_SETTINGS/DEFAULT_STREAM_COUNT";
const std::string Test::XPATH_TESTS_SETTINGS =
        "NIST_STS_SETTINGS/TESTS_SETTINGS";
const std::string Test::XPATH_ATTRIBUTE_TEST_INDEX =
        "test";
const std::string Test::XPATH_NODE_STREAM_SIZE =
        "STREAM_SIZE";
const std::string Test::XPATH_NODE_STREAM_COUNT =
        "STREAM_COUNT";
const std::string Test::XPATH_NODE_BLOCK_LENGTH =
        "BLOCK_LENGTH";
const std::string Test::PATH_MAIN_RESULT_DIR =
        "experiments/AlgorithmTesting/";

Test Test::getInstance(TestIndex testIndex,
                       TiXmlNode * cfgRoot,
                       const std::string & binaryDataPath) {
    Test test;

    switch(testIndex) {
    case TestIndex::frequency: {
        test.logicName = "Frequency (monobits) test";
        test.resultSubDir = PATH_MAIN_RESULT_DIR + "Frequency/";
        test.subTestCount = 1;
        test.adjustableBlockLen = false;
        break;
    }
    case TestIndex::blockFrequency: {
        test.logicName = "Test For Frequency Within A Block";
        test.resultSubDir = PATH_MAIN_RESULT_DIR + "BlockFrequency/";
        test.subTestCount = 1;
        test.adjustableBlockLen = true;
        break;
    }
    case TestIndex::cumulativeSums: {
        test.logicName = "Cumulative Sum (Cusum) Test";
        test.resultSubDir = PATH_MAIN_RESULT_DIR + "CumulativeSums/";
        test.subTestCount = 2;
        test.adjustableBlockLen = false;
        break;
    }
    case TestIndex::runs: {
        test.logicName = "Runs Test";
        test.resultSubDir = PATH_MAIN_RESULT_DIR + "Runs/";
        test.subTestCount = 1;
        test.adjustableBlockLen = false;
        break;
    }
    case TestIndex::longestRun: {
        test.logicName = "Test for the Longest Run of Ones in a Block";
        test.resultSubDir = PATH_MAIN_RESULT_DIR + "LongestRun/";
        test.subTestCount = 1;
        test.adjustableBlockLen = false;
        break;
    }
    case TestIndex::rank: {
        test.logicName = "Random Binary Matrix Rank Test";
        test.resultSubDir = PATH_MAIN_RESULT_DIR + "Rank/";
        test.subTestCount = 1;
        test.adjustableBlockLen = false;
        break;
    }
    case TestIndex::fft: {
        test.logicName = "Discrete Fourier Transform (Spectral) Test";
        test.resultSubDir = PATH_MAIN_RESULT_DIR + "FFT/";
        test.subTestCount = 1;
        test.adjustableBlockLen = false;
        break;
    }
    case TestIndex::nonOverlappingTemplate: {
        test.logicName = "Non-overlapping (Aperiodic) Template Matching Test";
        test.resultSubDir = PATH_MAIN_RESULT_DIR + "NonOverlappingTemplate/";
        test.subTestCount = 148;
        test.adjustableBlockLen = true;
        break;
    }
    case TestIndex::overlappingTemplate: {
        test.logicName = "Overlapping (Periodic) Template Matching Test";
        test.resultSubDir = PATH_MAIN_RESULT_DIR + "OverlappingTemplate/";
        test.subTestCount = 1;
        test.adjustableBlockLen = true;
        break;
    }
    case TestIndex::universal: {
        test.logicName = "Maurer's Universal Statistical Test";
        test.resultSubDir = PATH_MAIN_RESULT_DIR + "Universal/";
        test.subTestCount = 1;
        test.adjustableBlockLen = false;
        break;
    }
    case TestIndex::approximateEntropy: {
        test.logicName = "Approximate Entropy Test";
        test.resultSubDir = PATH_MAIN_RESULT_DIR + "ApproximateEntropy/";
        test.subTestCount = 1;
        test.adjustableBlockLen = true;
        break;
    }
    case TestIndex::randomExcursions: {
        test.logicName = "Random Excursions Test";
        test.resultSubDir = PATH_MAIN_RESULT_DIR + "RandomExcursions/";
        test.subTestCount = 8;
        test.adjustableBlockLen = false;
        break;
    }
    case TestIndex::randomExcursionsVariant: {
        test.logicName = "Random Excursions Variant Test";
        test.resultSubDir = PATH_MAIN_RESULT_DIR + "RandomExcursionsVariant/";
        test.subTestCount = 18;
        test.adjustableBlockLen = false;
        break;
    }
    case TestIndex::serial: {
        test.logicName = "Serial Test";
        test.resultSubDir = PATH_MAIN_RESULT_DIR + "Serial/";
        test.subTestCount = 2;
        test.adjustableBlockLen = true;
        break;
    }
    case TestIndex::linearComplexity: {
        test.logicName = "Linear Complexity Test";
        test.resultSubDir = PATH_MAIN_RESULT_DIR + "LinearComplexity/";
        test.subTestCount = 1;
        test.adjustableBlockLen = true;
        break;
    }
    default: {
        throw std::runtime_error("unknown test testIndex in NIST STS battery: " +
                                             Utils::itostr(static_cast<int>(testIndex)));
    }
    }
    test.testIndex = testIndex;
    /* Getting default values from XML */
    test.binaryDataPath = binaryDataPath;
    if(test.binaryDataPath.empty())
        throw std::runtime_error("path to input data can't be empty");
    test.executablePath = getXMLElementValue(cfgRoot , XPATH_BINARY_PATH);
    if(test.executablePath.empty())
        throw std::runtime_error("tag " + XPATH_BINARY_PATH + " can't be empty");

    /* Getting test specific settings from XML */
    std::string streamSize;
    std::string streamCount;
    std::string blockLength;

    TiXmlNode * testsSettingsNode = getXMLElement(cfgRoot , XPATH_TESTS_SETTINGS);
    const char * testAttribute;

    if(testsSettingsNode && testsSettingsNode->FirstChild()) {
        TiXmlNode * settingsNode = testsSettingsNode->FirstChild();
        TiXmlElement * settingsElement;
        for( ; settingsNode ; settingsNode = settingsNode->NextSibling()) {
            settingsElement = settingsNode->ToElement();
            testAttribute = settingsElement->Attribute(XPATH_ATTRIBUTE_TEST_INDEX.c_str());
            if(!testAttribute)
                throw std::runtime_error("child of tag " + XPATH_TESTS_SETTINGS + "doesn't"
                                         " have attribute " + XPATH_ATTRIBUTE_TEST_INDEX);
            if(strlen(testAttribute) > 0 &&
               static_cast<int>(testIndex) == Utils::strtoi(testAttribute)) {
                /* I've got correct node, load settings from there */
                streamSize = getXMLElementValue(settingsNode , XPATH_NODE_STREAM_SIZE);
                streamCount = getXMLElementValue(settingsNode , XPATH_NODE_STREAM_COUNT);
                blockLength = getXMLElementValue(settingsNode , XPATH_NODE_BLOCK_LENGTH);
                break;
            }
        }
    }
    if(streamSize.empty()) {
        streamSize = getXMLElementValue(cfgRoot , XPATH_STREAM_SIZE_DEFAULT);
        if(streamSize.empty())
            throw std::runtime_error("tag " + XPATH_STREAM_SIZE_DEFAULT + " can't be empty"
                                     " without setting stream size in tests settings.");
    }
    if(streamCount.empty()){
        streamCount = getXMLElementValue(cfgRoot , XPATH_STREAM_COUNT_DEFAULT);
        if(streamCount.empty())
            throw std::runtime_error("tag " + XPATH_STREAM_COUNT_DEFAULT + " can't be empty"
                                     " without setting stream count in tests settings.");
    }
    test.streamSize = Utils::strtoi(streamSize);
    test.streamCount = Utils::strtoi(streamCount);
    if(!blockLength.empty() && test.adjustableBlockLen)
        test.blockLen.push_back(Utils::strtoi(blockLength));

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
    std::cout << "Executing test " << static_cast<int>(testIndex) << std::endl;
    int stdin_pipe[2];
    int stdout_pipe[2];
    int stderr_pipe[2];
    pid_t pid = 0;

    /* Creating pipes for redirected I/O of new process */
    posix_spawn_file_actions_t actions;
    if(pipe(stdin_pipe) || pipe(stdout_pipe) || pipe(stderr_pipe))
        throw std::runtime_error("pipe creation failed");
    /* Pipes will be mapped to I/O after process start */
    /* Unused ends are closed */
    posix_spawn_file_actions_init(&actions);
    posix_spawn_file_actions_addclose(&actions , stdin_pipe[1]);
    posix_spawn_file_actions_addclose(&actions , stdout_pipe[0]);
    posix_spawn_file_actions_addclose(&actions , stderr_pipe[0]);
    posix_spawn_file_actions_adddup2(&actions , stdin_pipe[0] , 0);
    posix_spawn_file_actions_addclose(&actions , stdin_pipe[0]);
    posix_spawn_file_actions_adddup2(&actions , stdout_pipe[1] , 1);
    posix_spawn_file_actions_addclose(&actions , stdout_pipe[1]);
    posix_spawn_file_actions_adddup2(&actions , stderr_pipe[1] , 2);
    posix_spawn_file_actions_addclose(&actions , stderr_pipe[1]);
    /* Creating cli arguments for executable */
    int argc = 0;
    char ** argv = buildArgv(&argc);
    /* Creating input that will be sent to exec */
    std::string input(buildInput());
    /* Executing binary */
    int status = posix_spawn(&pid , executablePath.c_str() ,
                             &actions , NULL , argv , environ);
    if(status == 0) {
        std::cout << "Started NIST STS process with pid: " << pid << std::endl;
        close(stdin_pipe[0]);
        close(stdout_pipe[1]);
        close(stderr_pipe[1]);
        write(stdin_pipe[1] , input.c_str() , input.length());
        /* Reading and storing output of battery */
        readPipes(stdout_pipe , stderr_pipe);
        /* Waiting for STS to end */
        if(waitpid(pid , &status , 0) != -1) {
            std::cout << "NIST STS exited with code: " << status << std::endl;
        } else {
            throw std::runtime_error("error when running NIST STS");
        }
    } else {
        throw std::runtime_error("error ocurred when starting NIST STS executable: " +
                                 static_cast<std::string>(strerror(status)));
    }
    posix_spawn_file_actions_destroy(&actions);
    destroyArgv(argc , argv);

    /* Battery successfuly finished calculation */
    /* Now it's time to parse and store the results */
    parseStoreResults();

    /* One last thing */
    /* Allows extraction of results */
    executed = true;
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

char ** Test::buildArgv(int * argc) const {
    /* NIST STS takes only 1 argument from cli */
    std::vector<std::string> vecArg = {"assess" , Utils::itostr(streamSize)};
    char ** argv = new char * [vecArg.size() + 1];
    for(size_t i = 0 ; i < vecArg.size() ; ++i) {
        argv[i] = new char [vecArg[i].length() + 1];
        strcpy(argv[i] , vecArg[i].c_str());
    }
    argv[vecArg.size()] = NULL;
    *argc = vecArg.size() + 1;
    return argv;
}

void Test::destroyArgv(int argc, char **argv) const {
    for(int i = 0 ; i < argc ; i++) {
        if(argv[i]) delete[] argv[i];
    }
    delete[] argv;
}

std::string Test::buildInput() const {
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
    tmp[static_cast<int>(testIndex) - 1] = '1';
    inputSequence << tmp << " ";
    /* Setting blocksize of a test */
    /* If it's not possible, this setting is ommited */
    if(adjustableBlockLen) {
        if(blockLen.empty()) {
            /* Not adjusting anything, just entering 0 */
            /* to continue */
            inputSequence << "0 ";
        } else {
            /* Adjusting the block size */
            /* Always ruuning just one test, its index is always 1 */
            inputSequence << "1 ";
            /* Entering actual value of new block size */
            inputSequence << blockLen[0] << " ";
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

void Test::readPipes(int *stdout_pipe, int *stderr_pipe) {
    std::string buffer(1024 , ' ');
    size_t bytes_read;
    std::vector<pollfd> pollVector = {{stdout_pipe[0] , POLLIN},
                                      {stderr_pipe[0] , POLLIN}};
    for( ; poll(&pollVector[0] , pollVector.size() , -1) > 0 ; ) {
        if (pollVector[0].revents&POLLIN) {
            bytes_read = read(stdout_pipe[0] , &buffer[0] , buffer.length());
            outputLog.append(buffer , 0 , bytes_read);
        }
        else if (pollVector[1].revents&POLLIN) {
            bytes_read = read(stderr_pipe[0] , &buffer[0] , buffer.length());
            outputLog.append(buffer , 0 , bytes_read);
        }
        else break; /* Reading done */
    }
}

void Test::parseStoreResults() {
    testLog = Utils::readFileToString(resultSubDir + "stats.txt");

    if(subTestCount == 1) {
        /* Only file results.txt will be processed */
        tTestPvals pVals = readPvals(resultSubDir + "results.txt");
        results.push_back(pVals);
    } else {
        /* Multiple dataX.txt files will be processed */
        std::stringstream fName;
        tTestPvals pVals;
        for(int i = 1 ; i < subTestCount ; ++i) {
            fName << resultSubDir << "data" << i << ".txt";
            pVals = std::move(readPvals(fName.str()));
            results.push_back(pVals);
            pVals.clear();
            fName.str("");fName.clear();
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
        pVal = Utils::strtof(strPval);
        if(pVal < 0 || pVal > 1)
            throw std::runtime_error("file: " + fileName + " contains p-value"
                                     "that is not in <0,1> interval");
        vecPval.push_back(pVal);
    }
    return vecPval;
}

} // namespace niststs
} // namespace batteries
} // namespace rtt


#include "rtt/batteries/dieharder/test-dh.h"

namespace rtt {
namespace batteries {
namespace dieharder {

const tTestInfo Test::INFO_BIRTHDAYS            {  0 , "Diehard Birthdays Test"};
const tTestInfo Test::INFO_OPERM5               {  1 , "Diehard OPERM5 Test"};
const tTestInfo Test::INFO_BINARYRANK1          {  2 , "Diehard 32x32 Binary Rank Test"};
const tTestInfo Test::INFO_BINARYRANK2          {  3 , "Diehard 6x8 Binary Rank Test"};
const tTestInfo Test::INFO_BITSTREAM            {  4 , "Diehard Bitstream Test"};
const tTestInfo Test::INFO_OPSO                 {  5 , "Diehard OPSO"};
const tTestInfo Test::INFO_OQSO                 {  6 , "Diehard OQSO Test"};
const tTestInfo Test::INFO_DNA                  {  7 , "Diehard DNA Test"};
const tTestInfo Test::INFO_COUNT1SBYTE          {  8 , "Diehard Count the 1s (stream) Test"};
const tTestInfo Test::INFO_COUNT1SSTREAM        {  9 , "Diehard Count the 1s Test (byte)"};
const tTestInfo Test::INFO_PARKING              { 10 , "Diehard Parking Lot Test"};
const tTestInfo Test::INFO_MINDISTANCECIRCLE    { 11 , "Diehard Minimum Distance (2d Circle) Test"};
const tTestInfo Test::INFO_MINDISTANCESPHERE    { 12 , "Diehard 3d Sphere (Minimum Distance) Test"};
const tTestInfo Test::INFO_SQUEEZE              { 13 , "Diehard Squeeze Test"};
const tTestInfo Test::INFO_SUMS                 { 14 , "Diehard Sums Test"};
const tTestInfo Test::INFO_RUNS                 { 15 , "Diehard Runs Test"};
const tTestInfo Test::INFO_CRAPS                { 16 , "Diehard Craps Test"};
const tTestInfo Test::INFO_GCD                  { 17 , "Marsaglia and Tsang GCD Test"};
const tTestInfo Test::INFO_MONOBIT              {100 , "STS Monobit Test"};
const tTestInfo Test::INFO_STSRUNS              {101 , "STS Runs Test"};
const tTestInfo Test::INFO_SERIAL               {102 , "STS Serial Test (Generalized)"};
const tTestInfo Test::INFO_BITDIST              {200 , "RGB Bit Distribution Test"};
const tTestInfo Test::INFO_MINDISTANCE          {201 , "RGB Generalized Minimum Distance Test"};
const tTestInfo Test::INFO_PERMUTATIONS         {202 , "RGB Permutations Test"};
const tTestInfo Test::INFO_LAGGED               {203 , "RGB Lagged Sum Test"};
const tTestInfo Test::INFO_KS                   {204 , "RGB Kolmogorov-Smirnov Test"};
const tTestInfo Test::INFO_BYTEDIST             {205 , "Byte Distribution"};
const tTestInfo Test::INFO_DABDCT               {206 , "DAB DCT"};
const tTestInfo Test::INFO_DABFILLTREE          {207 , "DAB Fill Tree Test"};
const tTestInfo Test::INFO_DABFILLTREE2         {208 , "DAB Fill Tree Test 2"};
const tTestInfo Test::INFO_DABMONOBIT           {209 , "DAB Monobit 2 Test"};

const std::string Test::XPATH_BINARY_PATH           = "DIEHARDER_SETTINGS/BINARY_PATH";
const std::string Test::XPATH_DEFAULT_ARGUMENTS     = "DIEHARDER_SETTINGS/DEFAULT_ARGUMENTS";
const std::string Test::XPATH_DEFAULT_PSAMPLES      = "DIEHARDER_SETTINGS/DEFAULT_PSAMPLES";
const std::string Test::XPATH_TESTS_SETTINGS        = "DIEHARDER_SETTINGS/TESTS_SETTINGS";
const std::string Test::XPATH_ATTRIBUTE_TEST_INDEX  = "test";
const std::string Test::XPATH_TEST_ARGUMENTS        = "ARGUMENTS";
const std::string Test::XPATH_TEST_PSAMPLES         = "PSAMPLES";

const int Test::OPTION_HEADER_FLAG      = 66047;
const int Test::OPTION_FILE_GENERATOR   = 201;

Test Test::getInstance(int testIndex ,
                        const CliOptions & options ,
                        TiXmlNode * cfgRoot) {
    Test test;
    tTestInfo testInfo;

    if(testIndex == INFO_BIRTHDAYS.first)           testInfo = INFO_BIRTHDAYS; else
    if(testIndex == INFO_OPERM5.first)              testInfo = INFO_OPERM5 ; else
    if(testIndex == INFO_BINARYRANK1.first)         testInfo = INFO_BINARYRANK1 ; else
    if(testIndex == INFO_BINARYRANK2.first)         testInfo = INFO_BINARYRANK2 ; else
    if(testIndex == INFO_BITSTREAM.first)           testInfo = INFO_BITSTREAM ; else
    if(testIndex == INFO_OPSO.first)                testInfo = INFO_OPSO ; else
    if(testIndex == INFO_OQSO.first)                testInfo = INFO_OQSO ; else
    if(testIndex == INFO_DNA.first)                 testInfo = INFO_DNA ; else
    if(testIndex == INFO_COUNT1SBYTE.first)         testInfo = INFO_COUNT1SBYTE ; else
    if(testIndex == INFO_COUNT1SSTREAM.first)       testInfo = INFO_COUNT1SSTREAM ; else
    if(testIndex == INFO_PARKING.first)             testInfo = INFO_PARKING ; else
    if(testIndex == INFO_MINDISTANCECIRCLE.first)   testInfo = INFO_MINDISTANCECIRCLE ; else
    if(testIndex == INFO_MINDISTANCESPHERE.first)   testInfo = INFO_MINDISTANCESPHERE ; else
    if(testIndex == INFO_SQUEEZE.first)             testInfo = INFO_SQUEEZE ; else
    if(testIndex == INFO_SUMS.first)                testInfo = INFO_SUMS ; else
    if(testIndex == INFO_RUNS.first)                testInfo = INFO_RUNS ; else
    if(testIndex == INFO_CRAPS.first)               testInfo = INFO_CRAPS ; else
    if(testIndex == INFO_GCD.first)                 testInfo = INFO_GCD ; else
    if(testIndex == INFO_MONOBIT.first)             testInfo = INFO_MONOBIT ; else
    if(testIndex == INFO_STSRUNS.first)             testInfo = INFO_STSRUNS ; else
    if(testIndex == INFO_SERIAL.first)              testInfo = INFO_SERIAL ; else
    if(testIndex == INFO_BITDIST.first)             testInfo = INFO_BITDIST ; else
    if(testIndex == INFO_MINDISTANCE.first)         testInfo = INFO_MINDISTANCE ; else
    if(testIndex == INFO_PERMUTATIONS.first)        testInfo = INFO_PERMUTATIONS ; else
    if(testIndex == INFO_LAGGED.first)              testInfo = INFO_LAGGED ; else
    if(testIndex == INFO_KS.first)                  testInfo = INFO_KS ; else
    if(testIndex == INFO_BYTEDIST.first)            testInfo = INFO_BYTEDIST ; else
    if(testIndex == INFO_DABDCT.first)              testInfo = INFO_DABDCT ; else
    if(testIndex == INFO_DABFILLTREE.first)         testInfo = INFO_DABFILLTREE ; else
    if(testIndex == INFO_DABFILLTREE2.first)        testInfo = INFO_DABFILLTREE2 ; else
    if(testIndex == INFO_DABMONOBIT.first)          testInfo = INFO_DABMONOBIT ; else
        throw std::runtime_error("unknown test testIndex "
                                 "in Dieharder battery: " + Utils::itostr(testIndex));

    test.logicName = testInfo.second;
    test.testIndex = testIndex;

    test.binaryDataPath = options.getBinFilePath();
    if(test.binaryDataPath.empty())
        throw std::runtime_error("path to input data can't be empty");

    /* Getting default values from XML */
    test.executablePath = getXMLElementValue(cfgRoot , XPATH_BINARY_PATH);
    if(test.executablePath.empty())
        throw std::runtime_error("tag " + XPATH_BINARY_PATH + " can't be empty");

    TiXmlNode * testSettingsNode = getXMLChildNodeWithAttValue(
                    getXMLElement(cfgRoot , XPATH_TESTS_SETTINGS) ,
                    XPATH_ATTRIBUTE_TEST_INDEX ,
                    Utils::itostr(testIndex)
                );

    /* Getting psamples option from config */
    std::string pSamplesStr = getXMLElementValue(testSettingsNode , XPATH_TEST_PSAMPLES);
    if(pSamplesStr.empty()) {
        pSamplesStr = getXMLElementValue(cfgRoot , XPATH_DEFAULT_PSAMPLES);
        if(pSamplesStr.empty())
            throw std::runtime_error("Test " + Utils::itostr(testIndex) +
                                     ": default or test specific p-sample count "
                                     "must be set");
    }
    test.pSampleCount = Utils::strtoi(pSamplesStr);

    /* Getting default Dieharder options from config */
    std::string defaultArguments = getXMLElementValue(cfgRoot , XPATH_DEFAULT_ARGUMENTS);
    /* Options are separated by space */
    defaultArguments.append(" ");

    defaultArguments.append(
                getXMLElementValue(testSettingsNode , XPATH_TEST_ARGUMENTS));

    std::vector<std::string> vecOptions =
                std::move(Utils::split(defaultArguments , ' '));
    if(vecOptions.size() % 2 != 0)
        throw std::runtime_error("invalid Dieharder settings format: each option must value");

    for(size_t i = 0 ; i < vecOptions.size() ; ++i) {
        Setting setting = Setting::getInstance(vecOptions[i] ,
                                               vecOptions[i + 1]);
        test.settings.push_back(std::move(setting));
        ++i;
    }

    return test;
}

void Test::appendTestLog(std::string & batteryLog) {
    if(!executed)
        throw std::runtime_error("test " + Utils::itostr(testIndex) + " wasn't yet "
                                 "executed, can't provide test log");
    batteryLog.append(testLog);
}

void Test::execute() {
    std::cout << "Starting execution of Dieharder test "
              << static_cast<int>(testIndex) << std::endl;

    /* Creating pipes for redirecting battery output */
    int stdout_pipe[2];
    int stderr_pipe[2];
    if(pipe(stdout_pipe) || pipe(stderr_pipe))
            throw std::runtime_error("pipe creation failed");
    /* Setting process actions. At the beginning, stdout and stderr */
    /* are mapped to pipes and unused ends are closed. Then I can */
    /* inspect battery output in this process. */
    posix_spawn_file_actions_t actions;
    posix_spawn_file_actions_init(&actions);
    posix_spawn_file_actions_addclose(&actions , stdout_pipe[0]);
    posix_spawn_file_actions_addclose(&actions , stderr_pipe[0]);
    posix_spawn_file_actions_adddup2(&actions , stdout_pipe[1] , 1);
    posix_spawn_file_actions_addclose(&actions , stdout_pipe[1]);
    posix_spawn_file_actions_adddup2(&actions , stderr_pipe[1] , 2);
    posix_spawn_file_actions_addclose(&actions , stderr_pipe[1]);

    int argc = 0;
    char ** argv = buildArgv(&argc);
    pid_t pid = 0;
    int status = posix_spawn(&pid , executablePath.c_str() ,
                             &actions , NULL , argv , environ);
    if(status == 0) {
        std::cout << "Started Dieharder process with pid: " << pid << std::endl;
        close(stdout_pipe[1]);
        close(stderr_pipe[1]);
        /* Read and store battery output. */
        /* Later, the pvalues will be extracted */
        readPipes(stdout_pipe , stderr_pipe);
        if(waitpid(pid , &status , 0) != -1)
            std::cout << "Dieharder exited with status: " << status << std::endl;
        else
            throw std::runtime_error("error when running Dieharder");
    } else {
        throw std::runtime_error("error occured when starting Dieharder: " +
                                             (std::string)strerror(status));
    }
    posix_spawn_file_actions_destroy(&actions);
    destroyArgv(argc , argv);

    /* Battery successfuly finished computation */
    /* Resulting pvalues are extracted from stored battery output */
    extractPvalues();

    /* Allowing work with results */
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
    std::stringstream tmpss;
    tmpss << "dieharder ";
    /* Dieharder can receive single option multiple times and */
    /* will take only the last one. Therefore, first are passed */
    /* default values from config, then there are test specific */
    /* value that override default ones and lastly, options that */
    /* MUST be set for correct battery functionality are entered. */
    for(const auto & it : settings) {
        it.getConsoleInput(tmpss);
        tmpss << " ";
    }
    /* Set psample count */
    tmpss << "-p " << pSampleCount << " ";
    /* Specify test */
    tmpss << "-d " << testIndex << " ";
    /* Specify header flag */
    tmpss << "-D " << OPTION_HEADER_FLAG << " ";
    /* Specify binary file generator */
    tmpss << "-g " << OPTION_FILE_GENERATOR << " ";
    /* Specify binary input file */
    tmpss << "-f " << binaryDataPath;
    std::cout << tmpss.str() << std::endl;
    std::vector<std::string> vecArg = Utils::split(tmpss.str() , ' ');

    char ** argv = new char * [vecArg.size() + 1];
    for(size_t i = 0 ; i < vecArg.size() ; ++i) {
        argv[i] = new char [vecArg[i].length() + 1];
        strcpy(argv[i] , vecArg[i].c_str());
    }
    argv[vecArg.size()] = NULL;
    *argc = vecArg.size() + 1;
    return argv;
}

void Test::destroyArgv(int argc, char ** argv) const {
    for(int i = 0 ; i < argc ; i++) {
        if(argv[i]) delete[] argv[i];
    }
    delete[] argv;
}

void Test::readPipes(int * stdout_pipe, int * stderr_pipe) {
    std::string buffer(1024 , ' ');
    size_t bytes_read;
    std::vector<pollfd> pollVector = {{stdout_pipe[0] , POLLIN},
                                      {stderr_pipe[0] , POLLIN}};
    for( ; poll(&pollVector[0] , pollVector.size() , -1) > 0 ; ) {
        if (pollVector[0].revents&POLLIN) {
            bytes_read = read(stdout_pipe[0] , &buffer[0] , buffer.length());
            testLog.append(buffer , 0 , bytes_read);
        }
        else if (pollVector[1].revents&POLLIN) {
            bytes_read = read(stderr_pipe[0] , &buffer[0] , buffer.length());
            testLog.append(buffer , 0 , bytes_read);
        }
        else break; /* Reading done */
    }
}

void Test::extractPvalues() {
    static const std::regex RE_PSAMPLE_VALUE {"\\+\\+\\+\\+(0\\.[0-9]+?)\\+\\+\\+\\+\\n"};

    auto begin = std::sregex_iterator(testLog.begin() , testLog.end() ,
                                      RE_PSAMPLE_VALUE);
    auto end = std::sregex_iterator();

    int pValCount = std::distance(begin , end);
    if(pValCount == 0) {
        std::cout << "[WARNING] No pValues were extracted" << std::endl;
        return;
    }

    if(pValCount % pSampleCount != 0)
        throw std::runtime_error("can't extract pvalues from log: count of pvalues"
                                 " is not divisible by count of p-samples");
    subTestsCount = pValCount / pSampleCount;
    tTestPvals pSamples;

    for(int subTestIndex = 0 ; subTestIndex < subTestsCount ; ++subTestIndex) {
        for(int i = 0 ; i < pSampleCount ; ++i) {
            std::smatch match = *begin;
            pSamples.push_back(Utils::strtof(match[1].str()));
            ++begin;
        }
        results.push_back(std::move(pSamples));
        pSamples.clear();
    }
}

} // namespace dieharder
} // namespace batteries
} // namespace rtt


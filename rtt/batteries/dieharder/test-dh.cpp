#include "rtt/batteries/dieharder/test-dh.h"

namespace rtt {
namespace batteries {
namespace dieharder {

const std::string Test::XPATH_BINARY_PATH =
        "DIEHARDER_SETTINGS/BINARY_PATH";
const std::string Test::XPATH_DEFAULT_OPTIONS =
        "DIEHARDER_SETTINGS/DEFAULT_OPTIONS";
const std::string Test::XPATH_TESTS_SETTINGS =
        "DIEHARDER_SETTINGS/TESTS_SETTINGS";
const std::string Test::XPATH_ATTRIBUTE_TEST_INDEX =
        "test";
const int Test::OPTION_HEADER_FLAG = 66047;
const int Test::OPTION_FILE_GENERATOR = 201;


/* NUMBER OF TESTS MUST BE YET INSPECTED!!!!!!!!! */
/* NUMBER OF TESTS MUST BE YET INSPECTED!!!!!!!!! */
/* NUMBER OF TESTS MUST BE YET INSPECTED!!!!!!!!! */
/* NUMBER OF TESTS MUST BE YET INSPECTED!!!!!!!!! */
/* NUMBER OF TESTS MUST BE YET INSPECTED!!!!!!!!! */
/* NUMBER OF TESTS MUST BE YET INSPECTED!!!!!!!!! */
/* NUMBER OF TESTS MUST BE YET INSPECTED!!!!!!!!! */
/* NUMBER OF TESTS MUST BE YET INSPECTED!!!!!!!!! */
/* NUMBER OF TESTS MUST BE YET INSPECTED!!!!!!!!! */
/* NUMBER OF TESTS MUST BE YET INSPECTED!!!!!!!!! */
/* NUMBER OF TESTS MUST BE YET INSPECTED!!!!!!!!! */
/* NUMBER OF TESTS MUST BE YET INSPECTED!!!!!!!!! */
/* NUMBER OF TESTS MUST BE YET INSPECTED!!!!!!!!! */
/* NUMBER OF TESTS MUST BE YET INSPECTED!!!!!!!!! */
/* NUMBER OF TESTS MUST BE YET INSPECTED!!!!!!!!! */
/* NUMBER OF TESTS MUST BE YET INSPECTED!!!!!!!!! */
/* NUMBER OF TESTS MUST BE YET INSPECTED!!!!!!!!! */
/* NUMBER OF TESTS MUST BE YET INSPECTED!!!!!!!!! */
/* NUMBER OF TESTS MUST BE YET INSPECTED!!!!!!!!! */
/* NUMBER OF TESTS MUST BE YET INSPECTED!!!!!!!!! */
/* NUMBER OF TESTS MUST BE YET INSPECTED!!!!!!!!! */
/* NUMBER OF TESTS MUST BE YET INSPECTED!!!!!!!!! */
/* NUMBER OF TESTS MUST BE YET INSPECTED!!!!!!!!! */
/* NUMBER OF TESTS MUST BE YET INSPECTED!!!!!!!!! */
/* NUMBER OF TESTS MUST BE YET INSPECTED!!!!!!!!! */
/* NUMBER OF TESTS MUST BE YET INSPECTED!!!!!!!!! */
/* NUMBER OF TESTS MUST BE YET INSPECTED!!!!!!!!! */
/* NUMBER OF TESTS MUST BE YET INSPECTED!!!!!!!!! */
/* NUMBER OF TESTS MUST BE YET INSPECTED!!!!!!!!! */
/* NUMBER OF TESTS MUST BE YET INSPECTED!!!!!!!!! */
Test Test::getInstance(TestIndex testIndex,
                       TiXmlNode * cfgRoot,
                       const std::string &binaryDataPath) {
    Test test;
    switch(testIndex) {
    case TestIndex::birthdays: {
        test.logicName = "Diehard Birthdays Test";
        test.subTestsCount = 1;
        break;
    }
    case TestIndex::operm5: {
        test.logicName = "Diehard OPERM5 Test";
        test.subTestsCount = 1;
        break;
    }
    case TestIndex::binaryrank1: {
        test.logicName = "Diehard 32x32 Binary Rank Test";
        test.subTestsCount = 1;
        break;
    }
    case TestIndex::binaryrank2: {
        test.logicName = "Diehard 6x8 Binary Rank Test";
        test.subTestsCount = 1;
        break;
    }
    case TestIndex::bitstream: {
        test.logicName = "Diehard Bitstream Test";
        test.subTestsCount = 1;
        break;
    }
    case TestIndex::opso: {
        test.logicName = "Diehard OPSO";
        test.subTestsCount = 1;
        break;
    }
    case TestIndex::oqso: {
        test.logicName = "Diehard OQSO Test";
        test.subTestsCount = 1;
        break;
    }
    case TestIndex::dna: {
        test.logicName = "Diehard DNA Test";
        test.subTestsCount = 1;
        break;
    }
    case TestIndex::count1sbyte: {
        test.logicName = "Diehard Count the 1s (stream) Test";
        test.subTestsCount = 1;
        break;
    }
    case TestIndex::count1sstream: {
        test.logicName = "Diehard Count the 1s Test (byte)";
        test.subTestsCount = 1;
        break;
    }
    case TestIndex::parking: {
        test.logicName = "Diehard Parking Lot Test";
        test.subTestsCount = 1;
        break;
    }
    case TestIndex::mindistancecircle: {
        test.logicName = "Diehard Minimum Distance (2d Circle) Test";
        test.subTestsCount = 1;
        break;
    }
    case TestIndex::mindistancesphere: {
        test.logicName = "Diehard 3d Sphere (Minimum Distance) Test";
        test.subTestsCount = 1;
        break;
    }
    case TestIndex::squeeze: {
        test.logicName = "Diehard Squeeze Test";
        test.subTestsCount = 1;
        break;
    }
    case TestIndex::sums: {
        test.logicName = "Diehard Sums Test";
        test.subTestsCount = 1;
        break;
    }
    case TestIndex::runs: {
        test.logicName = "Diehard Runs Test";
        test.subTestsCount = 2;
        break;
    }
    case TestIndex::craps: {
        test.logicName = "Diehard Craps Test";
        test.subTestsCount = 2;
        break;
    }
    case TestIndex::gcd: {
        test.logicName = "Marsaglia and Tsang GCD Test";
        test.subTestsCount = 2;
        break;
    }
    case TestIndex::monobit: {
        test.logicName = "STS Monobit Test";
        test.subTestsCount = 1;
        break;
    }
    case TestIndex::stsruns: {
        test.logicName = "STS Runs Test";
        test.subTestsCount = 1;
        break;
    }
    case TestIndex::serial: {
        test.logicName = "STS Serial Test (Generalized)";
        test.subTestsCount = 30;
        break;
    }
    case TestIndex::bitdist: {
        test.logicName = "RGB Bit Distribution Test";
        test.subTestsCount = 1;
        break;
    }
    case TestIndex::mindistance: {
        test.logicName = "RGB Generalized Minimum Distance Test";
        test.subTestsCount = 1;
        break;
    }
    case TestIndex::permutations: {
        test.logicName = "RGB Permutations Test";
        test.subTestsCount = 1;
        break;
    }
    case TestIndex::lagged: {
        test.logicName = "RGB Lagged Sum Test";
        test.subTestsCount = 1;
        break;
    }
    case TestIndex::ks: {
        test.logicName = "RGB Kolmogorov-Smirnov Test Test";
        test.subTestsCount = 1;
        break;
    }
    case TestIndex::bytedist: {
        test.logicName = "Byte Distribution";
        test.subTestsCount = 1;
        break;
    }
    case TestIndex::dabdct: {
        test.logicName = "DAB DCT";
        test.subTestsCount = 1;
        break;
    }
    case TestIndex::dabfilltree: {
        test.logicName = "DAB Fill Tree Test";
        test.subTestsCount = 2;
        break;
    }
    case TestIndex::dabfilltree2: {
        test.logicName = "DAB Fill Tree Test 2";
        test.subTestsCount = 2;
        break;
    }
    case TestIndex::dabmonobit: {
        test.logicName = "DAB Monobit 2 Test";
        test.subTestsCount = 1;
        break;
    }
    default: {
        throw std::runtime_error("unknown test testIndex in Dieharder battery: " +
                                             Utils::itostr(static_cast<int>(testIndex)));
    }
    }
    test.testConst = testIndex;
    /* Getting default values from XML */
    test.binaryDataPath = binaryDataPath;
    if(test.binaryDataPath.empty())
        throw std::runtime_error("path to input data can't be empty");
    test.executablePath = getXMLElementValue(cfgRoot , XPATH_BINARY_PATH);
    if(test.executablePath.empty())
        throw std::runtime_error("tag " + XPATH_BINARY_PATH + " can't be empty");

    /* Getting default Dieharder options from config */
    std::string defaultOptions = getXMLElementValue(cfgRoot , XPATH_DEFAULT_OPTIONS);
    /* Options are separated by space */
    defaultOptions.append(" ");

    TiXmlNode * testsSettingsNode = getXMLElement(cfgRoot , XPATH_TESTS_SETTINGS);
    const char * testAttribute;
    const char * settingValue;

    if(testsSettingsNode && testsSettingsNode->FirstChild()) {
        TiXmlElement * settingsElement =
                testsSettingsNode->FirstChildElement();
        for( ; settingsElement ; settingsElement = settingsElement->NextSiblingElement()) {
            testAttribute = settingsElement->Attribute(XPATH_ATTRIBUTE_TEST_INDEX.c_str());
            if(!testAttribute)
                throw std::runtime_error("child of tag " + XPATH_TESTS_SETTINGS + "doesn't"
                                         " have attribute " + XPATH_ATTRIBUTE_TEST_INDEX);
            if(strlen(testAttribute) > 0 &&
               static_cast<int>(testIndex) == Utils::strtoi(testAttribute)) {
                settingValue = settingsElement->GetText();
                if(settingValue && strlen(settingValue) > 0) {
                    defaultOptions.append(settingValue);
                }
                break;
            }
        }
    }

    std::vector<std::string> vecOptions =
                std::move(Utils::split(defaultOptions , ' '));
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

void Test::execute() {
    std::cout << "Starting execution of Dieharder test "
              << static_cast<int>(testConst) << std::endl;

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

    /* Battery successfuly finished calculation */
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
    /* Specify test */
    tmpss << "-d " << static_cast<int>(testConst) << " ";
    /* Specify header flag */
    tmpss << "-D " << OPTION_HEADER_FLAG << " ";
    /* Specify binary file generator */
    tmpss << "-g " << OPTION_FILE_GENERATOR << " ";
    /* Specify binary input file */
    tmpss << "-f " << binaryDataPath;
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
    std::regex RE_PSAMPLE_VALUE {"\\+\\+\\+\\+(0\\.[0-9]+?)\\+\\+\\+\\+"};

    auto begin = std::sregex_iterator(testLog.begin() , testLog.end() ,
                                      RE_PSAMPLE_VALUE);
    auto end = std::sregex_iterator();

    int pValCount = std::distance(begin , end);
    if(pValCount == 0) {
        std::cout << "[WARNING] No pValues were extracted" << std::endl;
        return;
    }

    if(pValCount % subTestsCount != 0)
        throw std::runtime_error("can't extract pvalues from log: number of pvalues"
                                 " is not divisible by count of subtests");
    int pSamplesCount = pValCount / subTestsCount;
    testPvals pSamples;

    for(int subTestIndex = 0 ; subTestIndex < subTestsCount ; ++subTestIndex) {
        for(int k = 0 ; k < pSamplesCount ; ++k) {
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


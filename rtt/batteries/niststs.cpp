#include "rtt/batteries/niststs.h"

namespace rtt {
namespace batteries {

/* Constant definition */
const std::string NistSts::XPATH_BINARY_PATH =
        "NIST_STS_SETTINGS/BINARY_PATH";
const std::string NistSts::XPATH_OUTPUT_FILE =
        "NIST_STS_SETTINGS/DEFAULT_OUTPUT_FILE";
const std::string NistSts::XPATH_STREAM_SIZE =
        "NIST_STS_SETTINGS/STREAM_SIZE";
const std::string NistSts::XPATH_STREAM_COUNT =
        "NIST_STS_SETTINGS/STREAM_COUNT";
const std::string NistSts::XPATH_PAR_ADJUST =
        "NIST_STS_SETTINGS/PARAMETER_ADJUSTMENTS";
const std::string NistSts::XPATH_PAR_ADJUST_ATT =
        "test";

void NistSts::initBattery(const CliOptions & options) {
    validateTestConsts(options.getTestConsts());
    testsVector = createTestsVector(options.getTestConsts());

    binFilePath = options.getBinFilePath();
    outFilePath = options.getOutFilePath();

    TiXmlNode * cfgRoot = NULL;
    loadXMLFile(cfgRoot , options.getInputCfgPath());

    if(outFilePath.empty())
        outFilePath = getXMLElementValue(cfgRoot , XPATH_OUTPUT_FILE);
    nistStsBinPath = getXMLElementValue(cfgRoot , XPATH_BINARY_PATH);
    streamSize = Utils::strtoi(getXMLElementValue(cfgRoot , XPATH_STREAM_SIZE));
    streamCount = Utils::strtoi(getXMLElementValue(cfgRoot , XPATH_STREAM_COUNT));

    if(outFilePath.empty())
        throw std::runtime_error("XML tag " + XPATH_OUTPUT_FILE + " can't be empty");
    if(nistStsBinPath.empty())
        throw std::runtime_error("XML tag " + XPATH_BINARY_PATH + "can't be empty");
    loadAdjustedParameters(cfgRoot);
    delete cfgRoot;
}

void NistSts::runTests() {
    std::cout << "Starting execution of NIST STS tests." << std::endl;
    int stdin_pipe[2];
    int stdout_pipe[2];
    int stderr_pipe[2];
    pid_t pid = 0;
    int argc = 0;

    posix_spawn_file_actions_t actions =
            createFileActions(stdin_pipe , stdout_pipe , stderr_pipe);
    char ** argv = buildArgs(&argc);
    std::string inputSeq = createInputSequence();
    int status = posix_spawn(&pid , nistStsBinPath.c_str() ,
                             &actions , NULL , argv , environ);
    if(status == 0) {
        std::cout << "Started NIST STS process with pid: " << pid << std::endl;
        close(stdin_pipe[0]);
        close(stdout_pipe[1]);
        close(stderr_pipe[1]);
        // Setting up NIST STS via CLI
        write(stdin_pipe[1] , inputSeq.c_str() , inputSeq.length());
        // Reading and storing NIST STS output
        readPipes(stdout_pipe , stderr_pipe);
        if(waitpid(pid , &status , 0) != -1) {
            std::cout << "NIST STS exited with status: " << status << std::endl;
        }
        else {
            throw std::runtime_error("error when running NIST STS");
        }
    }
    else {
        throw std::runtime_error("error occred when starting NIST STS: " +
                                 (std::string)strerror(status));
    }
    posix_spawn_file_actions_destroy(&actions);
    destroyArgs(argc , argv);
}

std::string NistSts::createTestsVector(const std::vector<int> & tests) {
    std::string tv(15 , '0');
    for(size_t i = 0 ; i < tests.size() ; i++)
        tv[tests[i] - 1] = '1';
    return tv;
}

void NistSts::processStoredResults() {
    // Prints nistOutput on cout
    // Only for testing
    std::cout << nistOutput << std::endl;
}

/*
================================================================
****************** Private methods below ***********************
================================================================
*/

void NistSts::loadAdjustedParameters(TiXmlNode * root) {
    std::pair<int , int> singleTag;
    const char * attributeValue = 0;
    const char * tagValue = 0;

    TiXmlNode * parentNode = getXMLElement(root , XPATH_PAR_ADJUST);
    TiXmlElement * childElement;
    if(!parentNode)
        return; // No parent, no fun (???)

    if(parentNode->FirstChild()) {
        childElement = parentNode->FirstChildElement();
        for(; childElement != NULL ; childElement = childElement->NextSiblingElement()) {
            attributeValue = childElement->Attribute(XPATH_PAR_ADJUST_ATT.c_str());
            if(!attributeValue)
                throw std::runtime_error("child of tag " + XPATH_PAR_ADJUST +
                                         " doesn't have attribute " + XPATH_PAR_ADJUST_ATT);
            tagValue = childElement->GetText();
            if(strlen(attributeValue) > 0 && tagValue != NULL) {
                adjParValidator(Utils::strtoi(attributeValue)); // valid test number check
                singleTag.first = Utils::strtoi(attributeValue);
                singleTag.second = Utils::strtoi(tagValue);
                adjustedParameters.push_back(singleTag);
            }
        }
        Utils::sort2D(adjustedParameters);
        // Delete adjustments that won't be used
        for(size_t i = 0 ; i < adjustedParameters.size() ; i++) {
            if(testsVector[adjustedParameters[i].first - 1] == '0') {
                adjustedParameters.erase(adjustedParameters.begin() + i);
                i--;
            }
        }
    }
}



void NistSts::adjParValidator(int testNum) {
    if(testNum == 2 || testNum == 8 || testNum == 9 ||
            testNum == 11 || testNum == 14 || testNum == 15)
        return;
    throw std::runtime_error("parameters of test " +
                             Utils::itostr(testNum) + " can't be adjusted");
}

void NistSts::validateTestConsts(const std::vector<int> & tests) {
    for(size_t i = 0 ; i < tests.size() ; i++) {
        if(tests[i] < 1 || tests[i] > 15)
            throw std::runtime_error("test number " + Utils::itostr(tests[i]) +
                                     " doesn't exist in NIST STS battery");
    }
}

posix_spawn_file_actions_t NistSts::createFileActions(
        int *stdin_pipe, int *stdout_pipe, int *stderr_pipe){
    if(pipe(stdin_pipe) || pipe(stdout_pipe) || pipe(stderr_pipe))
        throw std::runtime_error("pipe creation failed");
    posix_spawn_file_actions_t actions;
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

    return actions;
}

void NistSts::readPipes(int * stdout_pipe , int * stderr_pipe) {
    std::string buffer(1024 , ' ');
    size_t bytes_read;
    std::vector<pollfd> pollVector = {{stdout_pipe[0] , POLLIN},
                                      {stderr_pipe[0] , POLLIN}};
    for( ; poll(&pollVector[0] , pollVector.size() , -1) > 0 ; ) {
        if (pollVector[0].revents&POLLIN) {
            bytes_read = read(stdout_pipe[0] , &buffer[0] , buffer.length());
            nistOutput.append(buffer , 0 , bytes_read);
        }
        else if (pollVector[1].revents&POLLIN) {
            bytes_read = read(stderr_pipe[0] , &buffer[0] , buffer.length());
            nistOutput.append(buffer , 0 , bytes_read);
        }
        else break; // Reading done
    }
}

std::string NistSts::createInputSequence() {
    /*
     * Yes, I agree, this is totally disgusting. But don't blame me,
     * blame the guy at NIST, who designed interface of the battery.
     * The interface that almost actively defends itself against any
     * form of automatization. With horrible interface comes horrible
     * solution. Lubo.
     */
    std::stringstream inputSequence;
    // input file generator
    inputSequence << "0 ";
    // input file path
    inputSequence << binFilePath << " ";
    // NO to executing all tests at once
    inputSequence << "0 ";
    // specifying tests that will be executed
    inputSequence << testsVector << " ";
    // adjusting parameters of tests
    for(size_t i = 0 ; i < adjustedParameters.size() ; i++) {
        // indexing test to adjust
        inputSequence << i + 1 << " ";
        // entering new value
        inputSequence << adjustedParameters[i].second << " ";
    }
    // end of parameter adjustment
    inputSequence << "0 ";
    // stream count setting
    inputSequence << streamCount << " ";
    // input file type -> binary, newline ends input
    inputSequence << "1\n";
    return inputSequence.str();
}

char ** NistSts::buildArgs(int * argc) {
    std::stringstream argSs;
    argSs << "assess " << Utils::itostr(streamSize);
    std::vector<std::string> argVector = Utils::split(argSs.str() , ' ');
    char ** args = new char * [argVector.size() + 1];
    for(unsigned i = 0 ; i < argVector.size() ; i++) {
        // Manual allocation... *shudders*
        args[i] = new char [argVector[i].length() + 1];
        strcpy(args[i] , argVector[i].c_str());
    }
    args[argVector.size()] = NULL;
    *argc = argVector.size() + 1;
    return args;
}

void NistSts::destroyArgs(int argc , char ** argv) {
    for(int i = 0 ; i < argc ; i++) {
        if(argv[i]) delete[] argv[i];
    }
    delete[] argv;
}

} // namespace batteries
} // namespace rtt

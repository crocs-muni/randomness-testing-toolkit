#include "TestU01Battery.h"

/* Constant definition */
const std::string TestU01Battery::XPATH_BINARY_PATH =
        "TESTU01_SETTINGS/BINARY_PATH";
const std::string TestU01Battery::XPATH_OUTPUT_FILE =
        "TESTU01_SETTINGS/DEFAULT_OUTPUT_FILE";
const std::string TestU01Battery::XPATH_REPETITIONS =
        "TESTU01_SETTINGS/REPETITIONS";

void TestU01Battery::initBattery(const ToolkitOptions &options) {
    tests = options.getTestConsts();
    binFilePath = options.getBinFilePath();
    outFilePath = options.getOutFilePath();

    TiXmlNode * cfgRoot = NULL;
    loadXMLFile(cfgRoot , options.getInputCfgPath());

    if(outFilePath.empty())
        outFilePath = getXMLElementValue(cfgRoot , XPATH_OUTPUT_FILE);
    tu01Path = getXMLElementValue(cfgRoot , XPATH_BINARY_PATH);
    repetitions = Utils::strtoi(getXMLElementValue(cfgRoot , XPATH_REPETITIONS));

    if(outFilePath.empty())
        throw std::runtime_error("XML tag " + XPATH_OUTPUT_FILE + " can't be empty");
    if(tu01Path.empty())
        throw std::runtime_error("XML tag " + XPATH_BINARY_PATH + " can't be empty");
    if(repetitions == -1)
        throw std::runtime_error("XML tag " + XPATH_REPETITIONS + "can't be empty");
    delete cfgRoot;
}

void TestU01Battery::runTests() {
    std::cout << "Starting execution of TestU01 tests." << std::endl;
    for(unsigned i = 0 ; i < tests.size() ; i++) {
        int stdout_pipe[2];
        int stderr_pipe[2];
        pid_t pid = 0;
        int argc = 0;

        posix_spawn_file_actions_t actions =
                createFileActions(stdout_pipe , stderr_pipe);
        char ** argv = buildArgs(tests[i] , &argc);
        int status = posix_spawn(&pid , tu01Path.c_str() ,
                                 &actions , NULL , argv , environ);
        if(status == 0) {
            std::cout << "Started TestU01 process with pid: " << pid << std::endl;
            close(stdout_pipe[1]);
            close(stderr_pipe[1]);
            /* Reading and storing TestU01 output */
            readPipes(stdout_pipe , stderr_pipe);
            if(waitpid(pid , &status , 0) != -1)
                std::cout << "TestU01 exited with status: " << status << std::endl;
            else
                throw std::runtime_error("error when running TestU01");
        } else {
            throw std::runtime_error("error occurred when starting TestU01: " +
                                     (std::string)strerror(status));
        }
        posix_spawn_file_actions_destroy(&actions);
        destroyArgs(argc , argv);
    }
}

void TestU01Battery::processStoredResults() {
    /* This prints stored results => testing */
    for(size_t i = 0 ; i < storedResults.size() ; i++) {
        std::cout << storedResults[i] << "\n\n\n";
    }
}

posix_spawn_file_actions_t TestU01Battery::createFileActions(
        int * stdout_pipe, int * stderr_pipe) {
    if(pipe(stdout_pipe) || pipe(stderr_pipe))
        throw std::runtime_error("pipe creation failed");
    posix_spawn_file_actions_t actions;
    posix_spawn_file_actions_init(&actions);

    posix_spawn_file_actions_addclose(&actions , stdout_pipe[0]);
    posix_spawn_file_actions_addclose(&actions , stderr_pipe[0]);

    posix_spawn_file_actions_adddup2(&actions , stdout_pipe[1] , 1);
    posix_spawn_file_actions_addclose(&actions , stdout_pipe[1]);

    posix_spawn_file_actions_adddup2(&actions , stderr_pipe[1] , 2);
    posix_spawn_file_actions_addclose(&actions , stderr_pipe[1]);

    return actions;
}

void TestU01Battery::readPipes(int *stdout_pipe, int *stderr_pipe) {
    std::string tmpStorage;
    std::string buffer(1024 , ' ');
    size_t bytes_read;
    std::vector<pollfd> pollVector = {{stdout_pipe[0] , POLLIN},
                                      {stderr_pipe[0] , POLLIN}};
    for( ; poll(&pollVector[0] , pollVector.size() , -1) > 0 ; ) {
        if (pollVector[0].revents&POLLIN) {
            bytes_read = read(stdout_pipe[0] , &buffer[0] , buffer.length());
            tmpStorage.append(buffer , 0 , bytes_read);
        }
        else if (pollVector[1].revents&POLLIN) {
            bytes_read = read(stderr_pipe[0] , &buffer[0] , buffer.length());
            tmpStorage.append(buffer , 0 , bytes_read);
        }
        else break; // Reading done
    }
    storedResults.push_back(tmpStorage);
}

char ** TestU01Battery::buildArgs(int testNum, int *argc) {
    std::stringstream argSs;
    argSs << "testu01 -m ";
    switch(batteryMode) {
    case Constants::BATTERY_TU01_SMALLCRUSH:
        argSs << "small_crush";
        break;
    case Constants::BATTERY_TU01_CRUSH:
        argSs << "crush";
        break;
    case Constants::BATTERY_TU01_BIGCRUSH:
        argSs << "big_crush";
        break;
    default:
        throw std::runtime_error("unknown battery constant: " + batteryMode);
    }
    argSs << " -t " << testNum
          << " -i " << binFilePath
          << " -p " << repetitions;
    std::vector<std::string> argVector = Utils::split(argSs.str() , ' ');
    char ** args = new char * [argVector.size() + 1];
    for(unsigned i = 0 ; i < argVector.size() ; i++) {
        args[i] = new char [argVector[i].length() + 1];
        strcpy(args[i] , argVector[i].c_str());
    }
    args[argVector.size()] = NULL;
    *argc = argVector.size() + 1;
    return args;
}

void TestU01Battery::destroyArgs(int argc , char ** argv) {
    for(int i = 0 ; i < argc ; i++) {
        if(argv[i]) delete[] argv[i];
    }
    delete[] argv;
}

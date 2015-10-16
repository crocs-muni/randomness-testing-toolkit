#include "DieharderBattery.h"

void DieharderBattery::initBattery(const ToolkitOptions & options) {
    tests = options.getTestConsts();
    binFilePath = options.getBinFilePath();
    outFilePath = options.getOutFilePath();

    TiXmlNode * cfgRoot = NULL;
    loadXMLFile(cfgRoot , options.getInputCfgPath());

    if(outFilePath.empty())
        outFilePath = getXMLElementValue(cfgRoot , XPATH_DIEHARDER_OUTPUT_FILE);
    dieharderBinPath = getXMLElementValue(cfgRoot , XPATH_DIEHARDER_BINARY_PATH);
    additionalArguments = getXMLElementValue(cfgRoot , XPATH_DIEHARDER_ADDITIONAL_ARGS);

    if(outFilePath.empty())
        throw std::runtime_error("XML tag " + (std::string)
                                 XPATH_DIEHARDER_OUTPUT_FILE + " can't be empty");
    if(dieharderBinPath.empty())
        throw std::runtime_error("XML tag " + (std::string)
                                 XPATH_DIEHARDER_BINARY_PATH + " can't be empty");

    delete cfgRoot;
}

void DieharderBattery::runTests() {
    std::cout << "Starting execution of Dieharder tests." << std::endl;
    for(unsigned i = 0 ; i < tests.size() ; i++) {
        int stdout_pipe[2];
        int stderr_pipe[2];
        pid_t pid = 0;
        int argc = 0;

        posix_spawn_file_actions_t actions =
                createFileActions(stdout_pipe , stderr_pipe);
        char ** argv = buildArgs(tests[i] , &argc);
        int status = posix_spawn(&pid , dieharderBinPath.c_str() ,
                                 &actions , NULL , argv , environ);
        if(status == 0) {
            std::cout << "Started Dieharder process with pid: " << pid << std::endl;
            close(stdout_pipe[1]);
            close(stderr_pipe[1]);
            // Reading and storing Dieharder output
            readPipes(stdout_pipe , stderr_pipe);
            if(waitpid(pid , &status , 0) != -1) {
                std::cout << "Dieharder exited with status: " << status << std::endl;
            }
            else {
                throw std::runtime_error("error when running Dieharder");
            }
        }
        else {
            throw std::runtime_error("error occured when starting Dieharder: " +
                                     (std::string)strerror(status));
        }
        posix_spawn_file_actions_destroy(&actions);
        destroyArgs(argc , argv);
    }
}

void DieharderBattery::processStoredResults() {
    // This prints stored results => testing
    for(size_t i = 0 ; i < storedResults.size() ; i++)
        std::cout << storedResults[i] << "\n\n\n";
}

posix_spawn_file_actions_t DieharderBattery::createFileActions(
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

void DieharderBattery::readPipes(int * stdout_pipe , int * stderr_pipe) {
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

char ** DieharderBattery::buildArgs(int testNum , int * argc) {
    std::stringstream argSs;
    argSs << "dieharder -d " << testNum << " -D 511 -g 201 -f "
          << binFilePath << " " << additionalArguments;
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

void DieharderBattery::destroyArgs(int argc, char ** argv ) {
    for(int i = 0 ; i < argc ; i++) {
        if(argv[i]) delete[] argv[i];
    }
    delete[] argv;
}





































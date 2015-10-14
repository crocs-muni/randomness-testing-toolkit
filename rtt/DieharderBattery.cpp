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
        throw std::runtime_error("XML tag " + (std::string)XPATH_DIEHARDER_OUTPUT_FILE + " can't be empty");
    if(dieharderBinPath.empty())
        throw std::runtime_error("XML tag " + (std::string)XPATH_DIEHARDER_BINARY_PATH + "can't be empty");

    delete cfgRoot;
}

void DieharderBattery::runTests() {
    char ** argv;
    int argc = 0;

    for(unsigned i = 0 ; i < tests.size() ; i++) {
        argv = buildArgs(tests[i] , &argc);

        pid_t pid;
        int status;

        status = posix_spawn(&pid , dieharderBinPath.c_str() , NULL , NULL , argv , environ);

        if(status == 0) {
            std::cout << "Started Dieharder process with pid: " << pid << std::endl;
            if(waitpid(pid , &status , 0) != -1) {
                std::cout << "Child exited with status " << status << std::endl;
            }
            else {
                throw std::runtime_error("error when running Dieharder");
            }
        }
        else {
            throw std::runtime_error("error occured when starting Dieharder: " + (std::string)strerror(status));
        }
        destroyArgs(argv , argc);
    }
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

void DieharderBattery::destroyArgs(char ** argv , int argc) {
    for(int i = 0 ; i < argc ; i++) {
        if(argv[i]) delete[] argv[i];
    }
    delete[] argv;
}





































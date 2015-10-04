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

    free(cfgRoot);
}

void DieharderBattery::runTests() {
    char ** arguments = NULL;

    for(unsigned i = 0 ; i < tests.size() ; i++) {
        arguments = buildArgs(tests[i]);

        pid_t pid;
        int status;
        status = posix_spawn(&pid , dieharderBinPath.c_str() , NULL , NULL , arguments , environ);
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
        //destroyArgs(arguments);
    }
}

char ** DieharderBattery::buildArgs(int testNum) {
    std::stringstream argss;
    argss << "dieharder -d " << testNum << " -D 511 -g 201 -f " << binFilePath << additionalArguments;
    std::vector<std::string> arguments(Utils::split(argss.str() , ' '));
    char ** args = new char * [arguments.size() + 1];
    for(unsigned i = 0 ; i < arguments.size() ; i++) {
        // Manual allocation... *shudders*
        args[i] = new char [arguments[i].length() + 1];
        strcpy(args[i] , arguments[i].c_str());
    }
    args[arguments.size()] = new char[1];
    args[arguments.size()] = NULL;
    return args;
}

void DieharderBattery::destroyArgs(char ** args) {
    // this does nothing :(

    /*int n = sizeof(args) / sizeof(args[0]);
    for(int i = 0 ; i < 10 ; i++) std::cout << args[i] << std::endl;
    for(int i = 0 ; i < n ; i++) delete [] args[i];
    delete [] args;*/
}



































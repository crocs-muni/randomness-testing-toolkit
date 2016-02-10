#include "testutils-batt.h"

namespace rtt {
namespace batteries {

std::string TestUtils::executeBinary(const std::string & binaryPath,
                                     const std::string & arguments,
                                     const std::string & input) {
    int stdin_pipe[2];
    int stdout_pipe[2];
    int stderr_pipe[2];

    std::string output;
    pid_t pid = 0;
    posix_spawn_file_actions_t actions;

    if(pipe(stdin_pipe) || pipe(stdout_pipe) || pipe(stderr_pipe))
        throw std::runtime_error("pipe creation failed");

    /* Pipes will be mapped to I/O after process start */
    /* Unused ends are closed */
    posix_spawn_file_actions_init(&actions);
    /* Standard input */
    posix_spawn_file_actions_addclose(&actions , stdin_pipe[1]);
    posix_spawn_file_actions_adddup2(&actions , stdin_pipe[0] , 0);
    posix_spawn_file_actions_addclose(&actions , stdin_pipe[0]);
    /* Standard output */
    posix_spawn_file_actions_addclose(&actions , stdout_pipe[0]);
    posix_spawn_file_actions_adddup2(&actions , stdout_pipe[1] , 1);
    posix_spawn_file_actions_addclose(&actions , stdout_pipe[1]);
    /* Standard error output */
    posix_spawn_file_actions_addclose(&actions , stderr_pipe[0]);
    posix_spawn_file_actions_adddup2(&actions , stderr_pipe[1] , 2);
    posix_spawn_file_actions_addclose(&actions , stderr_pipe[1]);

    int argc = 0;
    char ** argv = buildArgv(arguments , &argc);

    int status = posix_spawn(&pid , binaryPath.c_str() ,
                             &actions , NULL , argv , environ);

    if(status == 0) {
        std::cout << "Executing " << binaryPath << " with pid: " << pid << std::endl;
        close(stdin_pipe[0]);
        close(stdout_pipe[1]);
        close(stderr_pipe[1]);
        if(!input.empty())
            write(stdin_pipe[1] , input.c_str() , input.length());

        output = readOutput(stdout_pipe , stderr_pipe);
        if(waitpid(pid , &status , 0) != -1) {
            std::cout << "Process " << pid << " exited with code " << status << std::endl;
        } else {
            throw std::runtime_error("error during execution " + binaryPath);
        }
    } else {
        throw std::runtime_error("can't execute " + binaryPath +
                                 static_cast<std::string>(strerror(status)));
    }
    posix_spawn_file_actions_destroy(&actions);
    destroyArgv(argc , argv);
    return output;
}

std::string TestUtils::getTestOrDefOpt(TiXmlNode * cfgRoot , TiXmlNode * testNode ,
                                               const std::string & defaultPath ,
                                               const std::string & testPath) {
    if(!cfgRoot)
        throw std::runtime_error("null root");

    std::string nodeValue;
    if(!testNode) {
        nodeValue = getXMLElementValue(cfgRoot , defaultPath);
        return nodeValue;
    }

    nodeValue = getXMLElementValue(testNode , testPath);
    if(nodeValue.empty()) {
        nodeValue = getXMLElementValue(cfgRoot , defaultPath);
        return nodeValue;
    } else {
        return nodeValue;
    }
}


char ** TestUtils::buildArgv(const std::string & arguments, int * argc) {
    std::vector<std::string> vecArg = Utils::split(arguments , ' ');
    char ** argv = new char * [vecArg.size() + 1];
    for(size_t i = 0 ; i < vecArg.size() ; ++i) {
        argv[i] = new char [vecArg.at(i).length() + 1];
        strcpy(argv[i] , vecArg.at(i).c_str());
    }
    argv[vecArg.size()] = NULL;
    *argc = vecArg.size() + 1;
    return argv;
}

void TestUtils::destroyArgv(int argc, char ** argv) {
    for(int i = 0 ; i < argc ; ++i) {
        if(argv[i]) delete[] argv[i];
    }
    delete[] argv;
}

std::string TestUtils::readOutput(int * stdout_pipe, int * stderr_pipe) {
    std::string buffer(1024 , ' ');
    size_t bytes_read;
    std::string output;
    std::vector<pollfd> pollVector {{stdout_pipe[0] , POLLIN , 0},
                                    {stderr_pipe[0] , POLLIN , 0}};
    for(; poll(&pollVector[0] , pollVector.size() , -1) > 0 ; ) {
        if(pollVector[0].revents&POLLIN) {
            bytes_read = read(stdout_pipe[0] , &buffer[0] , buffer.length());
            output.append(buffer , 0 , bytes_read);
        }
        else if(pollVector[1].revents&POLLIN) {
            bytes_read = read(stderr_pipe[0] , &buffer[0] , buffer.length());
            output.append(buffer , 0 , bytes_read);
        }
        else break; /* Nothing else to read */
    }
    return output;
}

} // namespace batteries
} // namespace rtt


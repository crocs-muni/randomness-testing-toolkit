#ifndef DIEHARDERBATTERY_H
#define DIEHARDERBATTERY_H

#include <poll.h>
#include <unistd.h>
#include <spawn.h>
#include <sys/wait.h>

extern char **environ;

#include "StatBatteryInterface.h"
#include "XMLproc.h"

class DieharderBattery : public StatBatteryInterface {
private:
    std::vector<int> tests;
    std::string binFilePath;
    std::string dieharderBinPath;
    std::string outFilePath;
    std::string additionalArguments;
    std::vector<std::string> storedResults;
public:
    /* Default XPATH constants for Dieharder battery */
    static const std::string XPATH_BINARY_PATH;
    static const std::string XPATH_OUTPUT_FILE;
    static const std::string XPATH_ADDITIONAL_ARGS;

    DieharderBattery() {}
    void initBattery(const ToolkitOptions & options);
    void runTests();
    void processStoredResults();
private:
    posix_spawn_file_actions_t createFileActions(int * stdout_pipe , int * stderr_pipe);
    void readPipes(int * stdout_pipe , int * stderr_pipe);
    char ** buildArgs(int testNum , int * argc);
    void destroyArgs(int argc , char ** argv);
};

#endif //DIEHARDERBATTERY_H

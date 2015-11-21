#ifndef TESTU01_BATTERY_H
#define TESTU01_BATTERY_H

#include <poll.h>
#include <unistd.h>
#include <spawn.h>
#include <sys/wait.h>

extern char **environ;

#include "StatBatteryInterface.h"
#include "XMLproc.h"

class TestU01Battery : public StatBatteryInterface {
private:
    int batteryMode;
    std::vector<int> tests;
    std::string binFilePath;
    std::string tu01Path;
    std::string outFilePath;
    int repetitions;
    std::vector<std::string> storedResults;
public:
    /* XPATH constants for TestU01 battery */
    static const std::string XPATH_BINARY_PATH;
    static const std::string XPATH_OUTPUT_FILE;
    static const std::string XPATH_REPETITIONS;

    TestU01Battery(int batMode) :
        repetitions(-1) , batteryMode(batMode)
    {}
    void initBattery(const ToolkitOptions &options);
    void runTests();
    void processStoredResults();
private:
    posix_spawn_file_actions_t createFileActions(int * stdout_pipe , int * stderr_pipe);
    void readPipes(int * stdout_pipe , int * stderr_pipe);
    char ** buildArgs(int testNum , int * argc);
    void destroyArgs(int argc , char ** argv);
};

#endif // TESTU01_BATTERY_H

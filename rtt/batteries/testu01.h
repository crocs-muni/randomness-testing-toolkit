#ifndef RTT_BATTERIES_TESTU01_H
#define RTT_BATTERIES_TESTU01_H

#include <poll.h>
#include <unistd.h>
#include <spawn.h>
#include <sys/wait.h>

#include "rtt/batteries/interface.h"
#include "libs/tinyXML/xmlproc.h"

extern char **environ;

namespace rtt {
namespace batteries {

class TestU01 : public Interface {
private:
    int batteryMode;
    std::vector<int> tests;
    std::string binFilePath;
    std::string tu01Path;
    std::string outFilePath;
    int repetitions = -1;
    std::vector<std::string> storedResults;
public:
    /* XPATH constants for TestU01 battery */
    static const std::string XPATH_BINARY_PATH;
    static const std::string XPATH_OUTPUT_FILE;
    static const std::string XPATH_REPETITIONS;

    TestU01(int batMode) : batteryMode(batMode) {}
    void initBattery(const CliOptions &options);
    void runTests();
    void processStoredResults();
private:
    posix_spawn_file_actions_t createFileActions(int * stdout_pipe , int * stderr_pipe);
    void readPipes(int * stdout_pipe , int * stderr_pipe);
    char ** buildArgs(int testNum , int * argc);
    void destroyArgs(int argc , char ** argv);
};

} // namespace batteries
} // namespace rtt

#endif // RTT_BATTERIES_TESTU01_H

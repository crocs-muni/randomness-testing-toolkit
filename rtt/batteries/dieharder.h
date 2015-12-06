#ifndef RTT_BATTERIES_DIEHARDER_H
#define RTT_BATTERIES_DIEHARDER_H

#include <poll.h>
#include <unistd.h>
#include <spawn.h>
#include <sys/wait.h>

#include "rtt/batteries/interface.h"
#include "libs/tinyXML/xmlproc.h"

extern char **environ;

namespace rtt {
namespace batteries {

class Dieharder : public Interface {
private:
    std::vector<int> tests;
    std::string binFilePath;
    std::string dieharderBinPath;
    std::string outFilePath;
    std::string additionalArguments;
    std::vector<std::string> storedResults;
    std::vector<float> tmpResults;
public:
    /* Default XPATH constants for Dieharder battery */
    static const std::string XPATH_BINARY_PATH;
    static const std::string XPATH_OUTPUT_FILE;
    static const std::string XPATH_ADDITIONAL_ARGS;

    Dieharder(const CliOptions & options);
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

#endif // RTT_BATTERIES_DIEHARDER_H

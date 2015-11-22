#ifndef RTT_BATTERIES_NISTSTS_H
#define RTT_BATTERIES_NISTSTS_H

#include <poll.h>
#include <unistd.h>
#include <spawn.h>
#include <sys/wait.h>

#include "rtt/batteries/interface.h"
#include "libs/tinyXML/xmlproc.h"

extern char **environ;

namespace rtt {
namespace batteries {

class NistSts : public Interface {
private:
    std::string testsVector;
    std::string binFilePath;
    std::string nistStsBinPath;
    std::string outFilePath;
    std::vector<std::pair<int , int>> adjustedParameters;
    std::string nistOutput;
    int streamSize;
    int streamCount;
public:
    /* Default XPATH constants for NIST STS battery */
    static const std::string XPATH_BINARY_PATH;
    static const std::string XPATH_OUTPUT_FILE;
    static const std::string XPATH_STREAM_SIZE;
    static const std::string XPATH_STREAM_COUNT;
    static const std::string XPATH_PAR_ADJUST;
    static const std::string XPATH_PAR_ADJUST_ATT;

    NistSts() {}
    void initBattery(const CliOptions & options);
    void runTests();
    void processStoredResults();
private:
    std::string createTestsVector(const std::vector<int> & tests);
    void loadAdjustedParameters(TiXmlNode * root);
    void adjParValidator(int testNum);
    void validateTestConsts(const std::vector<int> & tests);
    posix_spawn_file_actions_t createFileActions(
            int * stdin_pipe , int * stdout_pipe , int * stderr_pipe);
    void readPipes(int * stdout_pipe , int * stderr_pipe);
    char ** buildArgs(int * argc);
    void destroyArgs(int argc , char ** argv);
    std::string createInputSequence();
};

} // namespace batteries
} // namespace rtt

#endif // RTT_BATTERIES_NISTSTS_H

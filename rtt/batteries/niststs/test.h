#ifndef RTT_BATTERIES_NISTSTS_TEST_H
#define RTT_BATTERIES_NISTSTS_TEST_H

#include <poll.h>
#include <unistd.h>
#include <spawn.h>
#include <sys/wait.h>
#include <string>
#include <vector>

#include "libs/tinyXML/xmlproc.h"
#include "rtt/utils.h"

namespace rtt {
namespace batteries {
namespace niststs {

enum class TestIndex {
    frequency = 1,
    blockFrequency,
    cumulativeSums,
    runs,
    longestRun,
    rank,
    fft,
    nonOverlappingTemplate,
    overlappingTemplate,
    universal,
    approximateEntropy,
    randomExcursions,
    randomExcursionsVariant,
    serial,
    linearComplexity
};

typedef std::vector<float> testPvals;

class Test {
public:
    /* Default XPATH constants for NIST STS battery */
    static const std::string XPATH_BINARY_PATH;
    static const std::string XPATH_OUTPUT_DIRECTORY;
    static const std::string XPATH_STREAM_SIZE_DEFAULT;
    static const std::string XPATH_STREAM_COUNT_DEFAULT;
    static const std::string XPATH_TESTS_SETTINGS;
    static const std::string XPATH_ATTRIBUTE_TEST_INDEX;
    static const std::string XPATH_NODE_STREAM_SIZE;
    static const std::string XPATH_NODE_STREAM_COUNT;
    static const std::string XPATH_NODE_BLOCK_LENGTH;

    /* Parent test result directory */
    static const std::string PATH_MAIN_RESULT_DIR;

    static Test getInstance(TestIndex testIndex ,
                            TiXmlNode * cfgRoot ,
                            const std::string & binaryDataPath);

    bool wasExecuted() const { return executed; }

    void execute();

private:
    /*
    =================
    *** Variables ***
    =================
    */
    /* These fields will be set after initialization in */
    /* getInstance */
    bool executed = false;
    std::string executablePath;
    std::string binaryDataPath;
    int streamSize;
    int streamCount;
    std::vector<int> blockLen;
    /* Following fields will be initialized in getInstance */
    /* to default values according to test index */
    TestIndex testConst;
    std::string logicName;
    std::string resultSubDir;
    int subTestCount;
    bool adjustableBlockLen;
    /* Following fileds will be set after calling */
    /* execute */
    std::string nistStsOutput;
    std::string testLog;
    std::vector<testPvals> results;

    /*
    ===============
    *** Methods ***
    ===============
    */
    /* I don't want to allow existence of Test objects */
    /* without initialization that is in getInstance */
    Test() {}
    void buildArgv(int * argc , char ** argv) const;
    void destroyArgv(int argc , char ** argv) const;
    std::string buildInput() const;
    void readPipes(int * stdout_pipe , int * stderr_pipe);
    void parseStoreResults();
    testPvals readPvals(const std::string &fileName);
};

} // namespace niststs
} // namespace batteries
} // namespace rtt

#endif // RTT_BATTERIES_NISTSTS_TEST_H

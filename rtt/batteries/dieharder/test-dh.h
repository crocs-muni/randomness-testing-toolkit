#ifndef RTT_BATTERIES_DIEHARDER_TEST_H
#define RTT_BATTERIES_DIEHARDER_TEST_H

#include <poll.h>
#include <unistd.h>
#include <spawn.h>
#include <sys/wait.h>
#include <string>
#include <string.h>
#include <vector>

extern char **environ;

#include "libs/tinyXML/xmlproc.h"
#include "rtt/utils.h"
#include "rtt/batteries/dieharder/setting-dh.h"

namespace rtt {
namespace batteries {
namespace dieharder {

enum class TestIndex {
    birthdays = 0 ,
    operm5 = 1,
    binaryrank1 = 2,
    binaryrank2 = 3,
    bitstream = 4,
    opso = 5,
    oqso = 6,
    dna = 7,
    count1sbyte = 8,
    count1sstream = 9,
    parking = 10,
    mindistancecircle = 11,
    mindistancesphere = 12,
    squeeze = 13,
    sums = 14,
    runs = 15,
    craps = 16,
    gcd = 17,
    monobit = 100,
    stsruns = 101,
    serial = 102,
    bitdist = 200,
    mindistance = 201,
    permutations = 202,
    lagged = 203,
    ks = 204,
    bytedist = 205,
    dabdct = 206,
    dabfilltree = 207,
    dabfilltree2 = 208,
    dabmonobit = 209
};

typedef std::vector<float> testPvals;

class Test {
public:
    /* Default XPATH constants for Dieharder battery */
    static const std::string XPATH_BINARY_PATH;
    static const std::string XPATH_DEFAULT_OPTIONS;
    static const std::string XPATH_TESTS_SETTINGS;
    static const std::string XPATH_ATTRIBUTE_TEST_INDEX;
    /* Parent test result directory */
    static const std::string PATH_MAIN_RESULT_DIR;
    /* Default options that are always used when starting battery */
    static const int OPTION_HEADER_FLAG;
    static const int OPTION_FILE_GENERATOR;

    /* Some getters for results will be probably added in time */
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
    std::vector<Setting> settings;
    /* Following fields will be initialized in getInstance */
    /* to default values according to test index */
    TestIndex testConst;
    std::string logicName;
    int subTestsCount;
    /* Following fields will be set after calling */
    /* execute */
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
    char ** buildArgv(int * argc) const;
    void destroyArgv(int argc , char ** argv) const;
    void readPipes(int * stdout_pipe , int * stderr_pipe);
    void extractPvalues();
};

} // namespace dieharder
} // namespace batteries
} // namespace rtt

#endif // RTT_BATTERIES_DIEHARDER_TEST_H

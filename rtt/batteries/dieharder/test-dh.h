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
#include "rtt/options.h"
#include "rtt/batteries/dieharder/setting-dh.h"

namespace rtt {
namespace batteries {
namespace dieharder {

/*enum class TestIndex {
    birthdays           = 0,
    operm5              = 1,
    binaryrank1         = 2,
    binaryrank2         = 3,
    bitstream           = 4,
    opso                = 5,
    oqso                = 6,
    dna                 = 7,
    count1sbyte         = 8,
    count1sstream       = 9,
    parking             = 10,
    mindistancecircle   = 11,
    mindistancesphere   = 12,
    squeeze             = 13,
    sums                = 14,
    runs                = 15,
    craps               = 16,
    gcd                 = 17,
    monobit             = 100,
    stsruns             = 101,
    serial              = 102,
    bitdist             = 200,
    mindistance         = 201,
    permutations        = 202,
    lagged              = 203,
    ks                  = 204,
    bytedist            = 205,
    dabdct              = 206,
    dabfilltree         = 207,
    dabfilltree2        = 208,
    dabmonobit          = 209
};*/

typedef std::vector<float> tTestPvals;
typedef std::pair<int , std::string> tTestInfo;

class Test {
public:
    /* Test info constants */
    static const tTestInfo INFO_BIRTHDAYS;
    static const tTestInfo INFO_OPERM5;
    static const tTestInfo INFO_BINARYRANK1;
    static const tTestInfo INFO_BINARYRANK2;
    static const tTestInfo INFO_BITSTREAM;
    static const tTestInfo INFO_OPSO;
    static const tTestInfo INFO_OQSO;
    static const tTestInfo INFO_DNA;
    static const tTestInfo INFO_COUNT1SBYTE;
    static const tTestInfo INFO_COUNT1SSTREAM;
    static const tTestInfo INFO_PARKING;
    static const tTestInfo INFO_MINDISTANCECIRCLE;
    static const tTestInfo INFO_MINDISTANCESPHERE;
    static const tTestInfo INFO_SQUEEZE;
    static const tTestInfo INFO_SUMS;
    static const tTestInfo INFO_RUNS;
    static const tTestInfo INFO_CRAPS;
    static const tTestInfo INFO_GCD;
    static const tTestInfo INFO_MONOBIT;
    static const tTestInfo INFO_STSRUNS;
    static const tTestInfo INFO_SERIAL;
    static const tTestInfo INFO_BITDIST;
    static const tTestInfo INFO_MINDISTANCE;
    static const tTestInfo INFO_PERMUTATIONS;
    static const tTestInfo INFO_LAGGED;
    static const tTestInfo INFO_KS;
    static const tTestInfo INFO_BYTEDIST;
    static const tTestInfo INFO_DABDCT;
    static const tTestInfo INFO_DABFILLTREE;
    static const tTestInfo INFO_DABFILLTREE2;
    static const tTestInfo INFO_DABMONOBIT;

    /* Default XPath constants for Dieharder battery */
    static const std::string XPATH_BINARY_PATH;
    static const std::string XPATH_DEFAULT_ARGUMENTS;
    static const std::string XPATH_DEFAULT_PSAMPLES;
    static const std::string XPATH_TESTS_SETTINGS;
    static const std::string XPATH_ATTRIBUTE_TEST_INDEX;
    static const std::string XPATH_TEST_ARGUMENTS;
    static const std::string XPATH_TEST_PSAMPLES;
    /* Parent test result directory */
    /* Default options that are always used when starting battery */
    static const int OPTION_HEADER_FLAG;
    static const int OPTION_FILE_GENERATOR;

    /* Some getters for results will be probably added in time */
    static Test getInstance(int testIndex ,
                            const CliOptions & options ,
                            TiXmlNode * cfgRoot);

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
    int pSampleCount;
    /* Following fields will be initialized in getInstance */
    /* to default values according to test index */
    int testConst;
    std::string logicName;
    /* Following fields will be set after calling */
    /* execute */
    int subTestsCount;
    std::string testLog;
    std::vector<tTestPvals> results;

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

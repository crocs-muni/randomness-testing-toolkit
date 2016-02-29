#ifndef RTT_BATTERIES_NISTSTS_TEST_H
#define RTT_BATTERIES_NISTSTS_TEST_H

#include <string>
#include <string.h>
#include <vector>
#include <sstream>
#include <tuple>

#include "libs/tinyXML/xmlproc.h"
#include "rtt/batteries/itest-batt.h"
#include "rtt/batteries/testrunner-batt.h"
#include "rtt/utils.h"
#include "rtt/options.h"

namespace rtt {
namespace batteries {
namespace niststs {

typedef std::tuple<int , std::string , std::string , int , bool> tTestInfo;

class Test : public ITest {
public:
    /* Test info constants */
    static const tTestInfo INFO_FREQ;
    static const tTestInfo INFO_BLOCKFREQ;
    static const tTestInfo INFO_CUSUMS;
    static const tTestInfo INFO_RUNS;
    static const tTestInfo INFO_LONGESTRUN;
    static const tTestInfo INFO_RANK;
    static const tTestInfo INFO_FFT;
    static const tTestInfo INFO_NONOVERTEMP;
    static const tTestInfo INFO_OVERTEMP;
    static const tTestInfo INFO_UNIVERSAL;
    static const tTestInfo INFO_APPROXENT;
    static const tTestInfo INFO_RNDEXCURSIONS;
    static const tTestInfo INFO_RNDEXCURSIONSVAR;
    static const tTestInfo INFO_SERIAL;
    static const tTestInfo INFO_LINEARCOMPLEXITY;

    /* Default XPATH constants for NIST STS battery */
    static const std::string XPATH_BINARY_PATH;
    static const std::string XPATH_OUTPUT_DIRECTORY;
    static const std::string XPATH_TESTS_SETTINGS;
    static const std::string XPATH_DEFAULT_STREAM_SIZE;
    static const std::string XPATH_DEFAULT_STREAM_COUNT;
    static const std::string XPATH_TEST_STREAM_SIZE;
    static const std::string XPATH_TEST_STREAM_COUNT;
    static const std::string XPATH_TEST_BLOCK_LENGTH;
    static const std::string XPATH_ATTRIBUTE_TEST_INDEX;
    /* Parent test result directory */
    static const std::string PATH_MAIN_RESULT_DIR;

    /*
    ======================
    *** Public methods ***
    ======================
    */
    /* Some getters for results will be probably added in time */
    static std::unique_ptr<Test> getInstance(int testIndex ,
                                             TiXmlNode * cfgRoot ,
                                             const CliOptions & options);

    void execute();

    bool wasExecuted() const { return executed; }

    void appendTestLog(std::string & outputLog) const;

    int getTestIndex() const;

    std::string getLogicName() const;

    std::vector<std::string> getParameters() const;

    std::vector<std::string> getStatistics() const;

    std::vector<tTestPvals> getResults() const;

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
    std::string streamSize;
    std::string streamCount;
    std::string blockLength;
    /* Following fields will be initialized in getInstance */
    /* to default values according to test index */
    int testIndex;
    std::string logicName;
    std::string resultSubDir;
    int subTestCount;
    bool adjustableBlockLen;
    /* Following fileds will be set after calling */
    /* execute */
    std::string outputLog;
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

    std::string createArgs() const;

    std::string createInput() const;

    void parseStoreResults();

    tTestPvals readPvals(const std::string & fileName);
};

} // namespace niststs
} // namespace batteries
} // namespace rtt

#endif // RTT_BATTERIES_NISTSTS_TEST_H

#ifndef RTT_BATTERIES_DIEHARDER_TEST_H
#define RTT_BATTERIES_DIEHARDER_TEST_H

#include <string.h>
#include <vector>

#include "libs/tinyXML/xmlproc.h"
#include "rtt/utils.h"
#include "rtt/options.h"
#include "rtt/rttexception.h"
#include "rtt/batteries/testrunner-batt.h"
#include "rtt/batteries/itest-batt.h"
#include "rtt/batteries/dieharder/setting-dh.h"

namespace rtt {
namespace batteries {
namespace dieharder {

typedef std::pair<int , std::string> tTestInfo;

class Test : public ITest {
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

    /*
    ======================
    *** Public methods ***
    ======================
    */
    static std::unique_ptr<Test> getInstance(int testIndex ,
                                 const CliOptions & options ,
                                 TiXmlNode * cfgRoot);

    void execute();

    bool wasExecuted() const { return executed; }

    void appendTestLog(std::string & batteryLog) const;

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
    std::vector<Setting> settings;
    std::string objectInfo;
    int pSampleCount;
    /* Following fields will be initialized in getInstance */
    /* to default values according to test index */
    int testIndex;
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

    std::string createArgs() const;

    void extractPvalues();
};

} // namespace dieharder
} // namespace batteries
} // namespace rtt

#endif // RTT_BATTERIES_DIEHARDER_TEST_H

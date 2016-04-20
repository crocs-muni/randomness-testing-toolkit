#ifndef RTT_BATTERIES_TESTU01_TEST_H
#define RTT_BATTERIES_TESTU01_TEST_H

#include <string>
#include <string.h>
#include <vector>
#include <sstream>
#include <tuple>

#include "rtt/globals.h"
#include "rtt/batteries/itest-batt.h"
#include "rtt/batteries/testrunner-batt.h"
#include "rtt/batteries/testconstants.h"

namespace rtt {
namespace batteries {
namespace testu01 {

/* Typedefs for parameter types */
typedef std::pair<std::string , std::string> tParam;
typedef std::vector<std::string> tStringVector;

class Test : public ITest {
public:
    /*
    ======================
    *** Public methods ***
    ======================
    */
    static std::unique_ptr<Test> getInstance(int testIndex ,
                                             const Globals & globals);

    void appendTestLog(std::string & batteryLog) const;

    bool wasExecuted() const { return executed; }

    void execute();

    std::string getLogicName() const;

    std::vector<std::string> getParameters() const;

    std::vector<std::string> getStatistics() const;

    std::vector<tTestPvals> getResults() const;

    int getTestIndex() const;

private:
    /*
    =================
    *** Variables ***
    =================
    */
    /* Pointers to global configurations */
    std::shared_ptr<CliOptions> cliOptions;
    std::shared_ptr<ToolkitSettings> toolkitSettings;
    std::shared_ptr<batteries::Configuration> batteryConfiguration;

    /* These fields will be set after initialization in */
    /* getInstance() */
    Constants::Battery battery;
    int testIndex = -1;
    std::string logicName;
    tStringVector paramNames;
    tStringVector statisticNames;
    int repetitions;
    std::string executablePath;
    std::string binaryDataPath;
    std::string objectInfo;
    /* Only used in crush batteres */
    std::vector<tParam> params;
    /* Used in rabbit/alphabit battery */
    std::string bit_nb;
    std::string bit_r;
    std::string bit_s;
    /* Following vars will be set after test execution */
    bool executed = false;
    /* Number of statistics calculated in each test
     * resulting pval count = reps*statCount */
    uint statCount;
    std::string testLog;
    /* Each tTestPval holds results of single test and its statistics */
    /* This is in vector - multiple test repetitions are possible */
    std::vector<tTestPvals> results;

    /*
    ===============
    *** Methods ***
    ===============
    */
    Test() {}

    std::string createArgs() const;

    void extractPvalues();

    void saveTestLogToFile();

    double convertStringToDouble(const std::string & num,
                                 const std::string & oneMinus);
};

} // namespace testu01
} // namespace batteries
} // namespace rtt

#endif // RTT_BATTERIES_TESTU01_TEST_H

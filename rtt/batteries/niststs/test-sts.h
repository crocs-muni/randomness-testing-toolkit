#ifndef RTT_BATTERIES_NISTSTS_TEST_H
#define RTT_BATTERIES_NISTSTS_TEST_H

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
namespace niststs {

typedef std::tuple<int , std::string , std::string , int , bool> tTestInfo;

class Test : public ITest {
public:
    /*
    ======================
    *** Public methods ***
    ======================
    */
    /* Some getters for results will be probably added in time */
    static std::unique_ptr<Test> getInstance(int testIndex ,
                                             const Globals & globals);

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
    /* Pointers to global configurations */
    std::shared_ptr<CliOptions> cliOptions;
    std::shared_ptr<ToolkitSettings> toolkitSettings;
    std::shared_ptr<batteries::Configuration> batteryConfiguration;

    /* These fields will be set after initialization in */
    /* getInstance */
    Constants::Battery battery;
    bool executed = false;
    std::string objectInfo;
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

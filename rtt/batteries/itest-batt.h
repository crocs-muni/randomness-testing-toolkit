#ifndef RTT_BATTERIES_ITEST_H
#define RTT_BATTERIES_ITEST_H

#include "rtt/globals.h"

namespace rtt {
namespace batteries {

typedef std::vector<double> tTestPvals;

class ITest {
public:
    static std::unique_ptr<ITest> getInstance(int testIndex ,
                                              const Globals & globals);

    virtual ~ITest() {}

    virtual void execute() = 0;

    virtual bool wasExecuted() const = 0;

    virtual void appendTestLog(std::string & batteryLog) const = 0;

    virtual std::string getLogicName() const = 0;

    virtual std::vector<std::string> getParameters() const = 0;

    virtual std::vector<std::string> getStatistics() const = 0;

    virtual std::vector<tTestPvals> getResults() const = 0;

    virtual int getTestIndex() const = 0;

    /* Following methods are used more or less by all tests */
    /* So for the sake of code non-duplicity, I declare them here */

protected:
    void initializeVariables(int ti , const Globals & globals);

    /* Pointers to global configurations */
    std::shared_ptr<CliOptions> cliOptions;
    std::shared_ptr<ToolkitSettings> toolkitSettings;
    std::shared_ptr<batteries::Configuration> batteryConfiguration;

    /* These fields will be set after initialization in */
    /* getInstance() */
    Constants::Battery battery;
    int testIndex = -1;
    std::string logicName;
    std::string executablePath;
    std::string binaryDataPath;
    std::string objectInfo;
    std::string testLog;
    std::vector<tTestPvals> results;
    bool executed = false;

private:
    bool initialized = false;
};

} // namespace batteries
} // namespace rtt

#endif // RTT_BATTERIES_ITEST_H

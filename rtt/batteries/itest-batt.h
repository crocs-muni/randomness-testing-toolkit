#ifndef RTT_BATTERIES_ITEST_H
#define RTT_BATTERIES_ITEST_H

#include "rtt/globalcontainer.h"
#include "rtt/batteries/batteryoutput.h"

namespace rtt {
namespace batteries {

typedef std::vector<double> tTestPvals;

class ITest {
public:
    static std::unique_ptr<ITest> getInstance(int testIndex ,
                                              const GlobalContainer & container);

    virtual ~ITest() {}

    virtual std::vector<std::string> getTestUserSettings() const = 0;

    virtual std::vector<std::vector<std::string>> getTestsParameters() const = 0;

    virtual std::vector<std::string> getStatistics() const = 0;

    void execute();

    /* Getters for results and some variables */
    bool wasExecuted() const;

    int getTestIndex() const;

    std::string getLogicName() const;

    std::vector<tTestPvals> getResults() const;

    std::string getBatteryStdErr() const;

    std::vector<std::string> getBatteryErrors();

    std::vector<std::string> getBatteryWarnings();

protected:
    ITest(int testIndex , const GlobalContainer & container);

    /* These fields will be set in the constructor */
    /* Pointers to global configurations */
    std::shared_ptr<CliOptions> cliOptions;
    std::shared_ptr<ToolkitSettings> toolkitSettings;
    std::shared_ptr<batteries::Configuration> batteryConfiguration;
    std::shared_ptr<Logger> logger;
    /* Test specific fields - will be set in constructor (base class) and
     * getInstance(derived classes) */
    int testIndex;
    Constants::Battery battery;
    std::string logicName;
    std::string logFilePath;
    std::string executablePath;
    std::string binaryDataPath;
    std::string objectInfo;
    std::string batteryArgs;
    std::string batteryInput;
    /* Will be set after test execution.
     * It is not extractable before execution. */
    bool executed = false;
    //std::string testLog;
    BatteryOutput batteryOutput;
    std::vector<tTestPvals> results;

private:
    virtual void processBatteryOutput() = 0;
};

} // namespace batteries
} // namespace rtt

#endif // RTT_BATTERIES_ITEST_H

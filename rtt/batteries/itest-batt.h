#ifndef RTT_BATTERIES_ITEST_H
#define RTT_BATTERIES_ITEST_H

#include "rtt/globalcontainer.h"
#include "rtt/batteries/batteryoutput.h"
#include "rtt/batteries/ivariant-batt.h"

namespace rtt {
namespace batteries {

typedef std::vector<double> tTestPvals;

class ITest {
public:
    static std::unique_ptr<ITest> getInstance(int testId,
                                              const GlobalContainer & cont);

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
    ITest(int testId , const GlobalContainer & cont);

    /* These fields will be set in the constructor */
    /* Pointers to global configurations */
    CliOptions * cliOptions;
    ToolkitSettings * toolkitSettings;
    Configuration * batteryConfiguration;
    Logger * logger;
    /* Variations of the test */
    std::vector<std::unique_ptr<IVariant>> variants;
    /* Test specific fields - will be set in constructor (base class) and
     * getInstance(derived classes) */
    int testId;
    Constants::Battery battId;
    std::string logicName;
    std::string logFilePath;
    std::string executablePath;
    std::string objectInfo;
    /* Will be set after test execution.
     * It is not extractable before execution. */
    bool executed = false;
    BatteryOutput batteryOutput;
    std::vector<tTestPvals> results;

private:
    virtual void processBatteryOutput() = 0;
};

} // namespace batteries
} // namespace rtt

#endif // RTT_BATTERIES_ITEST_H

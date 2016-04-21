#ifndef RTT_BATTERIES_ITEST_H
#define RTT_BATTERIES_ITEST_H

#include "rtt/globalcontainer.h"

namespace rtt {
namespace batteries {

typedef std::vector<double> tTestPvals;

class ITest {
public:
    static std::unique_ptr<ITest> getInstance(int testIndex ,
                                              const GlobalContainer & container);

    virtual ~ITest() {}

    virtual void execute() = 0;

    virtual std::vector<std::string> getParameters() const = 0;

    virtual std::vector<std::string> getStatistics() const = 0;

    /* Getters for results and some variables */
    bool wasExecuted() const;

    int getTestIndex() const;

    std::string getLogicName() const;

    std::vector<tTestPvals> getResults() const;

    void appendTestLog(std::string & batteryLog) const;

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
    std::string executablePath;
    std::string binaryDataPath;
    std::string objectInfo;
    /* Will be set after test execution.
     * It is not extractable before execution. */
    bool executed = false;
    std::string testLog;
    std::vector<tTestPvals> results;
};

} // namespace batteries
} // namespace rtt

#endif // RTT_BATTERIES_ITEST_H

#ifndef RTT_IBATTERY_H
#define RTT_IBATTERY_H

#include "rtt/globals.h"
#include "rtt/output/ioutput-out.h"
#include "rtt/batteries/itest-batt.h"
#include "rtt/batteries/testrunner-batt.h"

namespace rtt {
namespace batteries {

class IBattery {
public:
    static std::unique_ptr<IBattery> getInstance(const Globals & globals);

    void runTests();

    virtual ~IBattery() {}

    virtual void processStoredResults() = 0;

protected:
    /* Method for common variable initialization.
     * Have to be called at the beginning of
     * derived classes initialization, can stay uninitialized. */
    void initializeVariables(const Globals & globals);

    /* Variables common for all batteries. Set in getInstance().
     * Used by batteries in later stages. */

    /* Objects pointing to global setting storage -
     * many other classes are using these globals */
    std::shared_ptr<CliOptions> cliOptions;
    std::shared_ptr<batteries::Configuration> batteryConfiguration;
    std::shared_ptr<ToolkitSettings> toolkitSettings;
    /* Variables initialized in getInstance() */
    Constants::Battery battery;
    time_t creationTime;
    std::string logFilePath;
    std::string objectInfo;
    std::unique_ptr<output::IOutput> storage;
    /* Battery is keeping track of tests set to execution.
     * Test objects keep track of their settings and execution results. */
    std::vector<std::unique_ptr<ITest>> tests;
    /* Set to true after execution */
    bool executed = false;

private:
    /* Set to true in initializeVariables().
     * Prevents creation of derived class with
     * unitialized base class variables */
    bool initialized = false;
};

} // namespace batteries
} // namespace rtt

#endif // RTT_IBATTERY_H

#ifndef RTT_IBATTERY_H
#define RTT_IBATTERY_H

#include "rtt/batteries/itest-batt.h"
#include "rtt/batteries/itestresult-batt.h"

namespace rtt {
namespace batteries {

/**
 * @brief The IBattery class General interface for batteries to store their settings and tests.
 */
class IBattery {
public:
    /**
     * @brief getInstance Creates an initialized object
     * @param cont Global settings
     * @return
     */
    static std::unique_ptr<IBattery> getInstance(const GlobalContainer & cont);

    /**
     * @brief runTests Executes all tests in the battery
     */
    void runTests();

    /**
     * @brief ~IBattery Destructor.
     */
    virtual ~IBattery() {}

    /**
     * @brief getTestResults
     * @return Results of the executed tests, will throw
     * error if the Battery wasn't executed before.
     */
    virtual std::vector<std::unique_ptr<ITestResult>> getTestResults() const = 0;

protected:
    IBattery(const GlobalContainer & cont);

    /* Variables common for all batteries. Set in getInstance().
     * Used by batteries in later stages. */
    /* Objects pointing to global object storage -
     * many classes use these objects */
    clinterface::RTTCliOptions * rttCliOptions;
    Configuration * batteryConfiguration;
    ToolkitSettings * toolkitSettings;
    Logger * logger;
    /* Variables initialized in getInstance() */
    time_t creationTime;
    clinterface::BatteryArg battery;
    std::string objectInfo;
    /* Battery is keeping track of tests set to execution.
     * Test objects keep track of their settings and execution results. */
    std::vector<std::unique_ptr<ITest>> tests;
    /* Set to true after execution */
    bool executed = false;
};

} // namespace batteries
} // namespace rtt

#endif // RTT_IBATTERY_H

#ifndef RTT_IBATTERY_H
#define RTT_IBATTERY_H

#include "rtt/globalcontainer.h"
#include "rtt/output/ioutput-out.h"
#include "rtt/batteries/itest-batt.h"
#include "rtt/batteries/testrunner-batt.h"

namespace rtt {
namespace batteries {

class IBattery {
public:
    static std::unique_ptr<IBattery> getInstance(const GlobalContainer & container);

    void runTests();

    virtual ~IBattery() {}

    virtual void processStoredResults() = 0;

protected:
    IBattery(const GlobalContainer & container);

    /* Variables common for all batteries. Set in getInstance().
     * Used by batteries in later stages. */
    /* Objects pointing to global object storage -
     * many classes use these objects */
    std::shared_ptr<CliOptions> cliOptions;
    std::shared_ptr<batteries::Configuration> batteryConfiguration;
    std::shared_ptr<ToolkitSettings> toolkitSettings;
    std::shared_ptr<Logger> logger;
    /* Variables initialized in getInstance() */
    time_t creationTime;
    Constants::Battery battery;
    std::string objectInfo;
    //std::unique_ptr<output::IOutput> storage;
    std::shared_ptr<output::IOutput> storage;
    /* Battery is keeping track of tests set to execution.
     * Test objects keep track of their settings and execution results. */
    std::vector<std::unique_ptr<ITest>> tests;
    /* Set to true after execution */
    bool executed = false;
};

} // namespace batteries
} // namespace rtt

#endif // RTT_IBATTERY_H

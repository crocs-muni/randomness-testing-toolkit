#ifndef RTT_IBATTERY_H
#define RTT_IBATTERY_H

#include "rtt/storage/istorage.h"
#include "rtt/batteries/itest-batt.h"

namespace rtt {
namespace batteries {

class IBattery {
public:
    static std::unique_ptr<IBattery> getInstance(const GlobalContainer & cont);

    void runTests();

    virtual ~IBattery() {}

    virtual void storeResults() = 0;

protected:
    IBattery(const GlobalContainer & cont);

    /* Variables common for all batteries. Set in getInstance().
     * Used by batteries in later stages. */
    /* Objects pointing to global object storage -
     * many classes use these objects */
    CliOptions * cliOptions;
    Configuration * batteryConfiguration;
    ToolkitSettings * toolkitSettings;
    Logger * logger;
    /* Variables initialized in getInstance() */
    time_t creationTime;
    Constants::Battery battId;
    std::string objectInfo;
    std::unique_ptr<storage::IStorage> storage;
    /* Battery is keeping track of tests set to execution.
     * Test objects keep track of their settings and execution results. */
    std::vector<std::unique_ptr<ITest>> tests;
    /* Set to true after execution */
    bool executed = false;
};

} // namespace batteries
} // namespace rtt

#endif // RTT_IBATTERY_H

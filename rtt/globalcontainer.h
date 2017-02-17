#ifndef RTT_GLOBALCONTAINER_H
#define RTT_GLOBALCONTAINER_H

#include <memory>

#include "rtt/clioptions.h"
#include "rtt/toolkitsettings.h"
#include "rtt/batteries/configuration-batt.h"
#include "rtt/logger.h"

namespace rtt {

/* Class that unifies objects that are widely used thorough application
 * so that only one object is passed to other classes. Should be passed
 * as constant reference, only holds pointers to other objects. Before
 * calling getter on desired object, it must be first initialized using
 * init methods. Init only calls class's constructor or getInstance
 * method and creates an unique pointer. */
class GlobalContainer {
public:
    GlobalContainer()
        : creationTime(Utils::getRawTime()) {}

    void initCliOptions(int argc , char * argv[]);

    void initToolkitSettings(const std::string & filename);

    void initBatteriesConfiguration(const std::string & filename);

    void initLogger(const std::string & logId , bool toCout);

    time_t getCreationTime() const;

    CliOptions * getCliOptions() const;

    ToolkitSettings * getToolkitSettings() const;

    batteries::Configuration * getBatteryConfiguration() const;

    Logger * getLogger() const;

private:
    /* Application start time, will be used in naming files, etc. */
    time_t creationTime;
    std::unique_ptr<CliOptions> cliOptions;
    std::unique_ptr<ToolkitSettings> toolkitSettings;
    std::unique_ptr<batteries::Configuration> batteryConfiguration;
    std::unique_ptr<Logger> logger;
};

} // namespace rtt

#endif // RTT_GLOBALCONTAINER_H

#ifndef RTT_GLOBALCONTAINER_H
#define RTT_GLOBALCONTAINER_H

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
 * method and creates a shared pointer. */
class GlobalContainer {
public:
    GlobalContainer()
        : creationTime(Utils::getRawTime()) {}

    void initCliOptions(int argc , char * argv[]);

    void initToolkitSettings(const std::string & filename);

    void initBatteriesConfiguration(const std::string & filename);

    void initLogger(const std::string & logId ,
                    const std::string & logFile , bool toCout);

    time_t getCreationTime() const;

    std::shared_ptr<CliOptions> getCliOptions() const;

    std::shared_ptr<ToolkitSettings> getToolkitSettings() const;

    std::shared_ptr<batteries::Configuration> getBatteryConfiguration() const;

    std::shared_ptr<Logger> getLogger() const;

private:
    /* Application start time, will be used in naming files, etc. */
    time_t creationTime;
    std::shared_ptr<CliOptions> cliOptions;
    std::shared_ptr<ToolkitSettings> toolkitSettings;
    std::shared_ptr<batteries::Configuration> batteryConfiguration;
    std::shared_ptr<Logger> logger;
};

} // namespace rtt

#endif // RTT_GLOBALCONTAINER_H

#ifndef RTT_GLOBALCONTAINER_H
#define RTT_GLOBALCONTAINER_H

#include <memory>

#include "rtt/clinterface/rttclioptions.h"
#include "rtt/toolkitsettings.h"
#include "rtt/batteries/configuration-batt.h"
#include "rtt/logger.h"

namespace rtt {

/**
 * @brief The GlobalContainer class Class that unifies objects
 * that are widely used thorough application
 * so that only one object is passed to other classes. Should be passed
 * as constant reference, only holds pointers to other objects. Before
 * calling getter on desired object, it must be first initialized using
 * init methods. Init only calls class' constructor or getInstance
 * method and creates an unique pointer.
 */
class GlobalContainer {
public:
    GlobalContainer()
        : creationTime(Utils::getRawTime()) {}

    /**
     * @brief initCliOptions Initializes CliOptions object, will
     * parse command line arguments of the program
     * @param argc
     * @param argv
     */
    void initRttCliOptions(int argc , char * argv[]);

    /**
     * @brief initToolkitSettings Initializes ToolkitSettings object,
     * will read configuration file with said settings.
     * @param filename
     */
    void initToolkitSettings(const std::string & filename);

    /**
     * @brief initBatteriesConfiguration Initializes BatteriesConfiguration object,
     * will read configuration file.
     * @param filename
     */
    void initBatteriesConfiguration(const std::string & filename);

    /**
     * @brief initLogger Initializes logger object.
     * @param logId Unique id of the logged
     * @param toCout Sets whether the log will be also written to standard output
     */
    void initLogger(const std::string & logId , bool toCout);

    /**
     * @brief getCreationTime
     * @return Raw time of creation of the class instance
     */
    time_t getCreationTime() const;

    /**
     * @brief getCliOptions
     * @return CliOptions pointer, bug exception if not initialized
     */
    clinterface::RTTCliOptions * getRttCliOptions() const;

    /**
     * @brief getToolkitSettings
     * @return ToolkitSettings pointer, bug exception if not initialized.
     */
    ToolkitSettings * getToolkitSettings() const;

    /**
     * @brief getBatteryConfiguration
     * @return BatteryConfiguration pointer, bug exception if not initialized
     */
    batteries::Configuration * getBatteryConfiguration() const;

    /**
     * @brief getLogger
     * @return Logger pointer, bug exception if not initialized
     */
    Logger * getLogger() const;

private:
    /* Application start time, will be used in naming files, etc. */
    time_t creationTime;
    //std::unique_ptr<CliOptions> cliOptions;
    std::unique_ptr<clinterface::RTTCliOptions> rttCliOptions;
    std::unique_ptr<ToolkitSettings> toolkitSettings;
    std::unique_ptr<batteries::Configuration> batteryConfiguration;
    std::unique_ptr<Logger> logger;
};

} // namespace rtt

#endif // RTT_GLOBALCONTAINER_H

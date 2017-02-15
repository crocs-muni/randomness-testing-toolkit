#include "globalcontainer.h"

namespace rtt {


void GlobalContainer::initCliOptions(int argc, char * argv[]) {
    cliOptions =
            std::make_unique<CliOptions>(CliOptions::getInstance(argc , argv));
}

void GlobalContainer::initToolkitSettings(const std::string & filename) {
    toolkitSettings =
            std::make_unique<ToolkitSettings>(ToolkitSettings::getInstance(filename));
}

void GlobalContainer::initBatteriesConfiguration(const std::string & filename) {
    using namespace batteries;
    batteryConfiguration =
            std::make_unique<Configuration>(Configuration::getInstance(filename));
}

void GlobalContainer::initLogger(const std::string & logId, bool toCout) {
    if(cliOptions == nullptr)
        raiseBugException("can't initialize logger before command line options are init'd");
    if(toolkitSettings == nullptr)
        raiseBugException("can't initialize logger before toolkit settings are init'd");

    auto logFilePath = Utils::getLogFilePath(creationTime,
                                             toolkitSettings->getLoggerRunLogDir(),
                                             cliOptions->getInputDataPath(),
                                             Constants::batteryToShortString(
                                                 cliOptions->getBatteryId())
                                             );

    logger = std::unique_ptr<Logger>(new Logger(logId , logFilePath , toCout));
}

CliOptions * GlobalContainer::getCliOptions() const {
    if(cliOptions == nullptr)
        raiseBugException("cliOptions were not initialized");

    return cliOptions.get();
}

ToolkitSettings * GlobalContainer::getToolkitSettings() const {
    if(toolkitSettings == nullptr)
        raiseBugException("toolkitSettings were not initialized");

    return toolkitSettings.get();
}

batteries::Configuration * GlobalContainer::getBatteryConfiguration() const {
    if(batteryConfiguration == nullptr)
        raiseBugException("batteryConfiguration was not initialized");

    return batteryConfiguration.get();
}

Logger * GlobalContainer::getLogger() const {
    if(logger == nullptr)
        raiseBugException("logger was not initialized");

    return logger.get();
}

time_t GlobalContainer::getCreationTime() const {
    return creationTime;
}


} // namespace rtt

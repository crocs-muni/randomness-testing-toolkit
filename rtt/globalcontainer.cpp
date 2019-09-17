#include "globalcontainer.h"

namespace rtt {


void GlobalContainer::initRttCliOptions(int argc, char * argv[]) {
    using namespace clinterface;
    rttCliOptions =
            std::make_unique<RTTCliOptions>(RTTCliOptions::getInstance(argc , argv));
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
    if(rttCliOptions == nullptr)
        raiseBugException("can't initialize logger before command line options are init'd");
    if(toolkitSettings == nullptr)
        raiseBugException("can't initialize logger before toolkit settings are init'd");

    auto logFilePath = Utils::getLogFilePath(creationTime,
                                             toolkitSettings->getLoggerRunLogDir(),
                                             rttCliOptions->getInputDataPath(),
                                             rttCliOptions->getBatteryArg().getShortName(),
                                             rttCliOptions->hasJid() ? rttCliOptions->getJid() : 0
                       );

    logger = std::unique_ptr<Logger>(new Logger(logId , logFilePath , toCout));
}

clinterface::RTTCliOptions * GlobalContainer::getRttCliOptions() const {
    if(rttCliOptions == nullptr)
        raiseBugException("rttCliOptions were not initialized");

    return rttCliOptions.get();
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

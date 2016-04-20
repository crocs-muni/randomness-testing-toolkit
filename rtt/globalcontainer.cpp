#include "globalcontainer.h"

namespace rtt {


void GlobalContainer::initCliOptions(int argc, char * argv[]) {
    cliOptions =
            std::make_shared<CliOptions>(CliOptions::getInstance(argc , argv));
}

void GlobalContainer::initToolkitSettings(const std::string & filename) {
    toolkitSettings =
            std::make_shared<ToolkitSettings>(ToolkitSettings::getInstance(filename));
}

void GlobalContainer::initBatteriesConfiguration(const std::string & filename) {
    using namespace batteries;
    batteryConfiguration =
            std::make_shared<Configuration>(Configuration::getInstance(filename));
}

std::shared_ptr<CliOptions> GlobalContainer::getCliOptions() const {
    if(cliOptions == nullptr)
        raiseBugException("cliOptions were not initialized");

    return cliOptions;
}
std::shared_ptr<ToolkitSettings> GlobalContainer::getToolkitSettings() const {
    if(toolkitSettings == nullptr)
        raiseBugException("toolkitSettings were not initialized");

    return toolkitSettings;
}
std::shared_ptr<batteries::Configuration> GlobalContainer::getBatteryConfiguration() const {
    if(batteryConfiguration == nullptr)
        raiseBugException("batteriesConfiguration was not initialized");

    return batteryConfiguration;
}

} // namespace rtt

#include "battery-tu01.h"

namespace rtt {
namespace batteries {
namespace testu01 {

const std::string Battery::XPATH_LOG_DIRECTORY = "TOOLKIT_SETTINGS/LOGGER/TESTU01_DIR";

std::unique_ptr<Battery> Battery::getInstance(const CliOptions & options) {
    std::unique_ptr<Battery> battery (new Battery());

    TiXmlNode * cfgRoot = NULL;
    loadXMLFile(cfgRoot , options.getInputCfgPath());

    std::string logFileName;
    logFileName = getXMLElementValue(cfgRoot , XPATH_LOG_DIRECTORY);
    if(logFileName.empty())
        throw std::runtime_error("empty tag: " + XPATH_LOG_DIRECTORY);

    if(logFileName.back() != '/')
        logFileName.append("/");
    logFileName.append(Utils::getDateTime() + "-");
    logFileName.append(options.getBinFilePath() + ".log");
    battery->logFileName = std::move(logFileName);

    for(int i : options.getTestConsts()) {
        Test test = Test::getInstance(i , options , cfgRoot);
        battery->tests.push_back(std::move(test));
    }

    delete cfgRoot;
    return battery;
}

void Battery::runTests() {
    for(auto & i : tests)
        i.execute();

    executed = true;
}

void Battery::processStoredResults() {
    if(!executed)
        throw std::runtime_error("can't process results before execution of battery");

    std::cout << "This function stores battery log." << std::endl;

    std::string batteryLog;
    for(auto & i : tests)
        i.appendTestLog(batteryLog);

    Utils::createDirectory(Utils::getPathWithoutLastItem(logFileName));
    Utils::saveStringToFile(logFileName , batteryLog);
}

} // namespace testu01
} // namespace batteries
} // namespace rtt


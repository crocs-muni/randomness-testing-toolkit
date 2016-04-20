#include "ibattery-batt.h"

#include "rtt/batteries/dieharder/battery-dh.h"
#include "rtt/batteries/niststs/battery-sts.h"
#include "rtt/batteries/testu01/battery-tu01.h"

namespace rtt {
namespace batteries {

std::unique_ptr<IBattery> IBattery::getInstance(const GlobalContainer & container) {
    /* Pick correct derived class */
    switch(container.getCliOptions()->getBattery()) {
    case Constants::Battery::DIEHARDER:
        return dieharder::Battery::getInstance(container);
    case Constants::Battery::NIST_STS:
        return niststs::Battery::getInstance(container);
    case Constants::Battery::TU01_SMALLCRUSH:
    case Constants::Battery::TU01_CRUSH:
    case Constants::Battery::TU01_BIGCRUSH:
    case Constants::Battery::TU01_RABBIT:
    case Constants::Battery::TU01_ALPHABIT:
        return testu01::Battery::getInstance(container);
    default:
        raiseBugException("invalid battery");
    }
}

void IBattery::runTests() {
    if(executed)
        throw RTTException(objectInfo , "battery was already executed");

    TestRunner::executeTests(std::ref(tests));
    executed = true;
}

IBattery::IBattery(const GlobalContainer & container) {
    creationTime         = Utils::getRawTime();
    cliOptions           = container.getCliOptions();
    batteryConfiguration = container.getBatteryConfiguration();
    toolkitSettings      = container.getToolkitSettings();

    std::cout << "[INFO] Processing file: " << cliOptions->getBinFilePath()
              << std::endl;

    battery = cliOptions->getBattery();
    objectInfo = Constants::batteryToString(battery);
    logFilePath = toolkitSettings->getLoggerBatteryDir(battery);
    logFilePath.append(Utils::formatRawTime(creationTime , "%Y%m%d%H%M%S"));

    logFilePath.append("-" +
                       Utils::getLastItemInPath(cliOptions->getBinFilePath()) +
                       ".log");

    storage = output::IOutput::getInstance(container , creationTime);
    std::vector<int> testIndices = cliOptions->getTestConsts();
    if(testIndices.empty())
        testIndices = batteryConfiguration->getBatteryDefaultTests(battery);
    if(testIndices.empty())
        throw RTTException(objectInfo , "no tests were set for execution");

    for(int i : testIndices) {
        std::unique_ptr<ITest> test = ITest::getInstance(i , container);
        tests.push_back(std::move(test));
    }
}

} // namespace batteries
} // namespace rtt

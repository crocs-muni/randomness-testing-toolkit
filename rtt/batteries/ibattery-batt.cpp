#include "ibattery-batt.h"

#include "rtt/batteries/dieharder/battery-dh.h"
#include "rtt/batteries/niststs/battery-sts.h"
#include "rtt/batteries/testu01/battery-tu01.h"

namespace rtt {
namespace batteries {

std::unique_ptr<IBattery> IBattery::getInstance(const Globals & globals) {
    std::unique_ptr<IBattery> b;

    /* Pick correct derived class */
    switch(globals.getCliOptions()->getBattery()) {
    case Constants::Battery::DIEHARDER:
        b = dieharder::Battery::getInstance(globals);
        break;
    case Constants::Battery::NIST_STS:
        b = niststs::Battery::getInstance(globals);
        break;
    case Constants::Battery::TU01_SMALLCRUSH:
    case Constants::Battery::TU01_CRUSH:
    case Constants::Battery::TU01_BIGCRUSH:
    case Constants::Battery::TU01_RABBIT:
    case Constants::Battery::TU01_ALPHABIT:
        b = testu01::Battery::getInstance(globals);
        break;
    default:raiseBugException("invalid battery");
    }
    if(!b->initialized)
        raiseBugException("base class variables are not initialized");

    return b;
}

void IBattery::runTests() {
    if(!initialized)
        raiseBugException("base class variables are not initialized");

    if(executed)
        throw RTTException(objectInfo , "battery was already executed");

    TestRunner::executeTests(std::ref(tests));
    executed = true;
}

void IBattery::initializeVariables(const Globals & globals) {
    /* Set variables in base class */
    creationTime = Utils::getRawTime();

    cliOptions = globals.getCliOptions();
    batteryConfiguration = globals.getBatteryConfiguration();
    toolkitSettings = globals.getToolkitSettings();

    std::cout << "[INFO] Processing file: " << cliOptions->getBinFilePath()
              << std::endl;

    battery = cliOptions->getBattery();
    objectInfo = Constants::batteryToString( battery);
    logFilePath = toolkitSettings->getLoggerBatteryDir(battery);
    logFilePath.append(Utils::formatRawTime(creationTime , "%Y%m%d%H%M%S"));
    logFilePath.append("-" +
                          Utils::getLastItemInPath(cliOptions->getBinFilePath()) +
                          ".log");
    /* Result storage */
    storage = output::IOutput::getInstance(globals , creationTime);

    /* Creating test objects - test getInstance will handle picking
     * correct derived class */
    std::vector<int> testIndices = cliOptions->getTestConsts();
    if(testIndices.empty())
        testIndices = batteryConfiguration->getBatteryDefaultTests(battery);
    if(testIndices.empty())
        throw RTTException(objectInfo , "no tests were set for execution");

    for(int i : testIndices) {
        std::unique_ptr<ITest> test = ITest::getInstance(i , globals);
        tests.push_back(std::move(test));
    }

    initialized = true;
}

} // namespace batteries
} // namespace rtt

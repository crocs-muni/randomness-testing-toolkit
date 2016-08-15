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
    case Constants::Battery::TU01_BLOCK_ALPHABIT:
        return testu01::Battery::getInstance(container);
    default:
        raiseBugException(Strings::ERR_INVALID_BATTERY);
    }
}

void IBattery::runTests() {
    if(executed)
        throw RTTException(objectInfo , Strings::BATT_ERR_ALREADY_EXECUTED);

    logger->info(objectInfo + ": Test execution started!");
    /* Tests will create output file in output directory */
    Utils::createDirectory(toolkitSettings->getLoggerBatteryDir(battId));
    TestRunner::executeTests(logger , std::ref(tests) , toolkitSettings->getExecMaximumThreads());
    logger->info(objectInfo + ": Test execution finished!");
    executed = true;
}

IBattery::IBattery(const GlobalContainer & container) {
    cliOptions           = container.getCliOptions();
    batteryConfiguration = container.getBatteryConfiguration();
    toolkitSettings      = container.getToolkitSettings();
    logger               = container.getLogger();
    storage              = storage::IStorage::getInstance(container);

    creationTime = container.getCreationTime();
    battId       = cliOptions->getBattery();
    objectInfo   = Constants::batteryToString(battId);
    logger->info(objectInfo + Strings::BATT_INFO_PROCESSING_FILE + cliOptions->getBinFilePath());

    std::vector<int> testIndices = cliOptions->getTestConsts();
    if(testIndices.empty())
        testIndices = batteryConfiguration->getBatteryDefaultTests(battId);
    if(testIndices.empty())
        throw RTTException(objectInfo , Strings::BATT_ERR_NO_TESTS);

    for(int i : testIndices) {
        std::unique_ptr<ITest> test = ITest::getInstance(i , container);
        tests.push_back(std::move(test));
    }
}

} // namespace batteries
} // namespace rtt

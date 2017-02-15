#include "ibattery-batt.h"

#include "rtt/batteries/dieharder/battery-dh.h"
#include "rtt/batteries/niststs/battery-sts.h"
#include "rtt/batteries/testu01/battery-tu01.h"

#include "rtt/batteries/testrunner-batt.h"

namespace rtt {
namespace batteries {

std::unique_ptr<IBattery> IBattery::getInstance(const GlobalContainer & cont) {
    /* Pick correct derived class */
    switch(cont.getCliOptions()->getBatteryId()) {
        case Constants::Battery::DIEHARDER:
            return dieharder::Battery::getInstance(cont);
        case Constants::Battery::NIST_STS:
            return niststs::Battery::getInstance(cont);
        case Constants::Battery::TU01_SMALLCRUSH:
        case Constants::Battery::TU01_CRUSH:
        case Constants::Battery::TU01_BIGCRUSH:
        case Constants::Battery::TU01_RABBIT:
        case Constants::Battery::TU01_ALPHABIT:
        case Constants::Battery::TU01_BLOCK_ALPHABIT:
            return testu01::Battery::getInstance(cont);
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

    /* Get all variations from tests and execute them parallely. */
    std::vector<IVariant *> variants;
    for(const auto & test : tests) {
        auto testVars = test->getVariants();
        variants.insert(variants.end(), testVars.begin(), testVars.end());
    }
    TestRunner::executeTests(logger, variants,
                             toolkitSettings->getExecMaximumThreads());

    logger->info(objectInfo + ": Test execution finished!");
    executed = true;
}

IBattery::IBattery(const GlobalContainer & cont) {
    cliOptions           = cont.getCliOptions();
    batteryConfiguration = cont.getBatteryConfiguration();
    toolkitSettings      = cont.getToolkitSettings();
    logger               = cont.getLogger();

    creationTime = cont.getCreationTime();
    battId       = cliOptions->getBatteryId();
    objectInfo   = Constants::batteryToString(battId);
    logger->info(objectInfo + Strings::BATT_INFO_PROCESSING_FILE + cliOptions->getInputDataPath());

    std::vector<int> testIndices = cliOptions->getTestConsts();
    if(testIndices.empty())
        testIndices = batteryConfiguration->getBatteryDefaultTests(battId);
    if(testIndices.empty())
        throw RTTException(objectInfo , Strings::BATT_ERR_NO_TESTS);

    for(const int & i : testIndices) {
        tests.push_back(ITest::getInstance(i , cont));
    }
}

} // namespace batteries
} // namespace rtt

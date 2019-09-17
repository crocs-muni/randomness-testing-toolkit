#include "ibattery-batt.h"

#include "rtt/batteries/dieharder/battery-dh.h"
#include "rtt/batteries/niststs/battery-sts.h"
#include "rtt/batteries/testu01/battery-tu01.h"

#include "rtt/batteries/testrunner-batt.h"

#ifdef _WIN32
#include <direct.h>
// MSDN recommends against using getcwd & chdir names
#define cwd _getcwd
#define cd _chdir
#else
#include "unistd.h"
#define cwd getcwd
#define cd chdir
#endif


namespace rtt {
namespace batteries {

std::unique_ptr<IBattery> IBattery::getInstance(const GlobalContainer & cont) {
    /* Pick correct derived class */
    switch(cont.getRttCliOptions()->getBatteryId()) {
        case Constants::BatteryID::DIEHARDER:
            return dieharder::Battery::getInstance(cont);
        case Constants::BatteryID::NIST_STS:
            return niststs::Battery::getInstance(cont);
        case Constants::BatteryID::TU01_SMALLCRUSH:
        case Constants::BatteryID::TU01_CRUSH:
        case Constants::BatteryID::TU01_BIGCRUSH:
        case Constants::BatteryID::TU01_RABBIT:
        case Constants::BatteryID::TU01_ALPHABIT:
        case Constants::BatteryID::TU01_BLOCK_ALPHABIT:
            return testu01::Battery::getInstance(cont);
        default:
            raiseBugException(Strings::ERR_INVALID_BATTERY);
    }
}

void IBattery::runTests() {
    if(executed)
        throw RTTException(objectInfo , Strings::BATT_ERR_ALREADY_EXECUTED);

    if (rttCliOptions->hasResultsPathPrefix()){
        if (cd(rttCliOptions->getResultsPathPrefix().c_str()) != 0){
            raiseBugException(std::string("Could not change dir to ") + rttCliOptions->getResultsPathPrefix());
        }
    }

    logger->info(objectInfo + ": Test execution started!");
    /* Tests will create output file in output directory */
    Utils::createDirectory(toolkitSettings->getLoggerBatteryDir(battery));

    /* Get all variations from tests and execute them parallely. */
    std::vector<IVariant *> variants;
    for(const auto & test : tests) {
        auto testVars = test->getVariants();
        variants.insert(variants.end(), testVars.begin(), testVars.end());
    }
    TestRunner::executeTests(logger, variants,
                             toolkitSettings->getExecMaximumThreads(),
                             toolkitSettings->getExecTestTimeout());

    logger->info(objectInfo + ": Test execution finished!");
    executed = true;
}

IBattery::IBattery(const GlobalContainer & cont) {
    rttCliOptions        = cont.getRttCliOptions();
    batteryConfiguration = cont.getBatteryConfiguration();
    toolkitSettings      = cont.getToolkitSettings();
    logger               = cont.getLogger();

    creationTime = cont.getCreationTime();
    battery      = rttCliOptions->getBatteryArg();
    objectInfo   = battery.getName();
    logger->info(objectInfo + Strings::BATT_INFO_PROCESSING_FILE + rttCliOptions->getInputDataPath());

    std::vector<int> testIndices = rttCliOptions->getTestConsts();
    if(testIndices.empty())
        testIndices = batteryConfiguration->getBatteryDefaultTests(battery);
    if(testIndices.empty())
        throw RTTException(objectInfo , Strings::BATT_ERR_NO_TESTS);

    for(const int & i : testIndices) {
        tests.push_back(ITest::getInstance(objectInfo, i, cont));
    }
}

} // namespace batteries
} // namespace rtt

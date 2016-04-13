#include "itest-batt.h"

#include "rtt/batteries/niststs/test-sts.h"
#include "rtt/batteries/dieharder/test-dh.h"
#include "rtt/batteries/testu01/test-tu01.h"

namespace rtt {
namespace batteries {

std::unique_ptr<ITest> ITest::getInstance(int testIndex,
                                          const Globals & globals) {
    std::unique_ptr<ITest> t;

    switch(globals.getCliOptions()->getBattery()) {
    case Constants::Battery::DIEHARDER:
        t = dieharder::Test::getInstance(testIndex , globals);
        break;
    case Constants::Battery::NIST_STS:
        t = niststs::Test::getInstance(testIndex , globals);
        break;
    case Constants::Battery::TU01_SMALLCRUSH:
    case Constants::Battery::TU01_CRUSH:
    case Constants::Battery::TU01_BIGCRUSH:
    case Constants::Battery::TU01_RABBIT:
    case Constants::Battery::TU01_ALPHABIT:
        t = testu01::Test::getInstance(testIndex , globals);
        break;
    default:raiseBugException("invalid battery");
    }
    /* Some checks here */
    return t;
}

void ITest::initializeVariables(int ti , const Globals & globals) {
    /* Not yet used */
    cliOptions = globals.getCliOptions();
    toolkitSettings = globals.getToolkitSettings();
    batteryConfiguration = globals.getBatteryConfiguration();
    testIndex = ti;
    battery = cliOptions->getBattery();
    objectInfo = Constants::batteryToString(battery) + " - test " + Utils::itostr(testIndex);

    binaryDataPath = cliOptions->getBinFilePath();
    if(binaryDataPath.empty())
        raiseBugException("empty input binary data path");

    executablePath = toolkitSettings->getBinaryBattery(battery);
    if(executablePath.empty())
        raiseBugException("empty executable path");
}

} // namespace batteries
} // namespace rtt


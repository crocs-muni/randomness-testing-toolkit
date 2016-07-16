#include "itest-batt.h"

#include "rtt/batteries/niststs/test-sts.h"
#include "rtt/batteries/dieharder/test-dh.h"
#include "rtt/batteries/testu01/test-tu01.h"

namespace rtt {
namespace batteries {

std::unique_ptr<ITest> ITest::getInstance(int testIndex , const GlobalContainer & container) {
    switch(container.getCliOptions()->getBattery()) {
    case Constants::Battery::DIEHARDER:
        return dieharder::Test::getInstance(testIndex , container);
    case Constants::Battery::NIST_STS:
        return niststs::Test::getInstance(testIndex , container);
    case Constants::Battery::TU01_SMALLCRUSH:
    case Constants::Battery::TU01_CRUSH:
    case Constants::Battery::TU01_BIGCRUSH:
    case Constants::Battery::TU01_RABBIT:
    case Constants::Battery::TU01_ALPHABIT:
        return testu01::Test::getInstance(testIndex , container);
    default:
        raiseBugException(Strings::ERR_INVALID_BATTERY);
    }
}

bool ITest::wasExecuted() const {
    return executed;
}

std::string ITest::getLogicName() const {
    return logicName;
}

int ITest::getTestIndex() const {
    return testIndex;
}

std::vector<tTestPvals> ITest::getResults() const {
    if(!executed)
        throw RTTException(objectInfo , Strings::TEST_ERR_NO_EXEC_RES);

    return results;
}

ITest::ITest(int testIndex, const GlobalContainer & container) {
    cliOptions           = container.getCliOptions();
    toolkitSettings      = container.getToolkitSettings();
    batteryConfiguration = container.getBatteryConfiguration();
    logger               = container.getLogger();
    this->testIndex      = testIndex;
    battery              = cliOptions->getBattery();
    binaryDataPath       = cliOptions->getBinFilePath();
    executablePath       = toolkitSettings->getBinaryBattery(battery);
    logFilePath          = Utils::createLogFileName(container.getCreationTime(),
                                                    toolkitSettings->getLoggerBatteryDir(battery),
                                                    binaryDataPath);

    objectInfo =
            Constants::batteryToString(battery) + " - test " + Utils::itostr(testIndex);

    if(binaryDataPath.empty())
        raiseBugException(Strings::TEST_ERR_NO_BINARY_DATA);

    if(executablePath.empty())
        raiseBugException(Strings::TEST_ERR_NO_EXECUTABLE);
}

} // namespace batteries
} // namespace rtt


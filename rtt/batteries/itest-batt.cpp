#include "itest-batt.h"

#include "rtt/batteries/niststs/test-sts.h"
#include "rtt/batteries/dieharder/test-dh.h"
#include "rtt/batteries/testu01/test-tu01.h"

namespace rtt {
namespace batteries {

std::unique_ptr<ITest> ITest::getInstance(int testId,
                                          const GlobalContainer & cont) {
    switch(cont.getCliOptions()->getBatteryId()) {
        case Constants::Battery::DIEHARDER:
            return dieharder::Test::getInstance(testId , cont);
        case Constants::Battery::NIST_STS:
            return niststs::Test::getInstance(testId , cont);
        case Constants::Battery::TU01_SMALLCRUSH:
        case Constants::Battery::TU01_CRUSH:
        case Constants::Battery::TU01_BIGCRUSH:
        case Constants::Battery::TU01_RABBIT:
        case Constants::Battery::TU01_ALPHABIT:
        case Constants::Battery::TU01_BLOCK_ALPHABIT:
            return testu01::Test::getInstance(testId , cont);
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
    return testId;
}

std::vector<tTestPvals> ITest::getResults() const {
    if(!executed)
        throw RTTException(objectInfo , Strings::TEST_ERR_NO_EXEC_RES);

    return results;
}

std::string ITest::getBatteryStdErr() const {
    if(!executed)
        throw RTTException(objectInfo , Strings::TEST_ERR_NO_EXEC_RES);

    //return batteryOutput.at(0).getStdErr();
    return {};
}

std::vector<std::string> ITest::getBatteryErrors() {
    if(!executed)
        throw RTTException(objectInfo , Strings::TEST_ERR_NO_EXEC_RES);

    //return batteryOutput.at(0).getErrors();
    return {};
}

std::vector<std::string> ITest::getBatteryWarnings() {
    if(!executed)
        throw RTTException(objectInfo , Strings::TEST_ERR_NO_EXEC_RES);

    //return batteryOutput.at(0).getWarnings();
    return {};
}

std::vector<IVariant *> ITest::getVariants() const {
    std::vector<IVariant *> rval;
    for(const auto & el : variants)
        rval.push_back(el.get());

    return rval;
}

ITest::ITest(int testId, const GlobalContainer & cont) {
    cliOptions           = cont.getCliOptions();
    toolkitSettings      = cont.getToolkitSettings();
    batteryConfiguration = cont.getBatteryConfiguration();
    logger               = cont.getLogger();
    this->testId         = testId;
    battId               = cliOptions->getBatteryId();
    logFilePath          =
            Utils::createLogFileName(
                cont.getCreationTime(),
                toolkitSettings->getLoggerBatteryDir(battId),
                cliOptions->getBinFilePath());

    objectInfo =
            Constants::batteryToString(battId) +
            " - test " + Utils::itostr(testId);



    uint varCount = batteryConfiguration->getTestVariantsCount(battId, testId);
    if(varCount == 0) {
        variants.push_back(IVariant::getInstance(testId, 0, cont));
    } else {
        for(uint varIdx = 0; varIdx < varCount; ++varIdx)
            variants.push_back(IVariant::getInstance(testId, varIdx, cont));
    }
}

Constants::Battery ITest::getBattId() const
{
    return battId;
}

} // namespace batteries
} // namespace rtt


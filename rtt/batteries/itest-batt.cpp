#include "itest-batt.h"

#include "rtt/batteries/niststs/test-sts.h"
#include "rtt/batteries/dieharder/test-dh.h"
#include "rtt/batteries/testu01/test-tu01.h"

namespace rtt {
namespace batteries {

std::unique_ptr<ITest> ITest::getInstance(std::string battObjInf, int testId,
                                          const GlobalContainer & cont) {
    switch(cont.getRttCliOptions()->getBatteryId()) {
        case Constants::BatteryID::DIEHARDER:
            return dieharder::Test::getInstance(battObjInf, testId, cont);
        case Constants::BatteryID::NIST_STS:
            return niststs::Test::getInstance(battObjInf, testId , cont);
        case Constants::BatteryID::TU01_SMALLCRUSH:
        case Constants::BatteryID::TU01_CRUSH:
        case Constants::BatteryID::TU01_BIGCRUSH:
        case Constants::BatteryID::TU01_RABBIT:
        case Constants::BatteryID::TU01_ALPHABIT:
        case Constants::BatteryID::TU01_BLOCK_ALPHABIT:
            return testu01::Test::getInstance(battObjInf, testId , cont);
        default:
            raiseBugException(Strings::ERR_INVALID_BATTERY);
    }
}

std::string ITest::getLogicName() const {
    return logicName;
}

int ITest::getTestId() const {
    return testId;
}

std::vector<IVariant *> ITest::getVariants() const {
    return Utils::getRawPtrs(variants);
}

ITest::ITest(std::string battObjInf, int testId, const GlobalContainer & cont) {
    rttCliOptions        = cont.getRttCliOptions();
    toolkitSettings      = cont.getToolkitSettings();
    batteryConfiguration = cont.getBatteryConfiguration();
    logger               = cont.getLogger();
    this->testId         = testId;
    battery              = rttCliOptions->getBatteryArg();
    logicName            = TestConstants::getTestLogicName(battery, testId);
    objectInfo           =
            battObjInf + " - " + logicName +
            " (" + Utils::itostr(testId) + ")";

    uint varCount = batteryConfiguration->getTestVariantsCount(battery, testId);
    if(varCount == 0) {
        variants.push_back(IVariant::getInstance(testId, objectInfo, 0, cont));
    } else {
        for(uint varIdx = 0; varIdx < varCount; ++varIdx)
            variants.push_back(IVariant::getInstance(testId, objectInfo, varIdx, cont));
    }
}

Logger * ITest::getLogger() const {
    return logger;
}

BatteryArg ITest::getBatteryArg() const {
    return battery;
}

} // namespace batteries
} // namespace rtt


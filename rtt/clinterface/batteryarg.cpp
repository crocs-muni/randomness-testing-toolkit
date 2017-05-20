#include "batteryarg.h"

namespace rtt {
namespace clinterface {

BatteryArg::BatteryArg() {}

BatteryArg::BatteryArg(const std::string & battery) {
    init(battery);
}

std::string BatteryArg::getName(Constants::BatteryID batteryId) {
    switch(batteryId) {
    case Constants::BatteryID::NIST_STS:
        return "NIST Statistical Testing Suite";
    case Constants::BatteryID::DIEHARDER:
        return "Dieharder";
    case Constants::BatteryID::TU01_SMALLCRUSH:
        return "TestU01 Small Crush";
    case Constants::BatteryID::TU01_CRUSH:
        return "TestU01 Crush";
    case Constants::BatteryID::TU01_BIGCRUSH:
        return "TestU01 Big Crush";
    case Constants::BatteryID::TU01_RABBIT:
        return "TestU01 Rabbit";
    case Constants::BatteryID::TU01_ALPHABIT:
        return "TestU01 Alphabit";
    case Constants::BatteryID::TU01_BLOCK_ALPHABIT:
        return "TestU01 Block Alphabit";
    default:
        raiseBugException("invalid battery id");
    }
}

std::string BatteryArg::getShortName(Constants::BatteryID batteryId) {
    switch(batteryId) {
    case Constants::BatteryID::NIST_STS:
        return "nist_sts";
    case Constants::BatteryID::DIEHARDER:
        return "dieharder";
    case Constants::BatteryID::TU01_SMALLCRUSH:
        return "tu01_smallcrush";
    case Constants::BatteryID::TU01_CRUSH:
        return "tu01_crush";
    case Constants::BatteryID::TU01_BIGCRUSH:
        return "tu01_bigcrush";
    case Constants::BatteryID::TU01_RABBIT:
        return "tu01_rabbit";
    case Constants::BatteryID::TU01_ALPHABIT:
        return "tu01_alphabit";
    case Constants::BatteryID::TU01_BLOCK_ALPHABIT:
        return "tu01_blockalphabit";
    default:
        raiseBugException("invalid battery id");
    }
}

uint BatteryArg::getExpectedExitCode(Constants::BatteryID batteryId) {
    switch(batteryId) {
    case Constants::BatteryID::NIST_STS:
        return 256;
    case Constants::BatteryID::DIEHARDER:
    case Constants::BatteryID::TU01_SMALLCRUSH:
    case Constants::BatteryID::TU01_CRUSH:
    case Constants::BatteryID::TU01_BIGCRUSH:
    case Constants::BatteryID::TU01_RABBIT:
    case Constants::BatteryID::TU01_ALPHABIT:
    case Constants::BatteryID::TU01_BLOCK_ALPHABIT:
        return 0;
    default:
        raiseBugException("invalid battery id");
    }
}

Constants::BatteryID BatteryArg::getBatteryId() const {
    initCheck();

    return batteryId;
}

std::string BatteryArg::getName() const {
    initCheck();

    return name;
}

std::string BatteryArg::getShortName() const {
    initCheck();

    return shortName;
}

uint BatteryArg::getExpectedExitCode() const {
    initCheck();

    return expectedExitCode;
}

bool BatteryArg::isInTU01Family() const {
    initCheck();

    switch(batteryId) {
    case Constants::BatteryID::NIST_STS:
    case Constants::BatteryID::DIEHARDER:
        return false;
    case Constants::BatteryID::TU01_SMALLCRUSH:
    case Constants::BatteryID::TU01_CRUSH:
    case Constants::BatteryID::TU01_BIGCRUSH:
    case Constants::BatteryID::TU01_RABBIT:
    case Constants::BatteryID::TU01_ALPHABIT:
    case Constants::BatteryID::TU01_BLOCK_ALPHABIT:
        return true;
    default:
        raiseBugException("invalid battery id");
    }
}

bool BatteryArg::isInTU01CrushFamily() const {
    initCheck();

    switch(batteryId) {
    case Constants::BatteryID::NIST_STS:
    case Constants::BatteryID::DIEHARDER:
    case Constants::BatteryID::TU01_RABBIT:
    case Constants::BatteryID::TU01_ALPHABIT:
    case Constants::BatteryID::TU01_BLOCK_ALPHABIT:
        return false;
    case Constants::BatteryID::TU01_SMALLCRUSH:
    case Constants::BatteryID::TU01_CRUSH:
    case Constants::BatteryID::TU01_BIGCRUSH:
        return true;
    default:
        raiseBugException("invalid battery id");
    }
}

bool BatteryArg::isInTU01BitFamily() const {
    initCheck();

    switch(batteryId) {
    case Constants::BatteryID::NIST_STS:
    case Constants::BatteryID::DIEHARDER:
    case Constants::BatteryID::TU01_SMALLCRUSH:
    case Constants::BatteryID::TU01_CRUSH:
    case Constants::BatteryID::TU01_BIGCRUSH:
        return false;
    case Constants::BatteryID::TU01_RABBIT:
    case Constants::BatteryID::TU01_ALPHABIT:
    case Constants::BatteryID::TU01_BLOCK_ALPHABIT:
        return true;
    default:
        raiseBugException("invalid battery id");
    }
}

bool BatteryArg::isInTU01AlphabitFamily() const {
    initCheck();

    switch(batteryId) {
    case Constants::BatteryID::NIST_STS:
    case Constants::BatteryID::DIEHARDER:
    case Constants::BatteryID::TU01_SMALLCRUSH:
    case Constants::BatteryID::TU01_CRUSH:
    case Constants::BatteryID::TU01_BIGCRUSH:
    case Constants::BatteryID::TU01_RABBIT:
        return false;
    case Constants::BatteryID::TU01_ALPHABIT:
    case Constants::BatteryID::TU01_BLOCK_ALPHABIT:
        return true;
    default:
        raiseBugException("invalid battery id");
    }
}

Constants::BatteryID BatteryArg::getBatteryIdFromShortName(const std::string & shortName){
    Constants::BatteryID batteryId;
    for(int i = 1; i < static_cast<int>(Constants::BatteryID::LAST_ITEM); ++i) {
        batteryId = static_cast<Constants::BatteryID>(i);
        if(shortName == getShortName(batteryId))
            return batteryId;
    }
    throw std::runtime_error("unknown battery argument: " + shortName);
}

void BatteryArg::init(const std::string & shortName) {
    if(initialized)
        raiseBugException("BatteryArg is already initialized");

    batteryId = getBatteryIdFromShortName(shortName);
    this->shortName = shortName;
    name = getName(batteryId);
    expectedExitCode = getExpectedExitCode(batteryId);
    initialized = true;
}

void BatteryArg::initCheck() const {
    if(!initialized)
        raiseBugException("BatteryArg is not initialized");
}

} // namespace clinterface
} // namespace rtt

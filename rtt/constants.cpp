#include "rtt/constants.h"

namespace rtt {

/* Constant definition */
const std::string Constants::FILE_DEFAULT_CFG_PATH = "./config.xml";
const std::string Constants::FILE_TOOLKIT_SETTINGS = "./toolkit.settings";

const double Constants::MATH_ALPHA = 0.01;
const double Constants::MATH_EPS   = 1e-8;

std::string Constants::batteryToString(Battery batteryConstant) {
    switch(batteryConstant) {
    case Battery::DIEHARDER:         return "Dieharder";
    case Battery::NIST_STS:          return "NIST Statistical Test Suite";
    case Battery::TU01_SMALLCRUSH:   return "TestU01 Small Crush";
    case Battery::TU01_CRUSH:        return "TestU01 Crush";
    case Battery::TU01_BIGCRUSH:     return "TestU01 Big Crush";
    case Battery::TU01_RABBIT:       return "TestU01 Rabbit";
    case Battery::TU01_ALPHABIT:     return "TestU01 Alphabit";
    default:raiseBugException("invalid battery");
    }
}

} // namespace rtt

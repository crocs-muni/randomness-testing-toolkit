#include "rtt/constants.h"

namespace rtt {

/* Constant definition */
const std::string Constants::FILE_DEFAULT_CFG_PATH = "./config.xml";

const double Constants::MATH_ALPHA = 0.01;
const double Constants::MATH_EPS   = 1e-8;

std::string Constants::batteryToString(int batteryConstant) {
    switch(batteryConstant) {
    case BATTERY_DIEHARDER:         return "Dieharder";
    case BATTERY_NIST_STS:          return "NIST Statistical Test Suite";
    case BATTERY_TU01_SMALLCRUSH:   return "TestU01 Small Crush";
    case BATTERY_TU01_CRUSH:        return "TestU01 Crush";
    case BATTERY_TU01_BIGCRUSH:     return "TestU01 Big Crush";
    case BATTERY_TU01_RABBIT:       return "TestU01 Rabbit";
    case BATTERY_TU01_ALPHABIT:     return "TestU01 Alphabit";
    case BATTERY_EACIRC:            return "EACirc Framework";
    default:
        throw std::runtime_error("unknown battery constant: " +
                                 Utils::itostr(batteryConstant));
    }
}

} // namespace rtt

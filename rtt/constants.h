#ifndef RTT_CONSTANTS_H
#define RTT_CONSTANTS_H

#include <string>
#include <stdexcept>

#include "rtt/utils.h"

namespace rtt {

class Constants {
public:
    ///////////////////////////////////////////////
    /******** Toolkit global constants ***********/
    ///////////////////////////////////////////////

    /* Statistical batteries constants */
    /* Constants MUST have consecutive integers assigned */
    static const int BATTERY_DIEHARDER          = 1;
    static const int BATTERY_NIST_STS           = 2;
    static const int BATTERY_TU01_SMALLCRUSH    = 3;
    static const int BATTERY_TU01_CRUSH         = 4;
    static const int BATTERY_TU01_BIGCRUSH      = 5;
    static const int BATTERY_TU01_RABBIT        = 6;
    static const int BATTERY_TU01_ALPHABIT      = 7;
    static const int BATTERY_EACIRC             = 8;

    static const int BATTERY_TOTAL_COUNT        = 8;

    /* Default files locations */
    static const std::string FILE_DEFAULT_CFG_PATH;
    static const std::string FILE_TOOLKIT_SETTINGS;

    /* Math values */
    static const double MATH_ALPHA;
    static const double MATH_EPS;

    ///////////////////////////////////////////////
    /********* Toolkit global methods ************/
    ///////////////////////////////////////////////
    static std::string batteryToString(int batteryConstant);
};

} // namespace rtt

#endif // RTT_CONSTANTS_H


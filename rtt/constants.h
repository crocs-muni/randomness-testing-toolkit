#ifndef RTT_CONSTANTS_H
#define RTT_CONSTANTS_H

#include <string>

#include "rtt/bugexception.h"
#include "rtt/utils.h"

namespace rtt {

class Constants {
public:
    ///////////////////////////////////////////////
    /******** Toolkit global constants ***********/
    ///////////////////////////////////////////////

    /* Statistical batteries constants enum */
    /* Values in enum MUST NOT have assigned other than default values
     * (first is one). Item LAST_ITEM HAVE to be last. Always!
     * Additional battery item should be added before it. */
    enum class Battery {
        DIEHARDER = 1,
        NIST_STS,
        TU01_SMALLCRUSH,
        TU01_CRUSH,
        TU01_BIGCRUSH,
        TU01_RABBIT,
        TU01_ALPHABIT,
        LAST_ITEM
    };
    /*
    static const int BATTERY_DIEHARDER          = 1;
    static const int BATTERY_NIST_STS           = 2;
    static const int BATTERY_TU01_SMALLCRUSH    = 3;
    static const int BATTERY_TU01_CRUSH         = 4;
    static const int BATTERY_TU01_BIGCRUSH      = 5;
    static const int BATTERY_TU01_RABBIT        = 6;
    static const int BATTERY_TU01_ALPHABIT      = 7;
    static const int BATTERY_EACIRC             = 8;

    static const int BATTERY_TOTAL_COUNT        = 8;
    */

    /* Default files locations */
    static const std::string FILE_DEFAULT_CFG_PATH;
    static const std::string FILE_TOOLKIT_SETTINGS;

    /* Math values */
    static const double MATH_ALPHA;
    static const double MATH_EPS;

    ///////////////////////////////////////////////
    /********* Toolkit global methods ************/
    ///////////////////////////////////////////////
    static std::string batteryToString(Battery batteryConstant);
};

} // namespace rtt

#endif // RTT_CONSTANTS_H


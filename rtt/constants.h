#ifndef RTT_CONSTANTS_H
#define RTT_CONSTANTS_H

#include "rtt/strings.h"
#include "rtt/bugexception.h"
//#include "rtt/utils.h"

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

    static std::string batteryToStringShort(Battery batteryConstant);

private:
    Constants () {}
};

} // namespace rtt

#endif // RTT_CONSTANTS_H


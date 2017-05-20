#ifndef RTT_CONSTANTS_H
#define RTT_CONSTANTS_H

#include "rtt/strings.h"
#include "rtt/bugexception.h"
//#include "rtt/utils.h"

namespace rtt {

/**
 * @brief The Constants class contains global constants that are widely used
 */
class Constants {
public:
    /* Statistical batteries constants enum */
    /* Values in enum MUST NOT have assigned other than default values
     * (first is one). Item LAST_ITEM HAVE to be last. Always!
     * Additional battery item MUST be added before it. */
    /* LAST_ITEM must be last because them enums are occasionally iterated
     * and the element serves as ending. */
    enum class BatteryID {
        DIEHARDER = 1,
        NIST_STS,
        TU01_SMALLCRUSH,
        TU01_CRUSH,
        TU01_BIGCRUSH,
        TU01_RABBIT,
        TU01_ALPHABIT,
        TU01_BLOCK_ALPHABIT,
        LAST_ITEM
    };

    enum class ResultStorageID {
        FILE_REPORT = 1,
        DB_MYSQL,
        LAST_ITEM
    };

    /* Default files locations */
    static const std::string FILE_TOOLKIT_SETTINGS;

    /* Math values */
    static const double MATH_ALPHA;
    static const double MATH_EPS;

    /**
     * @brief batteryToString
     * @param battId
     * @return human readable string identifying the battery
     */
    //static std::string batteryToString(Battery battId);

    /**
     * @brief batteryToShortString
     * @param battId id
     * @return short string identifying the battery, used in filenames
     */
    //static std::string batteryToShortString(Battery battId);

    /**
     * @brief getBatteryExpExitCode
     * @param battId
     * @return Expected exit code of the battery executable binary
     */
    //static uint getBatteryExpExitCode(Battery battId);

    /**
     * @brief isInTU01Family Checks whether given battery is in TestU01 family of batteries
     * @param battId
     * @return
     */
    //static bool isInTU01Family(Battery battId);

    /**
     * @brief isInTU01CrushFamily Checks whether given battery is in TestU01 Crush family of batteries
     * @param battId
     * @return
     */
    //static bool isInTU01CrushFamily(Battery battId);

    /**
     * @brief isInTU01BitFamily Checks whether given battery is in
     * TestU01 Bit (rabbit, alphabit, block alphabit) family of batteries
     * @param battId
     * @return
     */
    //static bool isInTU01BitFamily(Battery battId);

    /**
     * @brief isinTU01AlphabitFamily Checks whether given battery is in
     * TestU01 Alphabit (alphabit, block alphabit) family of batteries
     * @param battId
     * @return
     */
    //static bool isinTU01AlphabitFamily(Battery battId);

private:
    Constants () {}
};

} // namespace rtt

#endif // RTT_CONSTANTS_H


#ifndef RTT_CLINTERFACE_BATTERYARG_H
#define RTT_CLINTERFACE_BATTERYARG_H

#include <string>
#include <istream>
#include <ostream>

#include "rtt/constants.h"
#include "rtt/bugexception.h"

namespace rtt {
namespace clinterface {

/**
 * @brief The BatteryArg class Stores battery chosen via
 * command line and information about the battery such as name,
 * short_name (command line) and type of the battery.
 */
class BatteryArg {
public:
    BatteryArg();

    BatteryArg(const std::string & battery);

    static std::string getName(Constants::BatteryID batteryId);

    static std::string getShortName(Constants::BatteryID batteryId);

    static uint getExpectedExitCode(Constants::BatteryID batteryId);

    Constants::BatteryID getBatteryId() const;

    std::string getName() const;

    std::string getShortName() const;

    uint getExpectedExitCode() const;

    bool isInTU01Family() const;

    bool isInTU01CrushFamily() const;

    bool isInTU01BitFamily() const;

    bool isInTU01AlphabitFamily() const;

    friend std::istream & operator>> (std::istream & is, BatteryArg & b) {
        std::string battery;
        is >> battery;
        if(!is.eof() || is.fail())
            return is;

        b.init(battery);
        return is;
    }

    friend std::ostream & operator<< (std::ostream & os, const BatteryArg & b) {
        b.initCheck();

        os << b.name;
        return os;
    }

private:
    bool initialized = false;
    Constants::BatteryID batteryId;
    std::string name;
    std::string shortName;
    uint expectedExitCode;

    static Constants::BatteryID getBatteryIdFromShortName(const std::string & shortName);

    void init(const std::string & shortName);

    void initCheck() const;
};

} // namespace clinterface
} // namespace rtt

#endif // RTT_CLINTERFACE_BATTERYARG_H

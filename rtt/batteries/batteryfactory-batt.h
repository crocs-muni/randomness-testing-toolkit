#ifndef RTT_BATTERIES_BATTERYFACTORY_H
#define RTT_BATTERIES_BATTERYFACTORY_H

#include "rtt/constants.h"
#include "rtt/options.h"

#include "rtt/batteries/ibattery-batt.h"
#include "rtt/batteries/niststs/battery-sts.h"
#include "rtt/batteries/dieharder/battery-dh.h"
#include "rtt/batteries/testu01/battery-tu01.h"

namespace rtt {
namespace batteries {

class BatteryFactory {
public:
    static std::unique_ptr<IBattery> createBattery(const CliOptions & options) {
        switch(options.getBattery()) {
        case Constants::BATTERY_DIEHARDER:
            return dieharder::Battery::getInstance(options);
            break;
        case Constants::BATTERY_NIST_STS:
            return niststs::Battery::getInstance(options);
            break;
        case Constants::BATTERY_TU01_SMALLCRUSH:
            return testu01::Battery::getInstance(options);
            break;
        case Constants::BATTERY_TU01_CRUSH:
            return testu01::Battery::getInstance(options);
            break;
        case Constants::BATTERY_TU01_BIGCRUSH:
            return testu01::Battery::getInstance(options);
            break;
        case Constants::BATTERY_TU01_RABBIT:
            return testu01::Battery::getInstance(options);
            break;
        case Constants::BATTERY_TU01_ALPHABIT:
            return testu01::Battery::getInstance(options);
            break;
        case Constants::BATTERY_EACIRC:
            throw std::runtime_error("EACirc battery is not yet implemented");
            break;
        default:
            throw std::runtime_error("unknown battery of tests set in options");
            break;
        }
    }
};

} // namespace batteries
} // namespace rtt

#endif //RTT_BATTERYFACTORY_H

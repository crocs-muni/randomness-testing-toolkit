#ifndef RTT_BATTERIES_BATTERYFACTORY_H
#define RTT_BATTERIES_BATTERYFACTORY_H

#include "rtt/constants.h"
#include "rtt/clioptions.h"

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
        case Constants::Battery::DIEHARDER:
            return dieharder::Battery::getInstance(options);
            break;
        case Constants::Battery::NIST_STS:
            return niststs::Battery::getInstance(options);
            break;
        case Constants::Battery::TU01_SMALLCRUSH:
            return testu01::Battery::getInstance(options);
            break;
        case Constants::Battery::TU01_CRUSH:
            return testu01::Battery::getInstance(options);
            break;
        case Constants::Battery::TU01_BIGCRUSH:
            return testu01::Battery::getInstance(options);
            break;
        case Constants::Battery::TU01_RABBIT:
            return testu01::Battery::getInstance(options);
            break;
        case Constants::Battery::TU01_ALPHABIT:
            return testu01::Battery::getInstance(options);
            break;
        default:raiseBugException("invalid battery");
        }
    }
};

} // namespace batteries
} // namespace rtt

#endif //RTT_BATTERYFACTORY_H

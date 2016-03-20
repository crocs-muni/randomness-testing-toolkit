#ifndef RTT_BATTERIES_TESTU01_BATTERY_H
#define RTT_BATTERIES_TESTU01_BATTERY_H

#include "rtt/batteries/ibattery-batt.h"

namespace rtt {
namespace batteries {
namespace testu01 {

class Battery : public IBattery {
public:
    static std::unique_ptr<Battery> getInstance(const Globals & globals);

    void processStoredResults();
private:
    /*
    ===============
    *** Methods ***
    ===============
    */
    /* So initialization in getInstance can't be avoided */
    Battery () {}
};

} // namespace testu01
} // namespace batteries
} // namespace rtt

#endif // RTT_BATTERIES_TESTU01_BATTERY_H

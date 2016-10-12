#ifndef RTT_BATTERIES_DIEHARDER_BATTERY_H
#define RTT_BATTERIES_DIEHARDER_BATTERY_H

#include "rtt/batteries/ibattery-batt.h"

namespace rtt {
namespace batteries {
namespace dieharder {

class Battery : public IBattery {
public:
    static std::unique_ptr<Battery> getInstance(const GlobalContainer & container);

    void storeResults();

private:
    /*
    ===============
    *** Methods ***
    ===============
    */
    /* So initialization in getInstance can't be avoided */
    Battery(const GlobalContainer & container)
        : IBattery(container) {}
};

} // namespace dieharder
} // namespace batteries
} // namespace rtt

#endif // RTT_BATTERIES_DIEHARDER_BATTERY_H

#ifndef RTT_BATTERIES_NISTSTS_BATTERY_H
#define RTT_BATTERIES_NISTSTS_BATTERY_H

#include <algorithm>

#include "libs/cephes/cephes.h"
#include "rtt/batteries/ibattery-batt.h"

namespace rtt {
namespace batteries {
namespace niststs {

class Battery : public IBattery {
public:
    static std::unique_ptr<Battery> getInstance(const GlobalContainer & container);

    void processStoredResults();
private:
    /*
    ===============
    *** Methods ***
    ===============
    */
    Battery(const GlobalContainer & container)
        : IBattery(container) {}
};

} // namespace niststs
} // namespace batteries
} // namespace rtt

#endif // RTT_BATTERIES_NISTSTS_BATTERY_H

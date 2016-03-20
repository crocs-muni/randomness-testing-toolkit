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
    static std::unique_ptr<Battery> getInstance(const Globals & globals);

    void processStoredResults();
private:
    /*
    ===============
    *** Methods ***
    ===============
    */
    /* So initialization in getInstance can't be avoided */
    Battery() {}

    static double chi2_stat(tTestPvals pvals);

    static std::string proportionStat(tTestPvals pvals, bool * failed);
};

} // namespace niststs
} // namespace batteries
} // namespace rtt

#endif // RTT_BATTERIES_NISTSTS_BATTERY_H

#ifndef RTT_BATTERIES_DIEHARDER_BATTERY_H
#define RTT_BATTERIES_DIEHARDER_BATTERY_H

#include "rtt/batteries/ibattery-batt.h"

namespace rtt {
namespace batteries {
namespace dieharder {

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

    static double kstest(const std::vector<double> & pvalue);

    static double p_ks_new(int n , double d);

    static void mMultiply(double *A,double *B,double *C,int m);

    static void mPower(double *A,int eA,double *V,int *eV,int m,int n);
};

} // namespace dieharder
} // namespace batteries
} // namespace rtt

#endif // RTT_BATTERIES_DIEHARDER_BATTERY_H

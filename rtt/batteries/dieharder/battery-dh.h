#ifndef RTT_BATTERIES_DIEHARDER_BATTERY_H
#define RTT_BATTERIES_DIEHARDER_BATTERY_H

#include "libs/tinyXML/xmlproc.h"
#include "rtt/options.h"
#include "rtt/batteries/interface-batt.h"
#include "rtt/batteries/dieharder/test-dh.h"
#include "rtt/output/interfacefactory-out.h"

namespace rtt {
namespace batteries {
namespace dieharder {

class Battery : public Interface {
public:
    /* XPath constants */
    static const std::string XPATH_LOG_DIRECTORY;

    static std::unique_ptr<Battery> getInstance(const CliOptions & options);

    void runTests();

    void processStoredResults();
private:
    /*
    =================
    *** Variables ***
    =================
    */
    time_t creationTime;
    std::string logFilePath;
    std::unique_ptr<output::Interface> storage;
    /* Test class keeps track of individual test logs, results and such */
    /* Also executes tests */
    std::vector<Test> tests;
    bool executed = false;

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

#ifndef RTT_BATTERIES_DIEHARDER_BATTERY_H
#define RTT_BATTERIES_DIEHARDER_BATTERY_H

#include "rtt/globals.h"
#include "rtt/batteries/testrunner-batt.h"
#include "rtt/batteries/ibattery-batt.h"
#include "rtt/batteries/dieharder/test-dh.h"
#include "rtt/output/outputfactory-out.h"

namespace rtt {
namespace batteries {
namespace dieharder {

class Battery : public IBattery {
public:
    /* XPath constants */
    static const std::string XPATH_LOG_DIRECTORY;
    static const std::string XPATH_DEFAULT_TESTS;

    static std::unique_ptr<Battery> getInstance(const Globals & globals);

    void runTests();

    void processStoredResults();

private:
    /*
    =================
    *** Variables ***
    =================
    */
    /* Objects pointing to global setting storage -
     * many other classes are using these globals */
    std::shared_ptr<CliOptions> cliOptions;
    std::shared_ptr<batteries::Configuration> batteryConfiguration;
    std::shared_ptr<ToolkitSettings> toolkitSettings;

    /* Variables initialized in getInstance() */
    Constants::Battery battery;
    time_t creationTime;
    std::string logFilePath;
    std::string objectInfo;
    std::unique_ptr<output::IOutput> storage;
    /* Test class keeps track of individual test logs, results and such */
    /* Also executes tests */
    std::vector<std::unique_ptr<ITest>> tests;
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

#ifndef RTT_BATTERIES_TESTU01_BATTERY_H
#define RTT_BATTERIES_TESTU01_BATTERY_H

#include "rtt/globals.h"
#include "rtt/batteries/testrunner-batt.h"
#include "rtt/batteries/ibattery-batt.h"
#include "rtt/batteries/testu01/test-tu01.h"
#include "rtt/output/outputfactory-out.h"

namespace rtt {
namespace batteries {
namespace testu01 {

class Battery : public IBattery {
public:
    /* XPath constants */
    static const std::string XPATH_LOG_DIRECTORY;
    static const std::string XPATH_DEFAULT_TESTS_SMALL_CRUSH;
    static const std::string XPATH_DEFAULT_TESTS_CRUSH;
    static const std::string XPATH_DEFAULT_TESTS_BIG_CRUSH;
    static const std::string XPATH_DEFAULT_TESTS_RABBIT;
    static const std::string XPATH_DEFAULT_TESTS_ALPHABIT;

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

    /* As soon as getInstance is called, this time is set */
    /* Used for naming output files */
    Constants::Battery battery;
    time_t creationTime;
    std::string objectInfo;
    /* After test execution, log of battery run will be stored in logFilePath */
    std::string logFilePath;
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
};

} // namespace testu01
} // namespace batteries
} // namespace rtt

#endif // RTT_BATTERIES_TESTU01_BATTERY_H

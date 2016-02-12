#ifndef RTT_BATTERIES_TESTU01_BATTERY_H
#define RTT_BATTERIES_TESTU01_BATTERY_H

#include "libs/tinyXML/xmlproc.h"
#include "rtt/options.h"
#include "rtt/batteries/interface-batt.h"
#include "rtt/batteries/testu01/test-tu01.h"
#include "rtt/output/interfacefactory-out.h"

namespace rtt {
namespace batteries {
namespace testu01 {

class Battery : public Interface {
public:
    /* XPath constants */
    static const std::string XPATH_LOG_DIRECTORY;
    static const std::string XPATH_DEFAULT_TESTS_SMALL_CRUSH;
    static const std::string XPATH_DEFAULT_TESTS_CRUSH;
    static const std::string XPATH_DEFAULT_TESTS_BIG_CRUSH;
    static const std::string XPATH_DEFAULT_TESTS_RABBIT;
    static const std::string XPATH_DEFAULT_TESTS_ALPHABIT;

    static std::unique_ptr<Battery> getInstance(const CliOptions & options);

    void runTests();

    void processStoredResults();
private:
    /*
    =================
    *** Variables ***
    =================
    */
    /* As soon as getInstance is called, this time is set */
    /* Used for naming output files */
    time_t creationTime;
    /* After test execution, log of battery run will be stored in logFilePath */
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
};

} // namespace testu01
} // namespace batteries
} // namespace rtt

#endif // RTT_BATTERIES_TESTU01_BATTERY_H

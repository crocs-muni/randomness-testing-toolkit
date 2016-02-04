#ifndef RTT_BATTERIES_NISTSTS_BATTERY_H
#define RTT_BATTERIES_NISTSTS_BATTERY_H

#include "libs/tinyXML/xmlproc.h"
#include "rtt/options.h"
#include "rtt/batteries/interface.h"
#include "rtt/batteries/niststs/test-sts.h"

namespace rtt {
namespace batteries {
namespace niststs {

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
    /* After test execution, log of battery run will be stored in logFileName */
    std::string logFileName;
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
    Battery() {}
};

} // namespace niststs
} // namespace batteries
} // namespace rtt

#endif // RTT_BATTERIES_NISTSTS_BATTERY_H

#ifndef RTT_BATTERIES_DIEHARDER_BATTERY_H
#define RTT_BATTERIES_DIEHARDER_BATTERY_H

#include "libs/tinyXML/xmlproc.h"
#include "rtt/options.h"
#include "rtt/batteries/interface.h"
#include "rtt/batteries/dieharder/test-dh.h"

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
    Battery () {}
};

} // namespace dieharder
} // namespace batteries
} // namespace rtt

#endif // RTT_BATTERIES_DIEHARDER_BATTERY_H

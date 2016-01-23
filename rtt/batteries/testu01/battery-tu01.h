#ifndef RTT_BATTERIES_TESTU01_BATTERY_H
#define RTT_BATTERIES_TESTU01_BATTERY_H

#include "libs/tinyXML/xmlproc.h"
#include "rtt/options.h"
#include "rtt/batteries/interface.h"
#include "rtt/batteries/testu01/test-tu01.h"

namespace rtt {
namespace batteries {
namespace testu01 {

class Battery : public Interface {
public:
    static std::unique_ptr<Battery> getInstance(const CliOptions & options);
    void runTests();
    void processStoredResults();
private:
    /*
    =================
    *** Variables ***
    =================
    */
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

#ifndef RTT_BATTERIES_NISTSTS_BATTERY_H
#define RTT_BATTERIES_NISTSTS_BATTERY_H

#include "libs/tinyXML/xmlproc.h"
#include "rtt/options.h"
#include "rtt/batteries/interface.h"
#include "rtt/batteries/niststs/test.h"

namespace rtt {
namespace batteries {
namespace niststs {

class Battery : public Interface {
public:
    Battery() {}
    static Battery * getInstance(const CliOptions & options);
    void runTests();
    void processStoredResults();
private:
    std::vector<Test> tests;
};

} // namespace niststs
} // namespace batteries
} // namespace rtt

#endif // RTT_BATTERIES_NISTSTS_BATTERY_H

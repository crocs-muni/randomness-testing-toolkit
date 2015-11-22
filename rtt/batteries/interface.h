#ifndef RTT_BATTERIES_INTERFACE_H
#define RTT_BATTERIES_INTERFACE_H

#include "rtt/options.h"

namespace rtt {
namespace batteries {

class Interface {
public:
    virtual ~Interface() {}

    virtual void initBattery(const CliOptions & options) = 0;

    virtual void runTests() = 0;

    virtual void processStoredResults() = 0;
};

} // namespace batteries
} // namespace rtt

#endif // RTT_BATTERIES_INTERFACE_H

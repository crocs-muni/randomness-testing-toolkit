#ifndef RTT_BATTERIES_INTERFACEFACTORY_H
#define RTT_BATTERIES_INTERFACEFACTORY_H

#include "rtt/constants.h"
#include "rtt/options.h"

#include "rtt/batteries/interface.h"
#include "rtt/batteries/niststs/battery-sts.h"
#include "rtt/batteries/dieharder/battery-dh.h"
#include "rtt/batteries/testu01/battery-tu01.h"

namespace rtt {

class InterfaceFactory {
public:
    static std::unique_ptr<batteries::Interface> createBattery(const CliOptions & options);
};

} // namespace rtt

#endif //RTT_INTERFACECREATOR_H

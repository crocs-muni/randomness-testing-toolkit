#ifndef RTT_INTERFACECREATOR_H
#define RTT_INTERFACECREATOR_H

#include "rtt/constants.h"
#include "rtt/options.h"

#include "rtt/batteries/interface.h"
#include "rtt/batteries/niststs/battery.h"
//#include "rtt/batteries/dieharder.h"
//#include "rtt/batteries/niststs.h"
//#include "rtt/batteries/testu01.h"

namespace rtt {

class InterfaceCreator {
public:
    static batteries::Interface *createBattery(const CliOptions & options);

    static void destroyBattery(batteries::Interface * battery);
};

} // namespace rtt

#endif //RTT_INTERFACECREATOR_H

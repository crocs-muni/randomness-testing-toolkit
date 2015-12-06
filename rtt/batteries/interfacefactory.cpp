#include "rtt/batteries/interfacefactory.h"

namespace rtt {

using namespace batteries;

std::unique_ptr<Interface> InterfaceFactory::createBattery(const CliOptions &options) {
    switch(options.getBattery()) {
    case Constants::BATTERY_DIEHARDER:
        throw std::runtime_error("Dieharder battery is not yet implemented");
        //return new batteries::Dieharder(options);
        break;
    case Constants::BATTERY_NIST_STS:
        //throw std::runtime_error("NIST STS battery is not yet implemented");
        return niststs::Battery::getInstance(options);
        break;
    case Constants::BATTERY_TU01_SMALLCRUSH:
        throw std::runtime_error("TU01 Small Crush battery is not yet implemented");
        //return new batteries::TestU01(options);
        break;
    case Constants::BATTERY_TU01_CRUSH:
        throw std::runtime_error("TU01 Crush battery is not yet implemented");
        //return new batteries::TestU01(options);
        break;
    case Constants::BATTERY_TU01_BIGCRUSH:
        throw std::runtime_error("TU01 Big Crush battery is not yet implemented");
        //return new batteries::TestU01(options);
        break;
    case Constants::BATTERY_EACIRC:
        throw std::runtime_error("EACirc battery is not yet implemented");
        break;
    default:
        throw std::runtime_error("unknown statistical battery requested");
        break;
    }
}

} // namespace rtt

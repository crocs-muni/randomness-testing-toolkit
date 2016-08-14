#include "ivariant-batt.h"

#include "rtt/batteries/niststs/variant-sts.h"
#include "rtt/batteries/dieharder/variant-dh.h"
#include "rtt/batteries/testu01/variant-tu01.h"

namespace rtt {
namespace batteries {

std::unique_ptr<IVariant> IVariant::getInstance(int testId, uint variantIdx,
                                                const GlobalContainer & cont) {
    switch(cont.getCliOptions()->getBattery()) {
        case Constants::Battery::NIST_STS:
            return niststs::Variant::getInstance(testId , variantIdx, cont);
        case Constants::Battery::DIEHARDER:
            return dieharder::Variant::getInstance(testId , variantIdx, cont);
        case Constants::Battery::TU01_SMALLCRUSH:
        case Constants::Battery::TU01_CRUSH:
        case Constants::Battery::TU01_BIGCRUSH:
        case Constants::Battery::TU01_RABBIT:
        case Constants::Battery::TU01_ALPHABIT:
        case Constants::Battery::TU01_BLOCK_ALPHABIT:
            return testu01::Variant::getInstance(testId , variantIdx , cont);
        default:
            raiseBugException(Strings::ERR_INVALID_BATTERY);
    }
}



} // namespace batteries
} // namespace rtt

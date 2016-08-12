#include "ivariant-batt.h"

#include "rtt/batteries/niststs/variant-sts.h"

namespace rtt {
namespace batteries {

std::unique_ptr<IVariant> IVariant::getInstance(int testId, uint variantIndex, const GlobalContainer & cont)
{
    return niststs::Variant::getInstance(testId , variantIndex , cont);
}



} // namespace batteries
} // namespace rtt

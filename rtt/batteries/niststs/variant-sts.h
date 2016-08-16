#ifndef RTT_BATTERIES_NISTSTS_VARIANT_H
#define RTT_BATTERIES_NISTSTS_VARIANT_H

#include "rtt/batteries/ivariant-batt.h"

namespace rtt {
namespace batteries {
namespace niststs {

class Variant : public IVariant {
public:
    static std::unique_ptr<Variant> getInstance(int testId, uint variantIdx,
                                                const GlobalContainer & cont);
private:
    /* Variables */
    std::string streamSize;
    std::string streamCount;
    std::string blockLength;
    bool adjustableBlockLength;

    /* Methods */
    Variant(int testId, uint variantIdx,
            const GlobalContainer & cont)
        : IVariant(testId, variantIdx, cont)
    {}

    void buildStrings();
};

} // namespace niststs
} // namespace batteries
} // namespace rtt

#endif // RTT_BATTERIES_NISTSTS_VARIANT_H

#ifndef RTT_BATTERIES_DIEHARDER_VARIANT_H
#define RTT_BATTERIES_DIEHARDER_VARIANT_H

#include "rtt/batteries/ivariant-batt.h"
#include "rtt/batteries/dieharder/setting-dh.h"

namespace rtt {
namespace batteries {
namespace dieharder {

class Variant : public IVariant {
public:
    static std::unique_ptr<Variant> getInstance(int testId, uint variantIdx,
                                                const GlobalContainer & cont);
private:
    /* Test info constants */
    static const int OPTION_HEADER_FLAG;
    static const int OPTION_FILE_GENERATOR;

    // Dieharder specific data
    std::vector<Setting> settings;
    int pSampleCount;

    /* Methods */
    Variant(int testId, uint variantIdx,
            const GlobalContainer & cont)
        : IVariant(testId, variantIdx, cont)
    {}

    void buildStrings();
};

} // namespace dieharder
} // namespace batteries
} // namespace rtt

#endif // RTT_BATTERIES_DIEHARDER_VARIANT_H

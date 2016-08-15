#ifndef RTT_BATTERIES_TESTU01_VARIANT_H
#define RTT_BATTERIES_TESTU01_VARIANT_H

#include "rtt/batteries/ivariant-batt.h"
#include "rtt/batteries/testconstants.h"

namespace rtt {
namespace batteries {
namespace testu01 {

/* Typedefs for parameter types */
typedef std::pair<std::string , std::string> tParam;

class Variant : public IVariant {
public:
    static std::unique_ptr<Variant> getInstance(int testId, uint variantIdx,
                                                const GlobalContainer & cont);
private:
    /* TestU01 specific */
    std::vector<std::string> paramNames;
    std::vector<std::string> statisticNames;
    uint repetitions;
    /* Only used in configuration of crush batteries */
    std::vector<tParam> params;
    /* Used in rabbit/alphabit battery */
    std::string bit_nb;
    std::string bit_r;
    std::string bit_s;
    std::string bit_w;

    /* Methods */
    Variant(int testId, uint variantIdx,
            const GlobalContainer & cont)
        : IVariant(testId, variantIdx, cont)
    {}

    void buildStrings();
};

} // namespace testu01
} // namespace batteries
} // namespace rtt

#endif // RTT_BATTERIES_TESTU01_VARIANT_H

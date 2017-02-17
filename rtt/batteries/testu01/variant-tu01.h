#ifndef RTT_BATTERIES_TESTU01_VARIANT_H
#define RTT_BATTERIES_TESTU01_VARIANT_H

#include "rtt/batteries/ivariant-batt.h"

namespace rtt {
namespace batteries {
namespace testu01 {

/* Typedefs for parameter types */
typedef std::pair<std::string , std::string> tParam;

class Variant : public IVariant {
public:
    static std::unique_ptr<Variant> getInstance(int testId, std::string testObjInf,
                                                uint variantIdx, const GlobalContainer & cont);


    std::vector<std::string> getStatisticNames() const;

    std::vector<std::string> getExtractableParamNames() const;

private:
    /* TestU01 specific */
    std::vector<std::string> settableParamNames;
    std::vector<std::string> extractableParamNames;
    std::vector<std::string> statisticNames;
    int repetitions;
    /* Only used in configuration of crush batteries */
    std::vector<tParam> params;
    /* Used in rabbit/alphabit battery */
    std::string bit_nb;
    std::string bit_r;
    std::string bit_s;
    std::string bit_w;

    /* Methods */
    Variant(int testId, std::string testObjInf,
            uint variantIdx, const GlobalContainer & cont)
        : IVariant(testId, testObjInf, variantIdx, cont)
    {}

    void buildStrings();
};

} // namespace testu01
} // namespace batteries
} // namespace rtt

#endif // RTT_BATTERIES_TESTU01_VARIANT_H

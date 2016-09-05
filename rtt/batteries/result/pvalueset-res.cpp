#include "pvalueset-res.h"

namespace rtt {
namespace batteries {
namespace result {

PValueSet PValueSet::getInstance(std::string statName, double statResult,
                                 const std::vector<double> & pValues) {
    if(statName.empty())
        raiseBugException("empty statName");
    if(statResult < (0 - Constants::MATH_EPS) ||
       statResult > (1 + Constants::MATH_EPS))
        raiseBugException("p-value outside of <0,1>");
    if(pValues.empty())
        raiseBugException("empty pValues");

    auto rval = PValueSet(statName, statResult, pValues);

    return rval;
}

std::string PValueSet::getStatName() const {
    return statName;
}

double PValueSet::getStatRes() const {
    return statRes;
}

std::vector<double> PValueSet::getPValues() const {
    return pValues;
}

} // namespace result
} // namespace batteries
} // namespace rtt

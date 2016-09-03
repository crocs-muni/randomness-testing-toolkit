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
    double alpha = Constants::MATH_ALPHA /*/ 2.0*/; // Ask Syso about this.

    if(statResult > alpha - Constants::MATH_EPS &&
       statResult < 1 - alpha + Constants::MATH_EPS)
        rval.statPassed = true;

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

bool PValueSet::getStatPassed() const {
    return statPassed;
}

} // namespace result
} // namespace batteries
} // namespace rtt

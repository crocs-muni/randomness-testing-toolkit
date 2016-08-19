#include "subtestresult-res.h"

namespace rtt {
namespace batteries {
namespace result {

SubTestResult SubTestResult::getInstance(
        const std::vector<PValueSet> & pValSets) {
    if(pValSets.empty())
        raiseBugException("empty pValSets");

    return SubTestResult(pValSets);
}

std::vector<double> SubTestResult::getStatResults() const{
    std::vector<double> rval;
    for(const PValueSet & set : pValSets)
        rval.push_back(set.getStatRes());

    return rval;
}

std::vector<PValueSet> SubTestResult::getPValSets() const {
    return pValSets;
}

std::vector<std::string> SubTestResult::getTestParameters() const {
    return testParameters;
}

void SubTestResult::setTestParameters(
        const std::vector<std::string> & value) {
    testParameters = value;
}


} // namespace result
} // namespace batteries
} // namespace rtt

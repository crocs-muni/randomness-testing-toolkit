#include "variantresult-res.h"

namespace rtt {
namespace batteries {
namespace result {

VariantResult VariantResult::getInstance(
        const std::vector<SubTestResult> & subResults,
        const std::vector<std::string> & userSettings,
        const BatteryOutput & battOut) {
    if(subResults.empty())
        raiseBugException("empty subResults");

    return VariantResult(subResults, userSettings, battOut);
}

std::vector<double> VariantResult::getSubTestStatResults() const {
    std::vector<double> rval;
    std::vector<double> tmp;
    for(const SubTestResult & subRes : subResults) {
        tmp = subRes.getStatResults();
        rval.insert(rval.end(), tmp.begin(), tmp.end());
    }
    return rval;
}

std::vector<SubTestResult> VariantResult::getSubResults() const {
    return subResults;
}

BatteryOutput VariantResult::getBatteryOutput() const {
    return battOut;
}

std::vector<std::string> VariantResult::getUserSettings() const {
    return userSettings;
}

} // namespace result
} // namespace batteries
} // namespace rtt

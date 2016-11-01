#include "variantresult-res.h"

namespace rtt {
namespace batteries {
namespace result {

VariantResult VariantResult::getInstance(const std::vector<SubTestResult> & subResults,
        const std::vector<std::pair<std::string, std::string>> & userSettings,
        const BatteryOutput & battOut) {
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

std::vector<std::pair<std::string, std::string>> VariantResult::getUserSettings() const {
    return userSettings;
}

} // namespace result
} // namespace batteries
} // namespace rtt

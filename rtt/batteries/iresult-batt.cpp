#include "iresult-batt.h"

#include "rtt/batteries/dieharder/result-dh.h"

namespace rtt {
namespace batteries {

std::unique_ptr<IResult> IResult::getInstance(const std::vector<ITest *> & tests) {
    if(tests.empty())
        raiseBugException("empty tests");

    switch(tests.at(0)->getBattId()) {
        case Constants::Battery::NIST_STS:
            raiseBugException("not implemented yet");
        case Constants::Battery::DIEHARDER:
            return dieharder::Result::getInstance(tests);
        case Constants::Battery::TU01_SMALLCRUSH:
        case Constants::Battery::TU01_CRUSH:
        case Constants::Battery::TU01_BIGCRUSH:
        case Constants::Battery::TU01_RABBIT:
        case Constants::Battery::TU01_ALPHABIT:
        case Constants::Battery::TU01_BLOCK_ALPHABIT:
            raiseBugException("not implemented yet");
        default:
            raiseBugException(Strings::ERR_INVALID_BATTERY);
    }
}

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
    double alpha = Constants::MATH_ALPHA / 2.0;

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

SubTestResult SubTestResult::getInstance(const std::vector<PValueSet> & pValSets) {
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

VariantResult VariantResult::getInstance(const std::vector<SubTestResult> & subResults,
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

} // namespace batteries
} // namespace rtt

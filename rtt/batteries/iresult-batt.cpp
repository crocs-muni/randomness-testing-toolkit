#include "iresult-batt.h"

#include "rtt/batteries/dieharder/result-dh.h"
#include "rtt/batteries/niststs/result-sts.h"
#include "rtt/batteries/testu01/result-tu01.h"

namespace rtt {
namespace batteries {

std::unique_ptr<IResult> IResult::getInstance(
        const std::vector<ITest *> & tests) {
    if(tests.empty())
        raiseBugException("empty tests");

    std::unique_ptr<IResult> rval;

    switch(tests.at(0)->getBattId()) {
        case Constants::Battery::NIST_STS:
            rval = niststs::Result::getInstance(tests);
            break;
        case Constants::Battery::DIEHARDER:
            rval = dieharder::Result::getInstance(tests);
            break;
        case Constants::Battery::TU01_SMALLCRUSH:
        case Constants::Battery::TU01_CRUSH:
        case Constants::Battery::TU01_BIGCRUSH:
        case Constants::Battery::TU01_RABBIT:
        case Constants::Battery::TU01_ALPHABIT:
        case Constants::Battery::TU01_BLOCK_ALPHABIT:
            rval = testu01::Result::getInstance(tests);
            break;
        default:
            raiseBugException(Strings::ERR_INVALID_BATTERY);
    }
    rval->evaluateSetPassed();
    return rval;
}

void IResult::writeResults(storage::IStorage * storage, int precision) {
    storage->addNewTest(testName);
    storage->setTestResult(passed);

    for(const result::VariantResult & var : varRes) {
        if(varRes.size() > 1)
            storage->addVariant();

        storage->setUserSettings(var.getUserSettings());
        storage->setRuntimeIssues(var.getBatteryOutput().getStdErr(),
                                  var.getBatteryOutput().getErrors(),
                                  var.getBatteryOutput().getWarnings());

        const auto & subResults = var.getSubResults();
        for(const result::SubTestResult & subtest : subResults) {
            if(subResults.size() > 1)
                storage->addSubTest();

            if(subtest.getTestParameters().size() > 0)
                storage->setTestParameters(subtest.getTestParameters());

            for(const result::PValueSet & pvalSet : subtest.getPValSets()) {
                storage->addStatisticResult(pvalSet.getStatName(),
                                            pvalSet.getStatRes(),
                                            precision,
                                            pvalSet.getStatPassed());
                if(pvalSet.getPValues().size() > 1)
                    storage->addPValues(pvalSet.getPValues());
            }

            if(subResults.size() >1)
                storage->finalizeSubTest();
        }


        if(varRes.size() > 1)
            storage->finalizeVariant();
    }
    storage->finalizeSubTest();
}

std::vector<result::VariantResult> IResult::getResults() const {
    return varRes;
}

bool IResult::getPassed() const {
    return passed;
}

void IResult::evaluateSetPassed() {
    std::vector<double> allPValues;
    for(const result::VariantResult & var : varRes) {
        std::vector<double> tmp = var.getSubTestStatResults();
        allPValues.insert(allPValues.end(), tmp.begin(), tmp.end());
    }

    double exp = 1.0/(double)allPValues.size();
    double alpha = 1.0 - (std::pow(1.0 - Constants::MATH_ALPHA, exp));
    alpha /= 2.0;

    for(const double & pval : allPValues) {
        if(pval < alpha - Constants::MATH_EPS ||
           pval > 1.0 - alpha + Constants::MATH_EPS) {
            passed = false;
            break;
        }
    }
}

} // namespace batteries
} // namespace rtt

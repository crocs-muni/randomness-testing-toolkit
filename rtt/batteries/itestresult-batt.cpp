#include "itestresult-batt.h"

#include "rtt/batteries/dieharder/testresult-dh.h"
#include "rtt/batteries/niststs/testresult-sts.h"
#include "rtt/batteries/testu01/testresult-tu01.h"

namespace rtt {
namespace batteries {

std::unique_ptr<ITestResult> ITestResult::getInstance(
        const std::vector<ITest *> & tests) {
    if(tests.empty())
        raiseBugException("empty tests");

    std::unique_ptr<ITestResult> rval;

    switch(tests.at(0)->getBatteryArg().getBatteryId()) {
        case Constants::BatteryID::NIST_STS:
            rval = niststs::TestResult::getInstance(tests);
            break;
        case Constants::BatteryID::DIEHARDER:
            rval = dieharder::TestResult::getInstance(tests);
            break;
        case Constants::BatteryID::TU01_SMALLCRUSH:
        case Constants::BatteryID::TU01_CRUSH:
        case Constants::BatteryID::TU01_BIGCRUSH:
        case Constants::BatteryID::TU01_RABBIT:
        case Constants::BatteryID::TU01_ALPHABIT:
        case Constants::BatteryID::TU01_BLOCK_ALPHABIT:
            rval = testu01::TestResult::getInstance(tests);
            break;
        default:
            raiseBugException(Strings::ERR_INVALID_BATTERY);
    }
    rval->evaluateSetPassed();
    return rval;
}

std::vector<result::VariantResult> ITestResult::getVariantResults() const {
    return varRes;
}

std::pair<bool, bool> ITestResult::getOptionalPassed() const {
    return optionalPassed;
}

std::string ITestResult::getTestName() const {
    return testName;
}

double ITestResult::getPartialAlpha() const {
    return partialAlpha;
}

void ITestResult::evaluateSetPassed() {
    std::vector<double> allPValues;
    for(const result::VariantResult & var : varRes) {
        std::vector<double> tmp = var.getSubTestStatResults();
        allPValues.insert(allPValues.end(), tmp.begin(), tmp.end());
    }

    if(allPValues.empty()) {
        optionalPassed.second = false;
        return;
    }

    optionalPassed.second = true;

    double exp = 1.0/(double)allPValues.size();
    partialAlpha = 1.0 - (std::pow(1.0 - Constants::MATH_ALPHA, exp));

    for(const double & pval : allPValues) {
        if(!isPValuePassing(pval)) {
            optionalPassed.first = false;
            break;
        }
    }
}

bool ITestResult::isPValuePassing(double pvalue) {
    /* Everything outside of the interval [alpha, 1) is failure.
     +     * Note the open interval on right side - this is to fail
     +     * full 1.0s which are often given as incorrect value by batteries */
    if(pvalue < partialAlpha - Constants::MATH_EPS ||
            pvalue > 1 - Constants::MATH_EPS)
        return false;

    return true;
}

} // namespace batteries
} // namespace rtt

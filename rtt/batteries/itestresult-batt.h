#ifndef RTT_BATTERIES_ITESTRESULT_H
#define RTT_BATTERIES_ITESTRESULT_H

#include "rtt/batteries/itest-batt.h"
#include "rtt/batteries/result/variantresult-res.h"

namespace rtt {
namespace batteries {

class ITestResult {
public:
    static std::unique_ptr<ITestResult> getInstance(
            const std::vector<ITest *> & tests);

    std::vector<result::VariantResult> getVariantResults() const;

    bool getPassed() const;

    std::pair<bool, bool> getOptionalPassed() const;

    std::string getTestName() const;

    double getPartialAlpha() const;

    bool isPValuePassing(double pvalue);

protected:
    /* Variables */
    Logger * logger;
    std::string objectInfo;
    std::string testName;
    std::vector<result::VariantResult> varRes;
    std::pair<bool, bool> optionalPassed = { true, false };
    double partialAlpha = 0;

    /* Methods */
    ITestResult(Logger * logger , std::string testName)
        : logger(logger) , testName(testName)
    {}

    void evaluateSetPassed();
};







} // namespace batteries
} // namespace rtt

#endif // RTT_BATTERIES_ITESTRESULT_H

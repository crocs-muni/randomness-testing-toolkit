#ifndef RTT_BATTERIES_ITESTRESULT_H
#define RTT_BATTERIES_ITESTRESULT_H

#include "rtt/batteries/itest-batt.h"
#include "rtt/batteries/result/variantresult-res.h"

namespace rtt {
namespace batteries {

/**
 * @brief The ITestResult class Holds results of one or multiple tests.
 * If there are multiple tests inside, the results will be bundled together
 */
class ITestResult {
public:
    /**
     * @brief getInstance Creates instance. Tests that are to
     * be bundled together should be provided in a vector.
     * @param tests set of tests
     * @return initialized instance
     */
    static std::unique_ptr<ITestResult> getInstance(
            const std::vector<ITest *> & tests);

    /**
     * @brief getVariantResults
     * @return Results of all underlying variants that were contained in the tests
     */
    std::vector<result::VariantResult> getVariantResults() const;

    /**
     * @brief getOptionalPassed Returns optional bool variable.
     * If second bool in the pair is false, then there were no
     * valid results and nothing was evaluated. If it is true
     * then first bool can be either true or false, based on
     * p-values of underlying variants.
     * @return Information about passing of the test.
     */
    std::pair<bool, bool> getOptionalPassed() const;

    /**
     * @brief getTestName
     * @return Human readable string containing test name
     */
    std::string getTestName() const;

    /**
     * @brief getPartialAlpha
     * @return Partial alpha that was used for
     * evaluating succes or failure of given test.
     */
    double getPartialAlpha() const;

    /**
     * @brief isPValuePassing Evaluates given p-value
     * against partial alpha of the test
     * @param pvalue to be evaluated
     * @return true if p-value is passing, false otherwise
     */
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

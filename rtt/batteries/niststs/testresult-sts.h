#ifndef RTT_BATTERIES_NISTSTS_TESTRESULT_H
#define RTT_BATTERIES_NISTSTS_TESTRESULT_H

#include "rtt/batteries/itestresult-batt.h"

#include "rtt/batteries/niststs/variant-sts.h"

namespace rtt {
namespace batteries {
namespace niststs {

class TestResult : public ITestResult {
public:
    static std::unique_ptr<TestResult> getInstance(
            const std::vector<ITest *> & tests);
private:
    TestResult(Logger * logger , std::string testName)
        : ITestResult(logger , testName)
    {}

    static std::vector<std::vector<double>> getVariantPValues(
            Variant * variant);

    static double chi2_stat(std::vector<double> pvals);
};

} // namespace niststs
} // namespace batteries
} // namespace rtt

#endif // RTT_BATTERIES_NISTSTS_TESTRESULT_H

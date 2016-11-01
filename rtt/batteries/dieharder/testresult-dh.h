#ifndef RTT_BATTERIES_DIEHARDER_TESTRESULT_H
#define RTT_BATTERIES_DIEHARDER_TESTRESULT_H

#include <cmath>

#include "rtt/batteries/itestresult-batt.h"


namespace rtt {
namespace batteries {
namespace dieharder {

class TestResult : public ITestResult {
public:
    static std::unique_ptr<TestResult> getInstance(
            const std::vector<ITest *> & tests);

private:
    TestResult(Logger * logger , std::string testName)
        : ITestResult(logger , testName)
    {}

    static std::vector<std::string> splitIntoSubTests(const std::string & str);

    /* Math functions used to calculate resulting KS statistic */
    double kstest(const std::vector<double> & pvalue);

    double p_ks_new(int n , double d);

    void mMultiply(double *A,double *B,double *C,int m);

    void mPower(double *A,int eA,double *V,int *eV,int m,int n);
};

} // namespace dieharder
} // namespace batteries
} // namespace rtt

#endif // RTT_BATTERIES_DIEHARDER_TESTRESULT_H

#ifndef RTT_BATTERIES_DIEHARDER_RESULT_H
#define RTT_BATTERIES_DIEHARDER_RESULT_H

#include <cmath>

#include "rtt/batteries/iresult-batt.h"

namespace rtt {
namespace batteries {
namespace dieharder {

class Result : public IResult {
public:
    static std::unique_ptr<Result> getInstance(
            const std::vector<ITest *> & tests);

    void writeResults(storage::IStorage * storage);

    std::vector<VariantResult> getResults() const;

    bool getPassed() const;

private:
    /* Variables */
    std::string objectInfo;
    std::string testName;
    std::vector<VariantResult> varRes;
    bool passed = true;

    /* Methods */
    Result() {}
    
    void evaluateSetPassed();

    /* Math functions used to calculate resulting KS statistic */
    double kstest(const std::vector<double> & pvalue);

    double p_ks_new(int n , double d);

    void mMultiply(double *A,double *B,double *C,int m);

    void mPower(double *A,int eA,double *V,int *eV,int m,int n);
};

} // namespace dieharder
} // namespace batteries
} // namespace rtt

#endif // RTT_BATTERIES_DIEHARDER_RESULT_H

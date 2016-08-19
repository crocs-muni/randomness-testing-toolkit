#ifndef RTT_BATTERIES_NISTSTS_RESULT_H
#define RTT_BATTERIES_NISTSTS_RESULT_H

#include "libs/cephes/cephes.h"
#include "rtt/batteries/iresult-batt.h"

#include "rtt/batteries/niststs/variant-sts.h"

namespace rtt {
namespace batteries {
namespace niststs {

class Result : public IResult {
public:
    static std::unique_ptr<Result> getInstance(
            const std::vector<ITest *> & tests);
private:
    Result() {}

    static std::vector<std::vector<double>> getVariantPValues(
            Variant * variant);

    static double chi2_stat(std::vector<double> pvals);
};

} // namespace niststs
} // namespace batteries
} // namespace rtt

#endif // RTT_BATTERIES_NISTSTS_RESULT_H

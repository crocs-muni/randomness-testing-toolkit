#ifndef RTT_BATTERIES_IRESULT_H
#define RTT_BATTERIES_IRESULT_H

#include "rtt/batteries/itest-batt.h"
#include "rtt/batteries/result/variantresult-res.h"
#include "rtt/storage/istorage.h"

namespace rtt {
namespace batteries {

class IResult {
public:
    static std::unique_ptr<IResult> getInstance(
            const std::vector<ITest *> & tests);

    void writeResults(storage::IStorage * storage, int precision);

    std::vector<result::VariantResult> getResults() const;

    bool getPassed() const;

    std::pair<bool, bool> getOptionalPassed() const;

protected:
    /* Variables */
    Logger * logger;
    std::string objectInfo;
    std::string testName;
    std::vector<result::VariantResult> varRes;
    std::pair<bool, bool> optionalPassed = { true, false };
    double partialAlpha = 0;

    /* Methods */
    IResult(Logger * logger , std::string testName)
        : logger(logger) , testName(testName)
    {}

    void evaluateSetPassed();

    bool isPValuePassing(double pvalue);
};







} // namespace batteries
} // namespace rtt

#endif // RTT_BATTERIES_IRESULT_H

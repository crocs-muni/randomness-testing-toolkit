#ifndef RTT_BATTERIES_RESULT_SUBTESTRESULT_H
#define RTT_BATTERIES_RESULT_SUBTESTRESULT_H

#include "rtt/batteries/result/pvalueset-res.h"

namespace rtt {
namespace batteries {
namespace result {

class SubTestResult {
public:
    static SubTestResult getInstance(const std::vector<PValueSet> & pValSets);

    std::vector<double> getStatResults() const;

    std::vector<PValueSet> getPValSets() const;

    std::vector<std::string> getTestParameters() const;

    void setTestParameters(const std::vector<std::string> & value);

private:
    SubTestResult(const std::vector<PValueSet> & pValSets)
        : pValSets(pValSets)
    {}

    std::vector<PValueSet> pValSets;

    std::vector<std::string> testParameters;
};

} // namespace result
} // namespace batteries
} // namespace rtt

#endif // RTT_BATTERIES_RESULT_SUBTESTRESULT_H

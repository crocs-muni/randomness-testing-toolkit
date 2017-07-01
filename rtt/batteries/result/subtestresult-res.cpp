#include "subtestresult-res.h"

namespace rtt {
namespace batteries {
namespace result {


SubTestResult SubTestResult::getInstance(const std::vector<Statistic> & statistics) {
    if(statistics.empty())
        raiseBugException("empty statistics");

    return SubTestResult(statistics, {});
}

SubTestResult SubTestResult::getInstance(const std::vector<Statistic> & statistics,
                                         const std::vector<double> & pvalues) {
    if(statistics.empty())
        raiseBugException("empty statistics");

    return SubTestResult(statistics, pvalues);
}

std::vector<std::pair<std::string, std::string> > SubTestResult::getTestParameters() const {
    return testParameters;
}

void SubTestResult::setTestParameters(const std::vector<std::pair<std::string, std::string> > & value) {
    testParameters = value;
}

std::vector<double> SubTestResult::getPvalues() const {
    return pvalues;
}

std::vector<Statistic> SubTestResult::getStatistics() const {
    return statistics;
}

std::vector<double> SubTestResult::getStatResults() const {
    std::vector<double> rval(statistics.size());
    std::transform(statistics.begin(), statistics.end(), rval.begin(),
                   [](const auto & el){ return el.getValue(); });

    return rval;
}

} // namespace result
} // namespace batteries
} // namespace rtt

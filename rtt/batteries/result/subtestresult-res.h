#ifndef RTT_BATTERIES_RESULT_SUBTESTRESULT_H
#define RTT_BATTERIES_RESULT_SUBTESTRESULT_H

#include "rtt/batteries/result/statistic-res.h"

namespace rtt {
namespace batteries {
namespace result {

class SubTestResult {
public:
    static SubTestResult getInstance(
            const std::vector<Statistic> & statistics);

    static SubTestResult getInstance(
            const std::vector<Statistic> & statistics,
            const std::vector<double> & pvalues);


    std::vector<std::pair<std::string, std::string>> getTestParameters() const;

    void setTestParameters(
            const std::vector<std::pair<std::string, std::string> > & value);

    std::vector<double> getStatResults() const;

    std::vector<double> getPvalues() const;

    std::vector<Statistic> getStatistics() const;

private:
    SubTestResult(const std::vector<Statistic> & statistics,
                  const std::vector<double> & pvalues)
        : statistics(statistics), pvalues(pvalues)
    {}

    std::vector<Statistic> statistics;

    std::vector<double> pvalues;

    std::vector<std::pair<std::string, std::string>> testParameters;
};

} // namespace result
} // namespace batteries
} // namespace rtt

#endif // RTT_BATTERIES_RESULT_SUBTESTRESULT_H

#ifndef RTT_BATTERIES_RESULT_SUBTESTRESULT_H
#define RTT_BATTERIES_RESULT_SUBTESTRESULT_H

#include "rtt/batteries/result/statistic-res.h"

namespace rtt {
namespace batteries {
namespace result {

/**
 * @brief The SubTestResult class Class used for storing result of a single subtest.
 * Subtest contains at least one statistic and may or may not contain set of p-values.
 */
class SubTestResult {
public:
    /**
     * @brief getInstance Used for initializing subtest w/out p-values
     * @param statistics Set of statistics of the subtest
     * @return instance
     */
    static SubTestResult getInstance(
            const std::vector<Statistic> & statistics);

    /**
     * @brief getInstance Used for initializing subtest with p-values
     * @param statistics Set of statistics of the subtest
     * @param pvalues Set of p-values
     * @return instance
     */
    static SubTestResult getInstance(
            const std::vector<Statistic> & statistics,
            const std::vector<double> & pvalues);

    /**
     * @brief getTestParameters
     * @return Parameters of the subtest
     */
    std::vector<std::pair<std::string, std::string>> getTestParameters() const;

    /**
     * @brief setTestParameters
     * @param value Parameters of the subtest
     */
    void setTestParameters(
            const std::vector<std::pair<std::string, std::string> > & value);

    /**
     * @brief getStatResults
     * @return Results of all underlying statistics
     */
    std::vector<double> getStatResults() const;

    /**
     * @brief getPvalues
     * @return Set of p-values
     */
    std::vector<double> getPvalues() const;

    /**
     * @brief getStatistics
     * @return All Statistics objects of given subtest
     */
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

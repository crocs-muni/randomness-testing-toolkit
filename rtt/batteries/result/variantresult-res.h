#ifndef RTT_BATTERIES_RESULT_VARIANTRESULT_H
#define RTT_BATTERIES_RESULT_VARIANTRESULT_H

#include "rtt/batteries/result/subtestresult-res.h"
#include "rtt/batteries/batteryoutput.h"

namespace rtt {
namespace batteries {
namespace result {

/**
 * @brief The VariantResult class Used for holding results of single variant of some test
 */
class VariantResult {
public:
    /**
     * @brief getInstance Creates initialized instance of VariantResult
     * @param subResults Results of subtests of this Variant
     * @param userSettings Settings created by user in configuration
     * @param battOut Output of the battery that will be processed
     * @return instance
     */
    static VariantResult getInstance(
            const std::vector<SubTestResult> & subResults,
            const std::vector<std::pair<std::string, std::string>> & userSettings,
            const BatteryOutput & battOut);

    /**
     * @brief getSubTestStatResults
     * @return All results of statistics of underlying subtests
     */
    std::vector<double> getSubTestStatResults() const;

    /**
     * @brief getSubResults
     * @return Result objects of underlying subtests
     */
    std::vector<SubTestResult> getSubResults() const;

    /**
     * @brief getBatteryOutput
     * @return Raw output of battery executable
     */
    BatteryOutput getBatteryOutput() const;

    /**
     * @brief getUserSettings
     * @return Settings chosen by user in configuration file.
     */
    std::vector<std::pair<std::string, std::string> > getUserSettings() const;

private:
    VariantResult(const std::vector<SubTestResult> & subResults,
                  const std::vector<std::pair<std::string, std::string>> & userSettings,
                  const BatteryOutput & battOut)
        : subResults(subResults), userSettings(userSettings),
          battOut(battOut)
    {}

    std::vector<SubTestResult> subResults;
    std::vector<std::pair<std::string, std::string>> userSettings;
    BatteryOutput battOut;
};

} // namespace result
} // namespace batteries
} // namespace rtt

#endif // RTT_BATTERIES_RESULT_VARIANTRESULT_H

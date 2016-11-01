#ifndef RTT_BATTERIES_RESULT_VARIANTRESULT_H
#define RTT_BATTERIES_RESULT_VARIANTRESULT_H

#include "rtt/batteries/result/subtestresult-res.h"
#include "rtt/batteries/batteryoutput.h"

namespace rtt {
namespace batteries {
namespace result {

class VariantResult {
public:
    static VariantResult getInstance(
            const std::vector<SubTestResult> & subResults,
            const std::vector<std::pair<std::string, std::string>> & userSettings,
            const BatteryOutput & battOut);

    std::vector<double> getSubTestStatResults() const;

    std::vector<SubTestResult> getSubResults() const;

    BatteryOutput getBatteryOutput() const;


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

#ifndef RTT_BATTERIES_TESTU01_TESTRESULT_H
#define RTT_BATTERIES_TESTU01_TESTRESULT_H

#include "rtt/batteries/itestresult-batt.h"

#include "rtt/batteries/testu01/variant-tu01.h"

namespace rtt {
namespace batteries {
namespace testu01 {

class TestResult : public ITestResult {
public:
    static std::unique_ptr<TestResult> getInstance(
            const std::vector<ITest *> & tests);

private:
    BatteryArg battery;

    TestResult(Logger * logger , std::string testName)
        : ITestResult(logger , testName)
    {}

    static std::regex buildParamRegex(
            std::vector<std::string> paramNames);

    static double convertStringToDouble(const std::string & num,
                                        const std::string & oneMinus);

    std::vector<result::Statistic> extractStatistics(
            const std::string & testLog,
            std::vector<std::string> statNames);

    std::vector<std::pair<std::string, std::string> > extractTestParameters(
            const std::string & testLog,
            std::vector<std::string> paramNames);

    std::vector<double> extractPValues(const std::string & testLog);
    std::string extractProblems(const std::string & testLog);
};

} // namespace testu01
} // namespace batteries
} // namespace rtt

#endif // RTT_BATTERIES_TESTU01_TESTRESULT_H

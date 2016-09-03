#ifndef RTT_BATTERIES_TESTU01_RESULT_H
#define RTT_BATTERIES_TESTU01_RESULT_H

#include "rtt/batteries/iresult-batt.h"

#include "rtt/batteries/testu01/variant-tu01.h"

namespace rtt {
namespace batteries {
namespace testu01 {

class Result : public IResult {
public:
    static std::unique_ptr<Result> getInstance(
            const std::vector<ITest *> & tests);

private:
    Constants::Battery battId;

    Result(Logger * logger , std::string testName)
        : IResult(logger , testName)
    {}

    static std::regex buildParamRegex(
            std::vector<std::string> paramNames);

    static double convertStringToDouble(const std::string & num,
                                        const std::string & oneMinus);

    std::vector<result::PValueSet> extractPValueSets(
            const std::string & testLog,
            std::vector<std::string> statNames);

    std::vector<std::string> extractTestParameters(
            const std::string & testLog,
            std::vector<std::string> paramNames);
};

} // namespace testu01
} // namespace batteries
} // namespace rtt

#endif // RTT_BATTERIES_TESTU01_RESULT_H

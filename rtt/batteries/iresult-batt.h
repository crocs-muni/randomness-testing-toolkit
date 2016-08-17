#ifndef RTT_BATTERIES_IRESULT_H
#define RTT_BATTERIES_IRESULT_H

#include "rtt/batteries/itest-batt.h"
#include "rtt/storage/istorage.h"

namespace rtt {
namespace batteries {

class IResult {
public:
    static std::unique_ptr<IResult> getInstance(const std::vector<ITest *> & tests);

    virtual void writeResults(storage::IStorage * storage) = 0;

protected:
    IResult() {}
};

class PValueSet {
public:
    static PValueSet getInstance(std::string statName, double statRes,
                                 std::vector<double> pValues);

    std::string getStatName() const;

    double getStatRes() const;

    std::vector<double> getPValues() const;

    bool getStatPassed() const;

private:
    PValueSet(std::string statName, double statRes,
              std::vector<double> pValues)
        : statName(statName), statRes(statRes), pValues(pValues)
    {}

    std::string statName;
    double statRes;
    bool statPassed = false;
    std::vector<double> pValues;
};

class SubTestResult {
public:
    static SubTestResult getInstance(std::vector<PValueSet> pValSets);

    std::vector<double> getStatResults() const;

    std::vector<PValueSet> getPValSets() const;

private:
    SubTestResult(std::vector<PValueSet> pValSets)
        : pValSets(pValSets)
    {}

    std::vector<PValueSet> pValSets;
};

class VariantResult {
public:
    static VariantResult getInstance(std::vector<SubTestResult> subResults);

    std::vector<double> getSubTestStatResults() const;

    std::vector<SubTestResult> getSubResults() const;

private:
    VariantResult(std::vector<SubTestResult> subResults)
        : subResults(subResults)
    {}

    std::vector<SubTestResult> subResults;
};

} // namespace batteries
} // namespace rtt

#endif // RTT_BATTERIES_IRESULT_H

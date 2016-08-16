#ifndef RTT_BATTERIES_TESTU01_TEST_H
#define RTT_BATTERIES_TESTU01_TEST_H

#include <string>
#include <string.h>
#include <vector>
#include <sstream>
#include <tuple>

#include "rtt/batteries/itest-batt.h"

namespace rtt {
namespace batteries {
namespace testu01 {

/* Typedefs for parameter types */
typedef std::pair<std::string , std::string> tParam;
typedef std::vector<std::string> tStringVector;

class Test : public ITest {
public:
    /*
    ======================
    *** Public methods ***
    ======================
    */
    static std::unique_ptr<Test> getInstance(int testId ,
                                             const GlobalContainer & container);

    std::vector<std::string> getTestUserSettings() const;

    std::vector<std::string> getStatistics() const;

    std::vector<std::vector<std::string>> getTestsParameters() const;

    //std::vector<std::vector<tParam>> getSubTestSettings() const;

    int getRepetitions() const;

    uint getSubTestCount() const;

private:
    /*
    =================
    *** Variables ***
    =================
    */
    std::vector<IVariant> variants;
    /* Following vars will be set after test execution */
    /* Number of statistics calculated in each test
     * resulting pval count = reps*statCount*subTestCount */
    uint statCount;
    /* Number of subtests executed - different from repetitions,
     * as multiple subtests can be executed in single repetition. */
    uint subTestCount;
    /* Parsed parameters of each subtest. */
    std::vector<std::vector<tParam>> subTestsParameters;

    /*
    ===============
    *** Methods ***
    ===============
    */
    Test(int testIndex , const GlobalContainer & container)
        : ITest(testIndex , container)
    {}

    std::string createArgs() const;

    void processBatteryOutput();

    void extractSettingsFromLog(const std::string & testLog);

    double convertStringToDouble(const std::string & num,
                                 const std::string & oneMinus);
};

} // namespace testu01
} // namespace batteries
} // namespace rtt

#endif // RTT_BATTERIES_TESTU01_TEST_H

#ifndef RTT_BATTERIES_TESTU01_TEST_H
#define RTT_BATTERIES_TESTU01_TEST_H

#include <string>
#include <string.h>
#include <vector>
#include <sstream>
#include <tuple>

#include "rtt/globalcontainer.h"
#include "rtt/batteries/itest-batt.h"
#include "rtt/batteries/testrunner-batt.h"
#include "rtt/batteries/testconstants.h"

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
    static std::unique_ptr<Test> getInstance(int testIndex ,
                                             const GlobalContainer & container);

    void execute();

    std::vector<std::string> getParameters() const;

    std::vector<std::string> getStatistics() const;

private:
    /*
    =================
    *** Variables ***
    =================
    */
    /* These fields will be set after initialization in */
    /* getInstance() */
    tStringVector paramNames;
    tStringVector statisticNames;
    int repetitions;
    /* Only used in crush batteres */
    std::vector<tParam> params;
    /* Used in rabbit/alphabit battery */
    std::string bit_nb;
    std::string bit_r;
    std::string bit_s;
    /* Following vars will be set after test execution */
    /* Number of statistics calculated in each test
     * resulting pval count = reps*statCount */
    uint statCount;

    /*
    ===============
    *** Methods ***
    ===============
    */
    Test(int testIndex , const GlobalContainer & container)
        : ITest(testIndex , container) {}

    std::string createArgs() const;

    void extractPvalues();

    void saveTestLogToFile();

    double convertStringToDouble(const std::string & num,
                                 const std::string & oneMinus);
};

} // namespace testu01
} // namespace batteries
} // namespace rtt

#endif // RTT_BATTERIES_TESTU01_TEST_H

#ifndef RTT_BATTERIES_NISTSTS_TEST_H
#define RTT_BATTERIES_NISTSTS_TEST_H

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
namespace niststs {

typedef std::tuple<int , std::string , std::string , int , bool> tTestInfo;

class Test : public ITest {
public:
    /*
    ======================
    *** Public methods ***
    ======================
    */
    /* Some getters for results will be probably added in time */
    static std::unique_ptr<Test> getInstance(int testIndex ,
                                             const GlobalContainer & container);

    std::vector<std::string> getTestUserSettings() const;

    std::vector<std::vector<std::string>> getTestsParameters() const;

    std::vector<std::string> getStatistics() const;

private:
    /*
    =================
    *** Variables ***
    =================
    */
    /* These fields will be set after initialization in */
    /* getInstance */
    std::string streamSize;
    std::string streamCount;
    std::string blockLength;
    /* Following fields will be initialized in getInstance */
    /* to default values according to test index */
    std::string resultSubDir;
    int subTestCount;
    bool adjustableBlockLen;
    /* Following fileds will be set after calling */
    /* execute */

    /*
    ===============
    *** Methods ***
    ===============
    */
    /* I don't want to allow existence of Test objects */
    /* without initialization that is in getInstance */
    Test(int testIndex , const GlobalContainer & container)
        : ITest(testIndex , container) {}

    std::string createArgs() const;

    std::string createInput() const;

    void processBatteryOutput();

    tTestPvals readPvals(const std::string & fileName);
};

} // namespace niststs
} // namespace batteries
} // namespace rtt

#endif // RTT_BATTERIES_NISTSTS_TEST_H

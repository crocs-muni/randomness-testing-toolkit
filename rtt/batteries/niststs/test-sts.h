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
#include "rtt/batteries/ivariant-batt.h"

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
    static std::unique_ptr<Test> getInstance(int testIndex ,
                                             const GlobalContainer & cont);

    std::vector<std::string> getTestUserSettings() const;

    std::vector<std::vector<std::string>> getTestsParameters() const;

    std::vector<std::string> getStatistics() const;

private:
    /*
    =================
    *** Variables ***
    =================
    */
    std::string resultSubDir;
    std::vector<std::unique_ptr<IVariant>> variants;

    /*
    ===============
    *** Methods ***
    ===============
    */
    Test(int testIndex , const GlobalContainer & container)
        : ITest(testIndex , container)
    {}

    std::string createArgs() const;

    std::string createInput() const;

    void processBatteryOutput();

    tTestPvals readPvals(const std::string & fileName);
};

} // namespace niststs
} // namespace batteries
} // namespace rtt

#endif // RTT_BATTERIES_NISTSTS_TEST_H

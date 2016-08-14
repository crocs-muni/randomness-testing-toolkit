#ifndef RTT_BATTERIES_DIEHARDER_TEST_H
#define RTT_BATTERIES_DIEHARDER_TEST_H

#include <string.h>
#include <vector>

#include "rtt/batteries/itest-batt.h"
#include "rtt/batteries/testrunner-batt.h"
#include "rtt/batteries/dieharder/setting-dh.h"
#include "rtt/batteries/testconstants.h"
#include "rtt/batteries/ivariant-batt.h"

namespace rtt {
namespace batteries {
namespace dieharder {

typedef std::pair<int , std::string> tTestInfo;

class Test : public ITest {
public:
    /*
    ======================
    *** Public methods ***
    ======================
    */
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
    std::vector<std::unique_ptr<IVariant>> variants;

    /*
    ===============
    *** Methods ***
    ===============
    */
    Test(int testIndex , const GlobalContainer & container)
        : ITest(testIndex , container) {}

    std::string createArgs() const;

    void processBatteryOutput();
};

} // namespace dieharder
} // namespace batteries
} // namespace rtt

#endif // RTT_BATTERIES_DIEHARDER_TEST_H

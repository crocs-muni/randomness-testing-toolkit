#ifndef RTT_BATTERIES_DIEHARDER_TEST_H
#define RTT_BATTERIES_DIEHARDER_TEST_H

#include <string.h>
#include <vector>

#include "rtt/batteries/itest-batt.h"

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
    static std::unique_ptr<Test> getInstance(int testId ,
                                             const GlobalContainer & container);

    std::vector<std::string> getTestUserSettings() const;

    std::vector<std::vector<std::string>> getTestsParameters() const;

    std::vector<std::string> getStatistics() const;

private:
    /*
    ===============
    *** Methods ***
    ===============
    */
    Test(int testIndex , const GlobalContainer & container)
        : ITest(testIndex , container)
    {}

    void processBatteryOutput();
};

} // namespace dieharder
} // namespace batteries
} // namespace rtt

#endif // RTT_BATTERIES_DIEHARDER_TEST_H

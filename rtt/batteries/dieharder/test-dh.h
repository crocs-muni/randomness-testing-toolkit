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
    static std::unique_ptr<Test> getInstance(std::string battObjInf, int testId,
                                             const GlobalContainer & container);
private:
    /* Methods */
    Test(std::string battObjInf, int testIndex,
         const GlobalContainer & container)
        : ITest(battObjInf, testIndex, container)
    {}
};

} // namespace dieharder
} // namespace batteries
} // namespace rtt

#endif // RTT_BATTERIES_DIEHARDER_TEST_H

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
    static std::unique_ptr<Test> getInstance(std::string battObjInf, int testId ,
                                             const GlobalContainer & container);
private:

    /* Methods */
    Test(std::string battObjInf, int testIndex,
         const GlobalContainer & container)
        : ITest(battObjInf, testIndex , container)
    {}
};

} // namespace testu01
} // namespace batteries
} // namespace rtt

#endif // RTT_BATTERIES_TESTU01_TEST_H

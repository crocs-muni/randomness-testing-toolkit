#include "rtt/batteries/dieharder/test-dh.h"

namespace rtt {
namespace batteries {
namespace dieharder {

std::unique_ptr<Test> Test::getInstance(int testIndex , const GlobalContainer & container) {
    std::unique_ptr<Test> t (new Test(testIndex , container));

    t->logicName = std::get<0>(TestConstants::getDieharderTestData(
                                   t->battId , t->testId));
    return t;
}

} // namespace dieharder
} // namespace batteries
} // namespace rtt


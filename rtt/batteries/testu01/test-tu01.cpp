#include "rtt/batteries/testu01/test-tu01.h"

namespace rtt {
namespace batteries {
namespace testu01 {

std::unique_ptr<Test> Test::getInstance(int testIndex ,
                                        const GlobalContainer & container) {
    std::unique_ptr<Test> t (new Test(testIndex , container));

    t->logicName =
            std::get<0>(TestConstants::getTu01TestData(t->battId , t->testId));

    return t;
}

} // namespace testu01
} // namespace batteries
} // namespace rtt


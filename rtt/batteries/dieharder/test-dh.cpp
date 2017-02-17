#include "rtt/batteries/dieharder/test-dh.h"

namespace rtt {
namespace batteries {
namespace dieharder {

std::unique_ptr<Test> Test::getInstance(std::string battObjInf, int testIndex,
                                        const GlobalContainer & container) {
    std::unique_ptr<Test> t (new Test(battObjInf, testIndex, container));

    /* Battery specific code goes here */

    return t;
}

} // namespace dieharder
} // namespace batteries
} // namespace rtt


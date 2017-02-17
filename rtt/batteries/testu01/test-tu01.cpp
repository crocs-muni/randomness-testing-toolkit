#include "rtt/batteries/testu01/test-tu01.h"

namespace rtt {
namespace batteries {
namespace testu01 {

std::unique_ptr<Test> Test::getInstance(std::string battObjInf, int testIndex ,
                                        const GlobalContainer & container) {
    std::unique_ptr<Test> t (new Test(battObjInf, testIndex , container));

    /* Battery specific code goes here */

    return t;
}

} // namespace testu01
} // namespace batteries
} // namespace rtt


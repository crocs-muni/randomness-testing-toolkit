#include "test-sts.h"

#include "rtt/batteries/niststs/variant-sts.h"

namespace rtt {
namespace batteries {
namespace niststs {

std::unique_ptr<Test> Test::getInstance(std::string battObjInf, int testIndex,
                                        const GlobalContainer & cont) {
    std::unique_ptr<Test> t (new Test(battObjInf, testIndex , cont));

    /* Battery specific code goes here */

    t->testDir_mux = std::make_unique<std::mutex>();

    for(const std::unique_ptr<IVariant> & var : t->variants) {
        Variant * stsVar = dynamic_cast<Variant*>(var.get());
        stsVar->setTestDir_mux(t->testDir_mux.get());
    }

    return t;
}

} // namespace niststs
} // namespace batteries
} // namespace rtt

#include "rtt/batteries/dieharder/battery-dh.h"

#include "rtt/batteries/iresult-batt.h"

namespace rtt {
namespace batteries {
namespace dieharder {

std::unique_ptr<Battery> Battery::getInstance(const GlobalContainer & container) {
    std::unique_ptr<Battery> b (new Battery(container));
    return b;
}

void Battery::processStoredResults() {
    if(!executed)
        throw RTTException(objectInfo , Strings::BATT_ERR_NO_EXEC_PROC);

    for(const auto & test : tests) {
        std::vector<ITest *> tsts = { test.get() };
        std::unique_ptr<IResult> res = IResult::getInstance(tsts);
        res->writeResults(storage.get(), 8);
    }

    storage->finalizeReport();
}

} // namespace dieharder
} // namespace batteries
} // namespace rtt


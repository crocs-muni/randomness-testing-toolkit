#include "rtt/batteries/niststs/battery-sts.h"

#include "rtt/batteries/iresult-batt.h"

namespace rtt {
namespace batteries {
namespace niststs {

std::unique_ptr<Battery> Battery::getInstance(const GlobalContainer & container) {
    std::unique_ptr<Battery> b (new Battery(container));
    return b;
}

void Battery::storeResults() {
    if(!executed)
        throw RTTException(objectInfo , Strings::BATT_ERR_NO_EXEC_PROC);

    for(const auto & test : tests) {
        std::vector<ITest *> tests = { test.get() };
        std::unique_ptr<IResult> res = IResult::getInstance(tests);
        res->writeResults(storage.get(), 6);
    }
    storage->finalizeReport();
}

} // namespace niststs
} // namespace batteries
} // namespace rtt

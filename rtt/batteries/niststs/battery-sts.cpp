#include "rtt/batteries/niststs/battery-sts.h"

#include "rtt/batteries/itestresult-batt.h"

namespace rtt {
namespace batteries {
namespace niststs {

std::unique_ptr<Battery> Battery::getInstance(const GlobalContainer & container) {
    std::unique_ptr<Battery> b (new Battery(container));
    return b;
}

std::vector<std::unique_ptr<ITestResult>> Battery::getTestResults() const {
    if(!executed)
        throw RTTException(objectInfo , Strings::BATT_ERR_NO_EXEC_PROC);

    std::vector<std::unique_ptr<ITestResult>> results(tests.size());
    std::transform(tests.begin(), tests.end(), results.begin(),
                   [](const auto & el){ return ITestResult::getInstance({el.get()}); });

    return results;
}

} // namespace niststs
} // namespace batteries
} // namespace rtt

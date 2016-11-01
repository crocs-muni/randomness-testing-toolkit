#include "rtt/batteries/testu01/battery-tu01.h"

#include "rtt/batteries/itestresult-batt.h"

namespace rtt {
namespace batteries {
namespace testu01 {

std::unique_ptr<Battery> Battery::getInstance(const GlobalContainer & container) {
    std::unique_ptr<Battery> b (new Battery(container));
    return b;
}

std::vector<std::unique_ptr<ITestResult>> Battery::getTestResults() const {
    if(!executed)
        throw RTTException(objectInfo, Strings::BATT_ERR_NO_EXEC_PROC);

    /* Tests with same name are considered variants of the
     * same test and are therefore bundled together. */
    std::vector<std::unique_ptr<ITestResult>> results;
    std::vector<ITest *> testBatch;
    std::string currTestName;

    for(uint i = 0; i < tests.size(); ++i) {
        if(currTestName.empty())
            currTestName = tests.at(i)->getLogicName();

        if(currTestName == tests.at(i)->getLogicName()) {
            testBatch.push_back(tests.at(i).get());
        } else {
            results.push_back(ITestResult::getInstance(testBatch));
            testBatch.clear();
            currTestName = tests.at(i)->getLogicName();
            testBatch.push_back(tests.at(i).get());
        }

        if(i + 1 == tests.size()) {
            results.push_back(ITestResult::getInstance(testBatch));
        }
    }

    return results;
}

} // namespace testu01
} // namespace batteries
} // namespace rtt


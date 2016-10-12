#include "rtt/batteries/testu01/battery-tu01.h"

#include "rtt/batteries/iresult-batt.h"

namespace rtt {
namespace batteries {
namespace testu01 {

std::unique_ptr<Battery> Battery::getInstance(const GlobalContainer & container) {
    std::unique_ptr<Battery> b (new Battery(container));
    return b;
}

void Battery::storeResults() {
    if(!executed)
        throw RTTException(objectInfo , Strings::BATT_ERR_NO_EXEC_PROC);

    std::vector<ITest *> testBatch;
    std::string currentTestName;
    for(uint i = 0 ; i < tests.size() ; ++i) {
        if(currentTestName.empty())
            currentTestName = tests.at(i)->getLogicName();

        if(currentTestName == tests.at(i)->getLogicName()) {
            testBatch.push_back(tests.at(i).get());
        } else {
            auto res = IResult::getInstance(testBatch);
            res->writeResults(storage.get(), 4);
            testBatch.clear();
            currentTestName = tests.at(i)->getLogicName();
            testBatch.push_back(tests.at(i).get());
        }

        if(i + 1 == tests.size()) {
            auto res = IResult::getInstance(testBatch);
            res->writeResults(storage.get(), 4);
        }
    }
    storage->finalizeReport();
}

} // namespace testu01
} // namespace batteries
} // namespace rtt


#include "battery-tu01.h"

namespace rtt {
namespace batteries {
namespace testu01 {

std::unique_ptr<Battery> Battery::getInstance(const GlobalContainer & container) {
    std::unique_ptr<Battery> b (new Battery(container));
    return b;
}

void Battery::processStoredResults() {
    if(!executed)
        throw RTTException(objectInfo , Strings::BATT_ERR_NO_EXEC_PROC);

    logger->info(objectInfo + Strings::BATT_INFO_PROCESSING_STARTED);

    /* Log storage */
    std::string batteryLog;
    for(auto & i : tests)
        i->appendTestLog(batteryLog);

    Utils::createDirectory(Utils::getPathWithoutLastItem(logFilePath));
    Utils::saveStringToFile(logFilePath , batteryLog);

    /* Result storage */
    for(const auto & test : tests) {
        storage->addNewTest(test->getLogicName());
        storage->setTestOptions(test->getParameters());

        std::vector<std::string> statistics = test->getStatistics();
        std::vector<tTestPvals> results = test->getResults();
        if(results.size() == 1) { /* Test w/out repetitions */
            for(size_t i = 0 ; i < statistics.size() ; ++i)
                /* Number of statistics and number of results of single
                   test is always the same */
                storage->addStatisticResult(statistics.at(i) , results.at(0).at(i) , 4);
        } else { /* Test had repetitions, create multiple subtests */
            for(const auto & result : results) {
                storage->addSubTest();
                for(size_t i = 0 ; i < statistics.size() ; ++i)
                    storage->addStatisticResult(statistics.at(i) , result.at(i) , 4);
                storage->finalizeSubTest();
            }
        }
        storage->finalizeTest();
    }
    storage->finalizeReport();
    logger->info(objectInfo + Strings::BATT_INFO_PROCESSING_COMPLETE);
}

} // namespace testu01
} // namespace batteries
} // namespace rtt


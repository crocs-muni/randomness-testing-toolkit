#include "battery-tu01.h"
#include "rtt/batteries/testu01/test-tu01.h"

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

    /* Result storage */
    for(auto & test : tests) {
        storage->addNewTest(test->getLogicName());
        storage->setUserSettings(test->getTestUserSettings());

        /* Writing issues */
        storage->setRuntimeIssues(test->getBatteryStdErr(),
                                  test->getBatteryErrors(),
                                  test->getBatteryWarnings());

        /* Indicates whether parameters will or will not be stored in report.
         * Parameters are not stored when they are inproperly extracted from logs.
         * This does not indicate invalidity of results, only log in unexpected format!! */
        bool storeParams = true;
        std::vector<std::string> statistics = test->getStatistics();
        std::vector<tTestPvals> results = test->getResults();
        std::vector<std::vector<std::string>>  parameters = test->getTestsParameters();
        if(parameters.size() != results.size())
            storeParams = false;

        if(results.size() == 1) { /* Test w/out repetitions */
            if(storeParams)
                storage->setTestParameters(parameters.at(0));
            for(size_t i = 0 ; i < statistics.size() ; ++i)
                /* Number of statistics and number of results of single
                   test is always the same */
                storage->addStatisticResult(statistics.at(i) , results.at(0).at(i) , 4);
        } else { /* Test had repetitions, create multiple subtests */
            //for(const auto & result : results) {
            for(size_t i = 0 ; i < results.size() ; ++i) {
                storage->addSubTest();
                if(storeParams)
                    storage->setTestParameters(parameters.at(i));
                for(size_t l = 0 ; l < statistics.size() ; ++l)
                    storage->addStatisticResult(statistics.at(l) , results.at(i).at(l) , 4);
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


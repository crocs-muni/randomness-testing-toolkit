#include "battery-tu01.h"

namespace rtt {
namespace batteries {
namespace testu01 {

const std::string Battery::XPATH_LOG_DIRECTORY                  = "TOOLKIT_SETTINGS/LOGGER/TESTU01_DIR";
const std::string Battery::XPATH_DEFAULT_TESTS_SMALL_CRUSH      = "TESTU01_SETTINGS/DEFAULT_TESTS_SCRUSH";
const std::string Battery::XPATH_DEFAULT_TESTS_CRUSH            = "TESTU01_SETTINGS/DEFAULT_TESTS_CRUSH";
const std::string Battery::XPATH_DEFAULT_TESTS_BIG_CRUSH        = "TESTU01_SETTINGS/DEFAULT_TESTS_BCRUSH";
const std::string Battery::XPATH_DEFAULT_TESTS_RABBIT           = "TESTU01_SETTINGS/DEFAULT_TESTS_RABBIT";
const std::string Battery::XPATH_DEFAULT_TESTS_ALPHABIT         = "TESTU01_SETTINGS/DEFAULT_TESTS_ALPHABIT";

std::unique_ptr<Battery> Battery::getInstance(const Globals & globals) {
    std::unique_ptr<Battery> b (new Battery());
    b->cliOptions = globals.getCliOptions();
    b->batteryConfiguration = globals.getBatteryConfiguration();
    b->toolkitSettings = globals.getToolkitSettings();
    b->battery = b->cliOptions->getBattery();
    b->objectInfo = Constants::batteryToString(b->battery);
    b->creationTime = Utils::getRawTime();

    std::cout << "[INFO] Processing file: " << b->cliOptions->getBinFilePath()
              << std::endl;

    /* Getting path to log file */
    b->logFilePath = b->toolkitSettings->getLoggerBatteryDir(b->battery);
    b->logFilePath.append(Utils::formatRawTime(b->creationTime , "%Y%m%d%H%M%S"));
    b->logFilePath.append(
                "-" + Utils::getLastItemInPath(b->cliOptions->getBinFilePath() + ".log"));

    /* Creating storage for results */
    b->storage = output::OutputFactory::createOutput(globals , b->creationTime);
    /* Getting constants of tests to be executed */
    std::vector<int> testConsts = b->cliOptions->getTestConsts();
    if(testConsts.empty())
        testConsts = b->batteryConfiguration->getBatteryDefaultTests(b->battery);
    if(testConsts.empty())
        throw RTTException(b->objectInfo , "no tests were set for execution");

    for(int i : testConsts) {
        std::unique_ptr<ITest> test = Test::getInstance(i , globals);
        b->tests.push_back(std::move(test));
    }

    //delete cfgRoot;
    return b;
}

void Battery::runTests() {
    if(executed)
        throw RTTException(objectInfo , "battery was already executed");

    TestRunner::executeTests(std::ref(tests));

    executed = true;
}

void Battery::processStoredResults() {
    if(!executed)
        throw RTTException(objectInfo , "battery must be executed before result processing");

    std::cout << "Storing battery logs and results." << std::endl;

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
}

} // namespace testu01
} // namespace batteries
} // namespace rtt


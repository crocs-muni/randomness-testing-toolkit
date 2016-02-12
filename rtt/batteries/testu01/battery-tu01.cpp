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

std::unique_ptr<Battery> Battery::getInstance(const CliOptions & options) {
    std::unique_ptr<Battery> battery (new Battery());
    battery->creationTime = Utils::getRawTime();

    TiXmlNode * cfgRoot = NULL;
    loadXMLFile(cfgRoot , options.getInputCfgPath());

    /* Getting path to log file */
    battery->logFilePath = std::move(
                createLogFilePath(
                    battery->creationTime,
                    getXMLElementValue(cfgRoot , XPATH_LOG_DIRECTORY),
                    options.getBinFilePath()));
    /* Creating storage for results */
    battery->storage = output::InterfaceFactory::createOutput(cfgRoot ,
                                                              options ,
                                                              battery->creationTime);
    /* Getting constants of tests to be executed */
    std::vector<int> testConsts = options.getTestConsts();
    if(testConsts.empty()) {
        /* Read them from config if no tests were entered via CLI */
        std::string testsXPath;
        switch(options.getBattery()) {
        case Constants::BATTERY_TU01_SMALLCRUSH:
            testsXPath = XPATH_DEFAULT_TESTS_SMALL_CRUSH;
            break;
        case Constants::BATTERY_TU01_CRUSH:
            testsXPath = XPATH_DEFAULT_TESTS_CRUSH;
            break;
        case Constants::BATTERY_TU01_BIGCRUSH:
            testsXPath = XPATH_DEFAULT_TESTS_BIG_CRUSH;
            break;
        case Constants::BATTERY_TU01_RABBIT:
            testsXPath = XPATH_DEFAULT_TESTS_RABBIT;
            break;
        case Constants::BATTERY_TU01_ALPHABIT:
            testsXPath = XPATH_DEFAULT_TESTS_ALPHABIT;
            break;
        }
        testConsts = parseIntValues(getXMLElementValue(cfgRoot , testsXPath));
    }
    if(testConsts.empty())
        throw std::runtime_error("no tests for execution were set in options "
                                 "and in config file");

    for(int i : testConsts) {
        Test test = Test::getInstance(i , options , cfgRoot);
        battery->tests.push_back(std::move(test));
    }

    delete cfgRoot;
    return battery;
}

void Battery::runTests() {
    for(auto & i : tests)
        i.execute();

    executed = true;
}

void Battery::processStoredResults() {
    if(!executed)
        throw std::runtime_error("can't process results before execution of battery");

    std::cout << "Storing battery logs and results." << std::endl;

    /* Log storage */
    std::string batteryLog;
    for(auto & i : tests)
        i.appendTestLog(batteryLog);

    Utils::createDirectory(Utils::getPathWithoutLastItem(logFilePath));
    Utils::saveStringToFile(logFilePath , batteryLog);

    /* Result storage */
    for(const Test & test :tests) {
        storage->addNewTest(test.getLogicName());
        storage->setTestOptions(test.getParameters());

        std::vector<std::string> statistics = test.getStatistics();
        std::vector<tTestPvals> results = test.getResults();
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


#include "battery-tu01.h"

namespace rtt {
namespace batteries {
namespace testu01 {

const std::string Battery::XPATH_LOG_DIRECTORY = "TOOLKIT_SETTINGS/LOGGER/TESTU01_DIR";

std::unique_ptr<Battery> Battery::getInstance(const CliOptions & options) {
    std::unique_ptr<Battery> battery (new Battery());

    TiXmlNode * cfgRoot = NULL;
    loadXMLFile(cfgRoot , options.getInputCfgPath());

    /* Setting log */
    std::string logFileName;
    logFileName = getXMLElementValue(cfgRoot , XPATH_LOG_DIRECTORY);
    if(logFileName.empty())
        throw std::runtime_error("empty tag: " + XPATH_LOG_DIRECTORY);

    std::string binFileName =
            Utils::getLastItemInPath(options.getBinFilePath());
    std::string datetime = Utils::getDateTime();
    if(logFileName.back() != '/')
        logFileName.append("/");
    logFileName.append(datetime + "-" + binFileName + ".log");
    battery->logFileName = std::move(logFileName);

    /* Setting output storage */
    battery->storage = output::InterfaceFactory::createOutput(cfgRoot ,
                                                              options ,
                                                              datetime);

    for(int i : options.getTestConsts()) {
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

    Utils::createDirectory(Utils::getPathWithoutLastItem(logFileName));
    Utils::saveStringToFile(logFileName , batteryLog);

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
                storage->addStatisticResult(statistics.at(i) , results.at(0).at(i));
        } else { /* Test had repetitions, create multiple subtests */
            for(const auto & result : results) {
                storage->addSubTest();
                for(size_t i = 0 ; i < statistics.size() ; ++i)
                    storage->addStatisticResult(statistics.at(i) , result.at(i));
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


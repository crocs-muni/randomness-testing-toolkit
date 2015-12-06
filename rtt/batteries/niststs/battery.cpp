#include "rtt/batteries/niststs/battery.h"

namespace rtt {
namespace batteries {
namespace niststs {

std::unique_ptr<Battery> Battery::getInstance(const CliOptions & options) {
    std::unique_ptr<Battery> battery (new Battery());
    TiXmlNode * cfgRoot = NULL;
    loadXMLFile(cfgRoot , options.getInputCfgPath());

    for(int i : options.getTestConsts()) {
        Test test = Test::getInstance(static_cast<TestIndex>(i) , cfgRoot , options.getBinFilePath());
        battery->tests.push_back(std::move(test));
    }

    delete cfgRoot;
    return battery;
}

void Battery::runTests() {
    /* Executing all tests in sequence here */
    /* In time, it's possible to add some multithreading */
    for(auto & i : tests)
        i.execute();

    /* Setting executed to true, allowing postprocessing */
    executed = true;
}

void Battery::processStoredResults() {
    if(!executed)
        throw std::runtime_error("can't process results before execution of battery");

    std::cout << "Momentarily, this does nothing!" << std::endl;
}



} // namespace niststs
} // namespace batteries
} // namespace rtt

#include "rtt/batteries/dieharder/test-dh.h"

namespace rtt {
namespace batteries {
namespace dieharder {

const int Test::OPTION_HEADER_FLAG      = 66047;
const int Test::OPTION_FILE_GENERATOR   = 201;

std::unique_ptr<Test> Test::getInstance(int testIndex , const GlobalContainer & container) {
    std::unique_ptr<Test> t (new Test(testIndex , container));

    std::tie(t->logicName) =
            TestConstants::getDieharderTestData(t->battery , t->testIndex);

    /* Setting psample count */
    t->pSampleCount = t->batteryConfiguration->getDieharderTestPSamples(t->testIndex);
    if(t->pSampleCount == Configuration::VALUE_INT_NOT_SET)
        t->pSampleCount = t->batteryConfiguration->getDieharderDefaultPSamples();
    if(t->pSampleCount == Configuration::VALUE_INT_NOT_SET)
        throw RTTException(t->objectInfo , "psample count not set");

    /* Getting default Dieharder options from config */
    std::string defaultArguments = t->batteryConfiguration->getDieharderDefaultArguments();
    /* Options are separated by space */
    defaultArguments.append(" ");
    defaultArguments
            .append(t->batteryConfiguration->getDieharderTestArguments(t->testIndex));

    /* Parsing loaded arguments */
    std::vector<std::string> vecOptions =
                std::move(Utils::split(defaultArguments , ' '));
    if(vecOptions.size() % 2 != 0)
        throw RTTException(t->objectInfo ,
                           "invalid test arguments format: each option must have value");
    for(size_t i = 0 ; i < vecOptions.size() ; ++i) {
        try {
            Setting setting =
                    Setting::getInstance(vecOptions[i] , vecOptions[i + 1]);
            t->settings.push_back(std::move(setting));
            ++i;
        } catch(std::runtime_error ex) {
            throw RTTException(t->objectInfo , ex.what());
        }
    }

    return t;
}

void Test::execute() {
    /* This method is turned into thread.
     * Will deadlock if run without main thread. */
    /* Add some logger info here */

    testLog = TestRunner::executeBinary(executablePath ,
                                        createArgs());
    extractPvalues();
    executed = true;
}

std::vector<std::string> Test::getParameters() const {
    std::stringstream parameters;
    parameters << "p-sample count: " << pSampleCount << std::endl;
    for(const Setting & setting : settings)
        parameters << setting.getLogicName() << ": "
                   << setting.getArgumentValue() << std::endl;
    return Utils::split(parameters.str() , '\n');
}

std::vector<std::string> Test::getStatistics() const {
    return {"Kolmogorov-Smirnov"};
}

/*
                     __                       __
                    |  \                     |  \
  ______    ______   \$$ __     __  ______  _| $$_     ______
 /      \  /      \ |  \|  \   /  \|      \|   $$ \   /      \
|  $$$$$$\|  $$$$$$\| $$ \$$\ /  $$ \$$$$$$\\$$$$$$  |  $$$$$$\
| $$  | $$| $$   \$$| $$  \$$\  $$ /      $$ | $$ __ | $$    $$
| $$__/ $$| $$      | $$   \$$ $$ |  $$$$$$$ | $$|  \| $$$$$$$$
| $$    $$| $$      | $$    \$$$   \$$    $$  \$$  $$ \$$     \
| $$$$$$$  \$$       \$$     \$     \$$$$$$$   \$$$$   \$$$$$$$
| $$
| $$
 \$$
*/

std::string Test::createArgs() const {
    std::stringstream arguments;
    arguments << "dieharder ";
    /* Dieharder can receive single option multiple times and
     * will take only the last one. Therefore, first are passed
     * default values from config, then there are test specific
     * value that override default ones and lastly, options that
     * MUST be set for correct battery functionality are entered. */
    for(const auto & it : settings) {
        it.getConsoleInput(arguments);
        arguments << " ";
    }
    /* Set psample count */
    arguments << "-p " << pSampleCount << " ";
    /* Specify test */
    arguments << "-d " << testIndex << " ";
    /* Specify header flag */
    arguments << "-D " << OPTION_HEADER_FLAG << " ";
    /* Specify binary file generator */
    arguments << "-g " << OPTION_FILE_GENERATOR << " ";
    /* Specify binary input file */
    arguments << "-f " << binaryDataPath;
    return arguments.str();
}

void Test::extractPvalues() {
    static const std::regex RE_PSAMPLE_VALUE {"\\+\\+\\+\\+([01]\\.[0-9]+?)\\+\\+\\+\\+\\n"};

    auto begin = std::sregex_iterator(testLog.begin() , testLog.end() ,
                                      RE_PSAMPLE_VALUE);
    auto end = std::sregex_iterator();

    int pValCount = std::distance(begin , end);
    if(pValCount == 0) {
        std::cout << "[WARNING] No pValues were extracted" << std::endl;
        return;
    }

    if(pValCount % pSampleCount != 0) {
        std::cout << "[WARNING] " << objectInfo << ": p-values can't be extracted from log. "
                     "Number of p-values present is not divisible by "
                     "number of p-samples per test." << std::endl;
        return;
    }

    subTestsCount = pValCount / pSampleCount;
    tTestPvals pSamples;

    for(int subTestIndex = 0 ; subTestIndex < subTestsCount ; ++subTestIndex) {
        for(int i = 0 ; i < pSampleCount ; ++i) {
            std::smatch match = *begin;
            pSamples.push_back(Utils::strtod(match[1].str()));
            ++begin;
        }
        results.push_back(std::move(pSamples));
        pSamples.clear();
    }
}

} // namespace dieharder
} // namespace batteries
} // namespace rtt


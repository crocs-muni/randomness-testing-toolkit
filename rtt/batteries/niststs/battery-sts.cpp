#include "rtt/batteries/niststs/battery-sts.h"

namespace rtt {
namespace batteries {
namespace niststs {

const std::string Battery::XPATH_LOG_DIRECTORY = "TOOLKIT_SETTINGS/LOGGER/NIST_STS_DIR";
const std::string Battery::XPATH_DEFAULT_TESTS = "NIST_STS_SETTINGS/DEFAULT_TESTS";

std::unique_ptr<Battery> Battery::getInstance(const CliOptions & options) {
    std::unique_ptr<Battery> battery (new Battery());
    battery->creationTime = Utils::getRawTime();

    TiXmlNode * cfgRoot = NULL;
    loadXMLFile(cfgRoot , options.getInputCfgPath());

    std::cout << "[INFO] Processing file: " << options.getBinFilePath() << std::endl;

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
    if(testConsts.empty()) /* Read them from config if no tests were entered via CLI */
        testConsts = parseIntValues(getXMLElementValue(cfgRoot , XPATH_DEFAULT_TESTS));
    if(testConsts.empty())
        throw std::runtime_error("no tests for execution were set in options "
                                 "and in config file");

    for(int i : testConsts) {
        Test test = Test::getInstance(i , cfgRoot , options);
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

    std::cout << "Storing log and results." << std::endl;

    /* Log storage */
    std::string batteryLog;
    for(auto & i : tests)
        i.appendTestLog(batteryLog);

    Utils::createDirectory(Utils::getPathWithoutLastItem(logFilePath));
    Utils::saveStringToFile(logFilePath , batteryLog);

    /* Result storage */
    for(const Test & test : tests) {
        storage->addNewTest(test.getLogicName());
        storage->setTestOptions(test.getSettings());

        std::vector<tTestPvals> results = test.getResults();
        bool propStatFailed;
        std::string propStat;

        if(results.size() == 1) { /* Single test */
            storage->addStatisticResult("Chi-square" , chi2_stat(results.at(0)) , 6);
            propStat = proportionStat(results.at(0) , &propStatFailed);
            storage->addStatisticResult("Proportion" , propStat , propStatFailed);
            storage->addPValues(results.at(0) , 6);
        } else { /* Multiple subtests */
            for(const auto & result : results) {
                storage->addSubTest();
                storage->addStatisticResult("Chi-square" , chi2_stat(result) , 6);
                propStat = proportionStat(result , &propStatFailed);
                storage->addStatisticResult("Proportion" , propStat , propStatFailed);
                storage->addPValues(result , 6);
                storage->finalizeSubTest();
            }
        }
        storage->finalizeTest();
    }
    storage->finalizeReport();
}

std::string Battery::proportionStat(tTestPvals pvals , bool * failed) {
    int passCount = 0;
    double p_hat = 1.0 - Constants::MATH_ALPHA;
    double proportion_threshold_max =
            (p_hat + 3.0 * sqrt((p_hat*Constants::MATH_ALPHA)/pvals.size())) * pvals.size();
    double proportion_threshold_min =
            (p_hat - 3.0 * sqrt((p_hat*Constants::MATH_ALPHA)/pvals.size())) * pvals.size();
    for(const auto & val : pvals) {
        if(val >= Constants::MATH_ALPHA)
            ++passCount;
    }
    if(passCount < proportion_threshold_min || passCount > proportion_threshold_max)
        *failed = true;
    else
        *failed = false;

    return {Utils::itostr(passCount) + "/" + Utils::itostr(pvals.size())};
}

/* Following code is taken from NIST STS source code */
/* Used for calculation of Chi2 statistic */
double Battery::chi2_stat(tTestPvals pvals) {
    int streamCount = pvals.size();
    int j, pos , expCount;
    double chi2 , uniformity;

    std::vector<int> freqPerBin(10 , 0);

    std::sort(pvals.begin() , pvals.end());
    for(j = 0 ; j <  streamCount ; ++j) {
        pos = (int)floor(pvals.at(j)*10);
        if(pos == 10)
            pos--;
        ++freqPerBin[pos];
    }
    chi2 = 0.0;
    expCount =  streamCount/10;
    if(expCount == 0) {
        uniformity = 0.0;
    } else {
        for (j = 0 ; j < 10 ; ++j)
            chi2 += pow(freqPerBin[j]-expCount, 2)/expCount;

        uniformity = Cephes::cephes_igamc(9.0/2.0, chi2/2.0);
    }
    return uniformity;
}



} // namespace niststs
} // namespace batteries
} // namespace rtt

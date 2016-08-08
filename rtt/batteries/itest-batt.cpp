#include "itest-batt.h"

#include "rtt/batteries/niststs/test-sts.h"
#include "rtt/batteries/dieharder/test-dh.h"
#include "rtt/batteries/testu01/test-tu01.h"

namespace rtt {
namespace batteries {

std::mutex outputFile_mux;

std::unique_ptr<ITest> ITest::getInstance(int testIndex , const GlobalContainer & container) {
    switch(container.getCliOptions()->getBattery()) {
    case Constants::Battery::DIEHARDER:
        return dieharder::Test::getInstance(testIndex , container);
    case Constants::Battery::NIST_STS:
        return niststs::Test::getInstance(testIndex , container);
    case Constants::Battery::TU01_SMALLCRUSH:
    case Constants::Battery::TU01_CRUSH:
    case Constants::Battery::TU01_BIGCRUSH:
    case Constants::Battery::TU01_RABBIT:
    case Constants::Battery::TU01_ALPHABIT:
    case Constants::Battery::TU01_BLOCK_ALPHABIT:
        return testu01::Test::getInstance(testIndex , container);
    default:
        raiseBugException(Strings::ERR_INVALID_BATTERY);
    }
}

void ITest::execute() {
    /* This method is turned into thread.
     * Will deadlock if run without main thread. */
    batteryOutput = TestRunner::executeBinary(logger , objectInfo , executablePath ,
                                              batteryArgs , batteryInput);

    /* p-values will be extracted from logs and stored in results */
    processBatteryOutput();

    batteryOutput.doDetection();
    if(!batteryOutput.getStdErr().empty())
        logger->warn(objectInfo + ": execution of test produced error output. Inspect logs.");
    if(!batteryOutput.getErrors().empty())
        logger->warn(objectInfo + ": test output contains errors.");
    if(!batteryOutput.getWarnings().empty())
        logger->warn(objectInfo + ": test output contains warnings.");

    /* Store test output into file */
    std::unique_lock<std::mutex> outputFile_lock(outputFile_mux);
    Utils::appendStringToFile(logFilePath , batteryOutput.getStdOut());
    Utils::appendStringToFile(logFilePath , batteryOutput.getStdErr());
    outputFile_lock.unlock();

    executed = true;
}

bool ITest::wasExecuted() const {
    return executed;
}

std::string ITest::getLogicName() const {
    return logicName;
}

int ITest::getTestIndex() const {
    return testIndex;
}

std::vector<tTestPvals> ITest::getResults() const {
    if(!executed)
        throw RTTException(objectInfo , Strings::TEST_ERR_NO_EXEC_RES);

    return results;
}

std::string ITest::getBatteryStdErr() const {
    if(!executed)
        throw RTTException(objectInfo , Strings::TEST_ERR_NO_EXEC_RES);

    return batteryOutput.getStdErr();
}

std::vector<std::string> ITest::getBatteryErrors() {
    if(!executed)
        throw RTTException(objectInfo , Strings::TEST_ERR_NO_EXEC_RES);

    return batteryOutput.getErrors();
}

std::vector<std::string> ITest::getBatteryWarnings() {
    if(!executed)
        throw RTTException(objectInfo , Strings::TEST_ERR_NO_EXEC_RES);

    return batteryOutput.getWarnings();
}

ITest::ITest(int testIndex, const GlobalContainer & container) {
    cliOptions           = container.getCliOptions();
    toolkitSettings      = container.getToolkitSettings();
    batteryConfiguration = container.getBatteryConfiguration();
    logger               = container.getLogger();
    this->testIndex      = testIndex;
    battery              = cliOptions->getBattery();
    binaryDataPath       = cliOptions->getBinFilePath();
    executablePath       = toolkitSettings->getBinaryBattery(battery);
    logFilePath          = Utils::createLogFileName(container.getCreationTime(),
                                                    toolkitSettings->getLoggerBatteryDir(battery),
                                                    binaryDataPath);

    objectInfo =
            Constants::batteryToString(battery) + " - test " + Utils::itostr(testIndex);

    if(binaryDataPath.empty())
        raiseBugException(Strings::TEST_ERR_NO_BINARY_DATA);

    if(executablePath.empty())
        raiseBugException(Strings::TEST_ERR_NO_EXECUTABLE);
}

} // namespace batteries
} // namespace rtt


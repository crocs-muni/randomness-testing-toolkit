#include "ivariant-batt.h"

#include "rtt/batteries/niststs/variant-sts.h"
#include "rtt/batteries/dieharder/variant-dh.h"
#include "rtt/batteries/testu01/variant-tu01.h"

#include "rtt/batteries/testrunner-batt.h"
/* For writing output into logfile continuosly. */
std::mutex outputFile_mux;

namespace rtt {
namespace batteries {

std::unique_ptr<IVariant> IVariant::getInstance(int testId, uint variantIdx,
                                                const GlobalContainer & cont) {
    std::unique_ptr<IVariant> rval;

    switch(cont.getCliOptions()->getBatteryId()) {
        case Constants::Battery::NIST_STS:
            rval = niststs::Variant::getInstance(testId , variantIdx, cont);
        case Constants::Battery::DIEHARDER:
            rval = dieharder::Variant::getInstance(testId , variantIdx, cont);
        case Constants::Battery::TU01_SMALLCRUSH:
        case Constants::Battery::TU01_CRUSH:
        case Constants::Battery::TU01_BIGCRUSH:
        case Constants::Battery::TU01_RABBIT:
        case Constants::Battery::TU01_ALPHABIT:
        case Constants::Battery::TU01_BLOCK_ALPHABIT:
            rval = testu01::Variant::getInstance(testId , variantIdx , cont);
        default:
            raiseBugException(Strings::ERR_INVALID_BATTERY);
    }
    rval->buildStrings();
}

void IVariant::execute() {
    /* This method is turned into thread.
     * Will deadlock if run without main thread. */
    batteryOutput = TestRunner::executeBinary(
                        logger, objectInfo, executablePath,
                        cliArguments, stdInput);
    batteryOutput.doDetection();
    if(!batteryOutput.getStdErr().empty())
        logger->warn(objectInfo + ": execution of test produced error output.");
    if(!batteryOutput.getErrors().empty())
        logger->warn(objectInfo + ": test output contains errors.");
    if(!batteryOutput.getWarnings().empty())
        logger->warn(objectInfo + ": test output contains warnings.");

    /* Store test output into file. */
    std::unique_lock<std::mutex> outputFile_lock(outputFile_mux);
    Utils::appendStringToFile(logFilePath, batteryOutput.getStdOut());
    Utils::appendStringToFile(logFilePath, batteryOutput.getStdErr());
    outputFile_lock.unlock();

    executed = true;
}

std::string IVariant::getCliArguments() const {
    return cliArguments;
}

std::string IVariant::getStdInput() const {
    return stdInput;
}

std::vector<std::string> IVariant::getUserSettings() const {
    return userSettings;
}

BatteryOutput IVariant::getBatteryOutput() const {
    return batteryOutput;
}

IVariant::IVariant(int testId, uint variantIdx,
                   const GlobalContainer & cont) {
    this->testId        = testId;
    this->variantIdx    = variantIdx;
    logger              = cont.getLogger();
    battId              = cont.getCliOptions()->getBatteryId();
    binaryDataPath      = cont.getCliOptions()->getBinFilePath();
    executablePath      = cont.getToolkitSettings()->getBinaryBattery(battId);
    logFilePath         =
            Utils::createLogFileName(
                cont.getCreationTime(),
                cont.getToolkitSettings()->getLoggerBatteryDir(battId),
                binaryDataPath);
    objectInfo          =
            Constants::batteryToString(battId) +
            " - test " + Utils::itostr(testId) +
            " - variant " + Utils::itostr(variantIdx);

    if(binaryDataPath.empty())
        raiseBugException(Strings::TEST_ERR_NO_BINARY_DATA);

    if(executablePath.empty())
        raiseBugException(Strings::TEST_ERR_NO_EXECUTABLE);
}



} // namespace batteries
} // namespace rtt

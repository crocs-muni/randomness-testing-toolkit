#include "ivariant-batt.h"

#include "rtt/batteries/niststs/variant-sts.h"
#include "rtt/batteries/dieharder/variant-dh.h"
#include "rtt/batteries/testu01/variant-tu01.h"

#include "rtt/batteries/testrunner-batt.h"
/* For writing output into logfile continuosly. */
std::mutex outputFile_mux;

namespace rtt {
namespace batteries {

std::unique_ptr<IVariant> IVariant::getInstance(int testId, std::string testObjInf,
                                                uint variantIdx, const rtt::GlobalContainer &cont) {
    std::unique_ptr<IVariant> rval;

    switch(cont.getRttCliOptions()->getBatteryId()) {
        case Constants::BatteryID::NIST_STS:
            rval = niststs::Variant::getInstance(testId , testObjInf , variantIdx, cont);
            break;
        case Constants::BatteryID::DIEHARDER:
            rval = dieharder::Variant::getInstance(testId , testObjInf , variantIdx, cont);
            break;
        case Constants::BatteryID::TU01_SMALLCRUSH:
        case Constants::BatteryID::TU01_CRUSH:
        case Constants::BatteryID::TU01_BIGCRUSH:
        case Constants::BatteryID::TU01_RABBIT:
        case Constants::BatteryID::TU01_ALPHABIT:
        case Constants::BatteryID::TU01_BLOCK_ALPHABIT:
            rval = testu01::Variant::getInstance(testId , testObjInf , variantIdx , cont);
            break;
        default:
            raiseBugException(Strings::ERR_INVALID_BATTERY);
    }
    rval->buildStrings();
    return rval;
}

void IVariant::execute() {
    /* This method is turned into thread.
     * Will deadlock if run without main thread. */
    uint expExitCode = BatteryArg::getExpectedExitCode(battery.getBatteryId());

    batteryOutput = TestRunner::executeBinary(logger, objectInfo, executablePath,
                                              expExitCode, cliArguments, stdInput);
    analyzeAndStoreBattOut();

    executed = true;
}

std::string IVariant::getCliArguments() const {
    return cliArguments;
}

std::string IVariant::getStdInput() const {
    return stdInput;
}


BatteryOutput IVariant::getBatteryOutput() const {
    if(executed)
        return batteryOutput;

    throw RTTException(objectInfo, Strings::TEST_ERR_NO_EXEC_RES);
}

int IVariant::getTestId() const {
    return testId;
}

std::string IVariant::getObjectInfo() const {
    return objectInfo;
}

std::vector<std::pair<std::string, std::string> > IVariant::getUserSettings() const {
    return userSettings;
}

IVariant::IVariant(int testId, std::string testObjInf, uint variantIdx,
                   const GlobalContainer & cont) {
    this->testId        = testId;
    this->variantIdx    = variantIdx;
    logger              = cont.getLogger();
    battery             = cont.getRttCliOptions()->getBatteryArg();
    binaryDataPath      = cont.getRttCliOptions()->getInputDataPath();
    executablePath      = cont.getToolkitSettings()->getBinaryBattery(battery);
    logFilePath         =
            Utils::getLogFilePath(
                cont.getCreationTime(),
                cont.getToolkitSettings()->getLoggerBatteryDir(battery),
                binaryDataPath,
                "",
                cont.getRttCliOptions()->hasJid() ? cont.getRttCliOptions()->getJid() : 0);
    objectInfo          =
            testObjInf +
            " - variant " + Utils::itostr(variantIdx + 1);

    if(binaryDataPath.empty())
        raiseBugException(Strings::TEST_ERR_NO_BINARY_DATA);

    if(executablePath.empty())
        raiseBugException(Strings::TEST_ERR_NO_EXECUTABLE);
}

void IVariant::analyzeAndStoreBattOut() {
    /* Detect errors and warnings in output */
    batteryOutput.doDetection();
    if(!batteryOutput.getStdErr().empty())
        logger->warn(objectInfo + ": execution of test produced error output.");
    if(!batteryOutput.getErrors().empty())
        logger->warn(objectInfo + ": test output contains errors.");
    if(!batteryOutput.getWarnings().empty())
        logger->warn(objectInfo + ": test output contains warnings.");

    {
        /* Store test output into file */
        std::lock_guard<std::mutex> l (outputFile_mux);
        std::stringstream stdoutStr;
        std::stringstream stderrStr;
        auto filler = "=================================================\n";
        stdoutStr << "=== Standard output of thread " << std::this_thread::get_id() << " ===" << std::endl;
        stderrStr << "=== Error output of thread " << std::this_thread::get_id() << " ===" << std::endl;

        if(!batteryOutput.getStdOut().empty()) {
            Utils::appendStringToFile(logFilePath, filler);
            Utils::appendStringToFile(logFilePath, stdoutStr.str());
            Utils::appendStringToFile(logFilePath, batteryOutput.getStdOut());
        } else {
            logger->warn(objectInfo + ": standard output of test is empty.");
        }

        if(!batteryOutput.getStdErr().empty()) {
            Utils::appendStringToFile(logFilePath, filler);
            Utils::appendStringToFile(logFilePath, stderrStr.str());
            Utils::appendStringToFile(logFilePath, batteryOutput.getStdErr());
        }
    }
}





} // namespace batteries
} // namespace rtt

#include "variant-sts.h"

namespace rtt {
namespace batteries {
namespace niststs {

/* For writing output into logfile continuosly. */
std::mutex outputFile_mux;

std::unique_ptr<Variant> Variant::getInstance(int testId, std::string testObjInf,
                                              uint variantIdx, const GlobalContainer & cont) {
    std::unique_ptr<Variant> v (new Variant(testId, testObjInf, variantIdx, cont));
    auto battConf = cont.getBatteryConfiguration();

    v->streamSize = battConf->getTestVariantParamString(
                        v->battery, testId, variantIdx,
                        Configuration::TAGNAME_STREAM_SIZE);
    if(v->streamSize.empty())
        throw RTTException(v->objectInfo , Strings::TEST_ERR_STREAM_SIZE_NOT_SET);
    v->streamCount = battConf->getTestVariantParamString(
                         v->battery, testId, variantIdx,
                         Configuration::TAGNAME_STREAM_COUNT);
    if(v->streamCount.empty())
        throw RTTException(v->objectInfo , Strings::TEST_ERR_STREAM_COUNT_NOT_SET);
    v->blockLength = battConf->getTestVariantParamString(
                         v->battery, testId, variantIdx,
                         Configuration::TAGNAME_BLOCK_LENGTH);
    v->resultSubDir = std::get<1>(
                          TestConstants::getNistStsTestData(
                              v->battery , v->testId));
    v->adjustableBlockLength = std::get<2>(
                                   TestConstants::getNistStsTestData(
                                       v->battery, testId));

    const auto & cli = cont.getRttCliOptions();
    if (cli->hasResultsPathPrefix()){
        v->resultSubDir = cli->getResultsPathPrefix() + "/" + v->resultSubDir;
    }

    return v;
}

void Variant::execute() {
    /* This method is turned into thread.
     * Will deadlock if run without main thread. */
    uint expExitCode = BatteryArg::getExpectedExitCode(battery.getBatteryId());

    {
        std::lock_guard<std::mutex> l (*testDir_mux);
        /* Cleaning result directory */
        Utils::rmDirFiles(resultSubDir);
        batteryOutput = TestRunner::executeBinary(logger, objectInfo, executablePath,
                                                  expExitCode, cliArguments, stdInput);
        readNistStsOutFiles();
    }

    analyzeAndStoreBattOut();

    executed = true;
}

void Variant::setTestDir_mux(std::mutex * value) {
    testDir_mux = value;
}

std::vector<std::string> Variant::getPValueFiles() const {
    return pValueFiles;
}

void Variant::buildStrings() {
    /* Building cli arguments */
    std::stringstream arguments;
    /* -fast is used with faster version of NIST STS */
    //arguments << "assess " << streamSize << " -fast";
    arguments << "niststs " << streamSize << " -fast";
    cliArguments = arguments.str();

    /* Building standard input */
    /* 'Beautiful' creation of input that will be sent to */
    /* sts over pipe, so that it will have proper settings. */
    std::stringstream stdIn;
    /* Choosing input file generator */
    stdIn << "0 ";
    /* Choosing file */
    stdIn << binaryDataPath << " ";
    /* Execute only one test */
    stdIn << "0 ";
    /* Specify which test will be executed */
    std::string zeroArr(15, '0');
    zeroArr[testId - 1] = '1';
    stdIn << zeroArr << " ";
    /* Setting blocksize of test. If blocksize is
     * not adjustable this is skipped. */
    if(adjustableBlockLength) {
        if(blockLength.empty()) {
            /* Not set, skipping setting */
            stdIn << "0 ";
        } else {
            /* Adjusting blocksize. Test Id in this
             * setting is always 1 since only one test
             * is executed at a time. */
            stdIn << "1 ";
            /* Zero is entered to end parameter adjusting */
            stdIn << blockLength << " 0 ";
        }
    }
    /* Setting stream count */
    stdIn << streamCount << " ";
    /* Setting type of file to binary */
    stdIn << "1" << std::endl;
    /* End of input. */
    stdInput = stdIn.str();

    /* Building variation user settings */
    userSettings.push_back({"Stream size", streamSize});
    userSettings.push_back({"Stream count", streamCount});
    if(adjustableBlockLength && !blockLength.empty())
        userSettings.push_back({"Block length", blockLength});
}

void Variant::readNistStsOutFiles() {
    try {
        auto testLog = Utils::readFileToString(resultSubDir + "stats.txt");
        batteryOutput.appendStdOut(testLog);

        if(Utils::fileExist(resultSubDir + "data1.txt")) {
            /* Multiple data<n>.txt files with p values */
            std::string dataFileName;
            for(uint i = 1 ; ; ++i) {
                dataFileName = resultSubDir + "data";
                dataFileName.append(Utils::itostr(i));
                dataFileName.append(".txt");
                if(Utils::fileExist(dataFileName)) {
                    /* Okay read it. */
                    pValueFiles.push_back(
                                Utils::readFileToString(
                                    dataFileName));
                } else {
                    /* No more files to read */
                    break;
                }
            }
        } else {
            /* Only one result file with p values */
            pValueFiles.push_back(
                        Utils::readFileToString(
                            resultSubDir + "results.txt"));
        }
    } catch (std::runtime_error ex) {
        logger->warn(objectInfo + Strings::TEST_ERR_EXCEPTION_DURING_THREAD + ex.what());
    }
}

} // namespace niststs
} // namespace batteries
} // namespace rtt

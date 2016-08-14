#include "variant-sts.h"

namespace rtt {
namespace batteries {
namespace niststs {

std::unique_ptr<Variant> Variant::getInstance(int testId, uint variantIdx,
                                              const GlobalContainer & cont) {
    std::unique_ptr<Variant> v (new Variant());
    auto battConf = cont.getBatteryConfiguration();
    auto cliOpt = cont.getCliOptions();
    v->testId = testId;
    v->batt = cliOpt->getBattery();

    v->objectInfo =
            Constants::batteryToString(v->batt) +
            " - test " + Utils::itostr(v->testId) +
            " - variant " + Utils::itostr(variantIdx);

    v->binaryDataPath = cliOpt->getBinFilePath();

    v->streamSize = battConf->getTestVariantParamString(
                        v->batt, testId, variantIdx,
                        Configuration::TAGNAME_STREAM_SIZE);
    if(v->streamSize.empty())
        throw RTTException(v->objectInfo , Strings::TEST_ERR_STREAM_SIZE_NOT_SET);
    v->streamCount = battConf->getTestVariantParamString(
                         v->batt, testId, variantIdx,
                         Configuration::TAGNAME_STREAM_COUNT);
    if(v->streamCount.empty())
        throw RTTException(v->objectInfo , Strings::TEST_ERR_STREAM_COUNT_NOT_SET);
    v->blockLength = battConf->getTestVariantParamString(
                         v->batt, testId, variantIdx,
                         Configuration::TAGNAME_BLOCK_LENGTH);
    v->adjustableBlockLength =
            std::get<3>(TestConstants::getNistStsTestData(v->batt, testId));

    v->buildStrings();
    return v;
}

void Variant::buildStrings() {
    /* Building cli arguments */
    std::stringstream arguments;
    /* -fast is used with faster version of NIST STS */
    arguments << "assess " << streamSize << " -fast";
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
    std::stringstream sett;
    sett << "Stream size: " << streamSize << std::endl;
    sett << "Stream count: " << streamCount << std::endl;
    if(adjustableBlockLength && !blockLength.empty())
        sett << "Block length: " << blockLength;
    userSettings = Utils::split(sett.str() , '\n');
}

std::vector<std::string> Variant::getUserSettings() const {
    return userSettings;
}

std::string Variant::getStdInput() const {
    return stdInput;
}

std::string Variant::getCliArguments() const {
    return cliArguments;
}

} // namespace niststs
} // namespace batteries
} // namespace rtt

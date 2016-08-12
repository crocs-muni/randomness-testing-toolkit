#include "variant-dh.h"

namespace rtt {
namespace batteries {
namespace dieharder {

const int Test::OPTION_HEADER_FLAG      = 66047;
const int Test::OPTION_FILE_GENERATOR   = 201;

std::unique_ptr<Variant> Variant::getInstance(int testId, uint variantIndex,
                                              const GlobalContainer & cont) {
    std::shared_ptr<Variant> v (new Variant());
    auto battConf = cont.getBatteryConfiguration();
    auto cliOpt = cont.getCliOptions();
    v->testId = testId;
    v->batt = cliOpt->getBattery();

    v->objectInfo =
            Constants::batteryToString(v->batt) +
            " - test " + Utils::itostr(v->testId) +
            " - variant " + Utils::itostr(variantIndex);

    v->binaryDataPath = cliOpt->getBinFilePath();

    v->pSampleCount = battConf->getTestVariantsParamInt(
                          v->batt, v->testId, variantIndex,
                          Configuration::TAGNAME_PSAMPLES);
    if(v->pSampleCount == Configuration::VALUE_INT_NOT_SET)
        throw RTTException(v->objectInfo , Strings::TEST_ERR_PSAMPLES_NOT_SET);

    std::string arguments = battConf->getTestVariantParamString(
                                v->batt, v->testId, variantIndex,
                                Configuration::TAGNAME_ARGUMENTS);
    auto vArguments = Utils::split(arguments , ' ');
    if(vArguments.size() % 2 != 0)
        throw RTTException(t->objectInfo ,
                           Strings::TEST_ERR_ARGS_BAD_FORMAT_OPT_WO_VAL);
    for(size_t i = 0 ; i < vArguments.size() ; i += 2) {
        try {
            auto sett = Setting::getInstance(vArguments.at(i), vArguments.at(i + 1));
            v->settings.push_back(std::move(sett));
        } catch(std::runtime_error ex) {
            throw RTTException(t->objectInfo , ex.what());
        }
    }
}

std::string Variant::getStdInput() const {
    return stdInput;
}

std::string Variant::getCliArguments() const {
    return cliArguments;
}

std::vector<std::string> Variant::getUserSettings() const {
    return userSettings;
}

void Variant::buildStrings() {
    /* Building cli arguments */
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
    cliArguments = arguments.str();

    /* Building standard input */
    //no input

    /* Building variation user settings */
    std::stringstream parameters;
    parameters << "p-sample count: " << pSampleCount << std::endl;
    for(const Setting & setting : settings)
        parameters << setting.getLogicName() << ": "
                   << setting.getArgumentValue() << std::endl;
    userSettings = Utils::split(parameters.str() , '\n');
}



} // namespace dieharder
} // namespace batteries
} // namespace rtt

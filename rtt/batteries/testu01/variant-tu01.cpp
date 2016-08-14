#include "variant-tu01.h"

namespace rtt {
namespace batteries {
namespace testu01 {

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

    v->paramNames =
            std::get<1>(TestConstants::getTu01TestData(v->batt , v->testId));
    v->statisticNames =
            std::get<2>(TestConstants::getTu01TestData(v->batt , v->testId));

   /* Repetitions - mandatory */
    v->repetitions = battConf->getTestVariantsParamInt(
                         v->batt, v->testId, variantIdx,
                         Configuration::TAGNAME_REPETITIONS);
    if(v->repetitions == Configuration::VALUE_INT_NOT_SET)
        throw RTTException(v->objectInfo , Strings::TEST_ERR_REPS_NOT_SET);

    /* Getting params - only for Crush batteries - optional */
    if(Constants::isInTU01CrushFamily(v->batt)) {
        tParam tmp;
        tStringStringMap actualParams =
                battConf->getTestVariantParamMap(v->batt, v->testId, variantIdx,
                                                 Configuration::TAGNAME_PARAMS);
        if(!actualParams.empty()) {
            for(const auto & paramName : v->paramNames) {
                if(actualParams.count(paramName) == 1) {
                    tmp.first = paramName;
                    tmp.second = actualParams.at(paramName);
                } else {
                    throw RTTException(v->objectInfo,
                                       Strings::TEST_ERR_PARAM_INCOMPLETE);
                }
                v->params.push_back(tmp);
            }
        }
    }
    /* Getting nb - Rabbit and (Block) Alphabit - mandatory */
    if(Constants::isInTU01BitFamily(v->batt)) {
        v->bit_nb = battConf->getTestVariantParamString(
                        v->batt, v->testId, variantIdx,
                        Configuration::TAGNAME_BIT_NB);
        if(v->bit_nb.empty())
            throw RTTException(v->objectInfo , Strings::TEST_ERR_BITNB_NOT_SET);
    }
    /* Getting r s - (Block) Alphabit - mandatory */
    if(Constants::isinTU01AlphabitFamily(v->batt)) {
        v->bit_r = battConf->getTestVariantParamString(
                       v->batt, v->testId, variantIdx,
                       Configuration::TAGNAME_BIT_R);
        if(v->bit_r.empty())
            throw RTTException(v->objectInfo , Strings::TEST_ERR_BITR_NOT_SET);
        v->bit_s = battConf->getTestVariantParamString(
                       v->batt, v->testId, variantIdx,
                       Configuration::TAGNAME_BIT_S);
        if(v->bit_s.empty())
            throw RTTException(v->objectInfo , Strings::TEST_ERR_BITS_NOT_SET);
    }
    /* Getting w - Block Alphabit - optional */
    if(v->batt == Constants::Battery::TU01_BLOCK_ALPHABIT) {
        v->bit_w = battConf->getTestVariantParamString(
                       v->batt, v->testId, variantIdx,
                       Configuration::TAGNAME_BIT_W);
    }

    buildStrings();

    return v;
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
    /* Building CLI arguments */
    std::stringstream arguments;
    arguments << "testu01 ";
    /* Setting battery mode */
    arguments << "-m ";
    switch(batt) {
    case Constants::Battery::TU01_SMALLCRUSH:
        arguments << "small_crush "; break;
    case Constants::Battery::TU01_CRUSH:
        arguments << "crush "; break;
    case Constants::Battery::TU01_BIGCRUSH:
        arguments << "big_crush "; break;
    case Constants::Battery::TU01_RABBIT:
        arguments << "rabbit "; break;
    case Constants::Battery::TU01_ALPHABIT:
        arguments << "alphabit "; break;
    case Constants::Battery::TU01_BLOCK_ALPHABIT:
        arguments << "block_alphabit "; break;
    default:
        raiseBugException(Strings::ERR_INVALID_BATTERY);
    }
    /* Test number option */
    arguments << "-t " << testId << " ";
    /* Input file option */
    arguments << "-i " << binaryDataPath << " ";
    /* Repetitions option */
    if(repetitions != 1)
        arguments << "-r " << repetitions << " ";
    if(params.size() > 0) {
        arguments << "--params ";
        for(const auto & i : params)
            arguments << i.second << " ";
    }
    /* nb */
    if(!bit_nb.empty())
        arguments << "--bit_nb " << bit_nb << " ";
    /* r */
    if(!bit_r.empty())
        arguments << "--bit_r " << bit_r << " ";
    /* s */
    if(!bit_s.empty())
        arguments << "--bit_s " << bit_s << " ";
    /* w */
    if(!bit_w.empty())
        arguments << "--bit_w " << bit_w;
    cliArguments = arguments.str();

    /* Building standard input */
    //no input

    /* Building variation user settings */
    std::stringstream userSett;
    userSett << "Repetitions: " << repetitions << std::endl;
    if(Constants::isInTU01BitFamily(batt)) {
        userSett << "Bit NB: " << bit_nb << std::endl;
    }
    if(Constants::isinTU01AlphabitFamily(batt)) {
        userSett << "Bit R: " << bit_r << std::endl;
        userSett << "Bit S: " << bit_s << std::endl;
    }
    if(!bit_w.empty() && batt == Constants::Battery::TU01_BLOCK_ALPHABIT) {
        userSett << "Bit W: " << bit_w << std::endl;
    }
    if(!params.empty() && Constants::isInTU01CrushFamily(batt)) {
        for(const tParam & param : params) {
            userSett << param.first << " = " << param.second << std::endl;
        }
    }
    userSettings = Utils::split(userSett.str() , '\n');
}

} // namespace testu01
} // namespace batteries
} // namespace rtt

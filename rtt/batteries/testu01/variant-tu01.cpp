#include "variant-tu01.h"

namespace rtt {
namespace batteries {
namespace testu01 {

std::unique_ptr<Variant> Variant::getInstance(int testId, std::string testObjInf,
                                              uint variantIdx, const GlobalContainer & cont) {
    std::unique_ptr<Variant> v (new Variant(testId, testObjInf, variantIdx, cont));
    auto battConf = cont.getBatteryConfiguration();

    v->settableParamNames =
            std::get<1>(TestConstants::getTu01TestData(
                            v->battery , v->testId));
    v->extractableParamNames =
            std::get<2>(TestConstants::getTu01TestData(
                            v->battery , v->testId));
    v->statisticNames =
            std::get<3>(TestConstants::getTu01TestData(
                            v->battery , v->testId));

   /* Repetitions - mandatory */
    v->repetitions = battConf->getTestVariantParamInt(
                         v->battery, v->testId, variantIdx,
                         Configuration::TAGNAME_REPETITIONS);
    if(v->repetitions == Configuration::VALUE_INT_NOT_SET)
        throw RTTException(v->objectInfo , Strings::TEST_ERR_REPS_NOT_SET);

    /* Getting params - only for Crush batteries - optional */
    if(v->battery.isInTU01CrushFamily()) {
        tParam tmp;
        tStringStringMap actualParams =
                battConf->getTestVariantParamMap(v->battery, v->testId, variantIdx,
                                                 Configuration::TAGNAME_PARAMS);
        if(!actualParams.empty()) {
            for(const auto & paramName : v->settableParamNames) {
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
    if(v->battery.isInTU01BitFamily()) {
        v->bit_nb = battConf->getTestVariantParamString(
                        v->battery, v->testId, variantIdx,
                        Configuration::TAGNAME_BIT_NB);
        if(v->bit_nb.empty())
            throw RTTException(v->objectInfo , Strings::TEST_ERR_BITNB_NOT_SET);
    }
    /* Getting r s - (Block) Alphabit - mandatory */
    if(v->battery.isInTU01AlphabitFamily()) {
        v->bit_r = battConf->getTestVariantParamString(
                       v->battery, v->testId, variantIdx,
                       Configuration::TAGNAME_BIT_R);
        if(v->bit_r.empty())
            throw RTTException(v->objectInfo , Strings::TEST_ERR_BITR_NOT_SET);
        v->bit_s = battConf->getTestVariantParamString(
                       v->battery, v->testId, variantIdx,
                       Configuration::TAGNAME_BIT_S);
        if(v->bit_s.empty())
            throw RTTException(v->objectInfo , Strings::TEST_ERR_BITS_NOT_SET);
    }
    /* Getting w - Block Alphabit - optional */
    if(v->battery.getBatteryId() == Constants::BatteryID::TU01_BLOCK_ALPHABIT) {
        v->bit_w = battConf->getTestVariantParamString(
                       v->battery, v->testId, variantIdx,
                       Configuration::TAGNAME_BIT_W);
    }

    return v;
}

std::vector<std::string> Variant::getStatisticNames() const {
    return statisticNames;
}

std::vector<std::string> Variant::getExtractableParamNames() const {
    return extractableParamNames;
}

void Variant::buildStrings() {
    /* Building CLI arguments */
    std::stringstream arguments;
    arguments << "testu01 ";
    /* Setting battery mode */
    arguments << "-m ";
    switch(battery.getBatteryId()) {
    case Constants::BatteryID::TU01_SMALLCRUSH:
        arguments << "small_crush "; break;
    case Constants::BatteryID::TU01_CRUSH:
        arguments << "crush "; break;
    case Constants::BatteryID::TU01_BIGCRUSH:
        arguments << "big_crush "; break;
    case Constants::BatteryID::TU01_RABBIT:
        arguments << "rabbit "; break;
    case Constants::BatteryID::TU01_ALPHABIT:
        arguments << "alphabit "; break;
    case Constants::BatteryID::TU01_BLOCK_ALPHABIT:
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
    userSettings.push_back({"Repetitions", Utils::itostr(repetitions)});
    if(battery.isInTU01BitFamily()) {
        userSettings.push_back({"Bit NB", bit_nb});
    }
    if(battery.isInTU01AlphabitFamily()) {
        userSettings.push_back({"Bit R", bit_r});
        userSettings.push_back({"Bit S", bit_s});
    }
    if(!bit_w.empty() && battery.getBatteryId() == Constants::BatteryID::TU01_BLOCK_ALPHABIT) {
        userSettings.push_back({"Bit W", bit_w});
    }
    if(!params.empty() && battery.isInTU01CrushFamily()) {
        for(const tParam & param : params) {
            userSettings.push_back({param.first, param.second});
        }
    }
    //userSettings = Utils::split(userSett.str() , '\n');
}

} // namespace testu01
} // namespace batteries
} // namespace rtt

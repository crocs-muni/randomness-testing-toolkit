#include "configuration-batt.h"

namespace rtt {
namespace batteries {

const std::string Configuration::TAGNAME_ROOT               = "randomness-testing-toolkit";
const std::string Configuration::TAGNAME_DIEHARDER_SETT     = "dieharder-settings";
const std::string Configuration::TAGNAME_NISTSTS_SETT       = "nist-sts-settings";
const std::string Configuration::TAGNAME_SCRUSH_SETT        = "tu01-smallcrush-settings";
const std::string Configuration::TAGNAME_CRUSH_SETT         = "tu01-crush-settings";
const std::string Configuration::TAGNAME_BCRUSH_SETT        = "tu01-bigcrush-settings";
const std::string Configuration::TAGNAME_RABBIT_SETT        = "tu01-rabbit-settings";
const std::string Configuration::TAGNAME_ALPHABIT_SETT      = "tu01-alphabit-settings";
const std::string Configuration::TAGNAME_BLALPHABIT_SETT    = "tu01-blockalphabit-settings";
const std::string Configuration::TAGNAME_RTT_SETT           = "rtt-settings";
const std::string Configuration::TAGNAME_RTT_SETT_SKIP_PVALUE_STORAGE = "skip-pvalue-storage";
const std::string Configuration::TAGNAME_DEFAULTS           = "defaults";
const std::string Configuration::TAGNAME_TEST_SPECIFIC_SETT = "test-specific-settings";
const std::string Configuration::TAGNAME_DEFAULT_TESTS      = "test-ids";
const std::string Configuration::TAGNAME_TEST_ID            = "test-id";
const std::string Configuration::TAGNAME_VARIANTS           = "variants";
const std::string Configuration::TAGNAME_ARGUMENTS          = "arguments";
const std::string Configuration::TAGNAME_PSAMPLES           = "psamples";
const std::string Configuration::TAGNAME_STREAM_SIZE        = "stream-size";
const std::string Configuration::TAGNAME_STREAM_COUNT       = "stream-count";
const std::string Configuration::TAGNAME_BLOCK_LENGTH       = "block-length";
const std::string Configuration::TAGNAME_REPETITIONS        = "repetitions";
const std::string Configuration::TAGNAME_BIT_NB             = "bit-nb";
const std::string Configuration::TAGNAME_BIT_R              = "bit-r";
const std::string Configuration::TAGNAME_BIT_S              = "bit-s";
const std::string Configuration::TAGNAME_BIT_W              = "bit-w";
const std::string Configuration::TAGNAME_PARAMS             = "parameters";

const std::string Configuration::objectInfo = "Battery Configuration";

Configuration Configuration::getInstance(const std::string & configFileName) {
    json root;
    Configuration conf;

    try {
        root = json::parse(Utils::readFileToString(configFileName));
    } catch (std::exception & ex) {
        throw RTTException(objectInfo,
                           "error during JSON parsing (" + configFileName +
                           ") - " + (std::string)ex.what());
    }

    if(root.count(TAGNAME_ROOT) != 1)
        throw RTTException(objectInfo,
                           "root tag is missing in file - " + TAGNAME_ROOT);

    root = root.at(TAGNAME_ROOT);
    conf.configRoot = root;

    return conf;
}



uint Configuration::getTestVariantsCount(const BatteryArg & battery, int testId) {
    json testNode = findTestSpecificNode(configRoot , battery , testId);
    if(testNode.count(TAGNAME_VARIANTS) == 1)
        return testNode.at(TAGNAME_VARIANTS).size();

    return 0;
}

int Configuration::getTestVariantParamInt(const BatteryArg & battery,
                                           int testId, uint variantIdx,
                                           const std::string & paramName) {
    int rval = VALUE_INT_NOT_SET;

    /* Default value if any */
    const json & nDefaults = findBatteryDefaultSettNode(configRoot , battery);
    if(nDefaults.count(paramName) == 1)
        rval = nDefaults.at(paramName);

    /* Test specific value if any */
    const json & nTest = findTestSpecificNode(configRoot , battery , testId);
    if(nTest.count(paramName) == 1)
        rval = nTest.at(paramName);

    /* Variation specific value if any */
    if(nTest.count(TAGNAME_VARIANTS) == 1) {
        const json & nVariants = nTest.at(TAGNAME_VARIANTS);
        if(nVariants.size() > variantIdx) {
            if(nVariants.at(variantIdx).count(paramName) == 1)
                rval = nVariants.at(variantIdx).at(paramName);
        }
    }

    return rval;
}

std::string Configuration::getTestVariantParamString(const BatteryArg & battery,
                                                     int testId, uint variantIdx,
                                                     const std::string & paramName) {
    std::string rval;

    /* Default value if any */
    const json & nDefaults = findBatteryDefaultSettNode(configRoot , battery);
    if(nDefaults.count(paramName) == 1)
        rval = nDefaults.at(paramName);

    /* Test specific value if any */
    const json & nTest = findTestSpecificNode(configRoot , battery , testId);
    if(nTest.count(paramName) == 1)
        rval = nTest.at(paramName);

    /* Variation specific value if any */
    if(nTest.count(TAGNAME_VARIANTS) == 1) {
        const json & nVariants = nTest.at(TAGNAME_VARIANTS);
        if(nVariants.size() > variantIdx) {
            if(nVariants.at(variantIdx).count(paramName) == 1)
                rval = nVariants.at(variantIdx).at(paramName);
        }
    }

    return rval;
}

tStringStringMap Configuration::getTestVariantParamMap(const BatteryArg & battery,
                                                       int testId, uint variantIdx,
                                                       const std::string & paramName) {
    json nParams = json::object();

    /* Default value if any */
    const json & nDefaults = findBatteryDefaultSettNode(configRoot , battery);
    if(nDefaults.count(paramName) == 1)
        nParams = nDefaults.at(paramName);

    /* Test specific value if any */
    const json & nTest = findTestSpecificNode(configRoot , battery , testId);
    if(nTest.count(paramName) == 1)
        nParams = nTest.at(paramName);

    /* Variation specific value if any */
    if(nTest.count(TAGNAME_VARIANTS) == 1) {
        const json & nVariants = nTest.at(TAGNAME_VARIANTS);
        if(nVariants.size() > variantIdx) {
            if(nVariants.at(variantIdx).count(paramName) == 1)
                nParams = nVariants.at(variantIdx).at(paramName);
        }
    }

    if(nParams.empty())
        return {};

    /* Convert json object into map */
    tStringStringMap rval;
    for(json::iterator it = nParams.begin() ; it != nParams.end() ; ++it)
        rval[it.key()] = it.value();

    return rval;
}

std::vector<int> Configuration::getBatteryDefaultTests(const BatteryArg & battery) {
    json nDefaults = findBatteryDefaultSettNode(configRoot , battery);
    if(nDefaults.count(TAGNAME_DEFAULT_TESTS) == 1)
        return parseTestConstants(
                    nDefaults.at(TAGNAME_DEFAULT_TESTS).get<json::array_t>()
                );

    return {};
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

json Configuration::findBatterySettingsNode(const json & rootNode,
                                            const BatteryArg & battery) {
    if(rootNode.empty())
        raiseBugException("empty json node");

    switch(battery.getBatteryId()) {
        case Constants::BatteryID::NIST_STS:
            if(rootNode.count(TAGNAME_NISTSTS_SETT) == 1)
                return rootNode.at(TAGNAME_NISTSTS_SETT);
            break;
        case Constants::BatteryID::DIEHARDER:
            if(rootNode.count(TAGNAME_DIEHARDER_SETT) == 1)
                return rootNode.at(TAGNAME_DIEHARDER_SETT);
            break;
        case Constants::BatteryID::TU01_SMALLCRUSH:
            if(rootNode.count(TAGNAME_SCRUSH_SETT) == 1)
                return rootNode.at(TAGNAME_SCRUSH_SETT);
            break;
        case Constants::BatteryID::TU01_CRUSH:
            if(rootNode.count(TAGNAME_CRUSH_SETT) == 1)
                return rootNode.at(TAGNAME_CRUSH_SETT);
            break;
        case Constants::BatteryID::TU01_BIGCRUSH:
            if(rootNode.count(TAGNAME_BCRUSH_SETT) == 1)
                return rootNode.at(TAGNAME_BCRUSH_SETT);
            break;
        case Constants::BatteryID::TU01_RABBIT:
            if(rootNode.count(TAGNAME_RABBIT_SETT) == 1)
                return rootNode.at(TAGNAME_RABBIT_SETT);
            break;
        case Constants::BatteryID::TU01_ALPHABIT:
            if(rootNode.count(TAGNAME_ALPHABIT_SETT) == 1)
                return rootNode.at(TAGNAME_ALPHABIT_SETT);
            break;
        case Constants::BatteryID::TU01_BLOCK_ALPHABIT:
            if(rootNode.count(TAGNAME_BLALPHABIT_SETT) == 1)
                return rootNode.at(TAGNAME_BLALPHABIT_SETT);
            break;
        default:
            raiseBugException("invalid battery");
    }
    return {};
}

json Configuration::findRttSettingsNode() const {
    if(configRoot.empty())
        raiseBugException("empty json node");

    if(configRoot.count(TAGNAME_RTT_SETT) == 1)
        return configRoot.at(TAGNAME_RTT_SETT);
    return {};
}

bool Configuration::hasSkipPvalueStorage() const {
    auto js = findRttSettingsNode();
    return js.count(TAGNAME_RTT_SETT_SKIP_PVALUE_STORAGE) == 1
           && js.at(TAGNAME_RTT_SETT_SKIP_PVALUE_STORAGE).is_number();
}

bool Configuration::skipPvalueStorage() const {
    auto js = findRttSettingsNode();
    return js.count(TAGNAME_RTT_SETT_SKIP_PVALUE_STORAGE) == 1
        && js.at(TAGNAME_RTT_SETT_SKIP_PVALUE_STORAGE).is_number()
        && js.at(TAGNAME_RTT_SETT_SKIP_PVALUE_STORAGE).get<int>() > 0;
}

json Configuration::findBatteryDefaultSettNode(const json & rootNode,
                                               const BatteryArg & battery) {
    if(rootNode.empty())
        raiseBugException("empty json node");

    json rval = findBatterySettingsNode(rootNode , battery);
    if(rval.empty())
        return {};

    if(rval.count(TAGNAME_DEFAULTS) == 1)
        return rval.at(TAGNAME_DEFAULTS);

    return {};
}

json Configuration::findBatteryTestSettNode(const json & rootNode,
                                            const BatteryArg & battery) {
    if(rootNode.empty())
        raiseBugException("empty json node");

    json rval = findBatterySettingsNode(rootNode , battery);
    if(rval.empty())
        return {};

    if(rval.count(TAGNAME_TEST_SPECIFIC_SETT) == 1)
        return rval.at(TAGNAME_TEST_SPECIFIC_SETT);

    return {};
}

json Configuration::findTestSpecificNode(const json & rootNode, const BatteryArg & battery , int testId) {
    if(rootNode.empty())
        raiseBugException("empty json node");

    json testSpecificSettNode = findBatteryTestSettNode(rootNode , battery);
    if(testSpecificSettNode.empty())
        return {};

    for(const json & el : testSpecificSettNode) {
        if(el.count(TAGNAME_TEST_ID) == 1 && el.at(TAGNAME_TEST_ID).is_number() && el.at(TAGNAME_TEST_ID).get<int>() == testId)
            return el;
    }
    return {};
}

std::vector<int> Configuration::parseTestConstants(json::array_t node) {
    if(node.empty())
        return {};

    std::vector<int> rval;

    for(const std::string & el : node) {
        if(std::count(el.begin() , el.end() , '-') == 0) {
            /* Single number */
            rval.push_back(Utils::strtoi(el));
        } else if(std::count(el.begin() , el.end() , '-') == 1) {
            /* Range of numbers */
            auto splitted = Utils::split(el , '-');
            int bot = Utils::strtoi(splitted.at(0));
            int top = Utils::strtoi(splitted.at(1));
            for( ; bot <= top ; ++bot)
                rval.push_back(bot);
        } else {
            /* Multiple dashes, wrong format */
            throw RTTException(objectInfo ,
                               "invalid range value: " + el);
        }
    }
    std::sort(rval.begin() , rval.end());
    rval.erase(std::unique(rval.begin() , rval.end()) , rval.end());
    return rval;
}

} // namespace batteries
} // namespace rtt

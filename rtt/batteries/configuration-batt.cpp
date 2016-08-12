#include "configuration-batt.h"

namespace rtt {
namespace batteries {

const std::string Configuration::TAGNAME_ROOT               = "randomness-testing-toolkit";
const std::string Configuration::TAGNAME_DIEHARDER_SETT     = "dieharder-settings";
const std::string Configuration::TAGNAME_NISTSTS_SETT       = "nist-sts-settings";
const std::string Configuration::TAGNAME_TESTU01_SETT       = "testu01-settings";
const std::string Configuration::TAGNAME_SCRUSH_BATT        = "small-crush";
const std::string Configuration::TAGNAME_CRUSH_BATT         = "crush";
const std::string Configuration::TAGNAME_BCRUSH_BATT        = "big-crush";
const std::string Configuration::TAGNAME_RABBIT_BATT        = "rabbit";
const std::string Configuration::TAGNAME_ALPHABIT_BATT      = "alphabit";
const std::string Configuration::TAGNAME_BLALPHABIT_BATT    = "block-alphabit";
const std::string Configuration::TAGNAME_DEFAULTS           = "defaults";
const std::string Configuration::TAGNAME_TEST_SPECIFIC_SETT = "test-specific-settings";
const std::string Configuration::TAGNAME_DEFAULT_TESTS      = "test-ids";
const std::string Configuration::TAGNAME_TEST_ID            = "test-id";
const std::string Configuration::TAGNAME_VARIATIONS         = "variants";
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
    json root = json::parse(Utils::readFileToString(configFileName));

    Configuration conf;

    try {
        root = root.at(TAGNAME_ROOT);
        conf.configRoot = root;
    } catch (std::runtime_error ex) {
        throw RTTException(objectInfo,
                           "error during JSON processing - " + (std::string)ex.what());
    } catch (std::out_of_range ex) {
        throw RTTException(objectInfo,
                           "missing tag in JSON - " + (std::string)ex.what());
    } catch (std::domain_error ex) {
        throw RTTException(objectInfo,
                           "conversion error in JSON - " + (std::string)ex.what());
    }

    return conf;
}



uint Configuration::getTestVariantsCount(Constants::Battery batt, int testId) {
    json testNode = findTestSpecificNode(configRoot , batt , testId);
    if(testNode.count(TAGNAME_VARIATIONS) == 1)
        return testNode.at(TAGNAME_VARIATIONS).size();

    return 0;
}

int Configuration::getTestVariantsParamInt(Constants::Battery batt,
                                           int testId, uint variantIndex,
                                           const std::string & paramName) {
    int rval = VALUE_INT_NOT_SET;

    /* Default value if any */
    const json & nDefaults = findBatteryDefaultSettNode(configRoot , batt);
    if(nDefaults.count(paramName) == 1)
        rval = nDefaults.at(paramName);

    /* Test specific value if any */
    const json & nTest = findTestSpecificNode(configRoot , batt , testId);
    if(nTest.count(paramName) == 1)
        rval = nTest.at(paramName);

    /* Variation specific value if any */
    if(nTest.count(TAGNAME_VARIATIONS) == 1) {
        const json & nVariations = nTest.at(TAGNAME_VARIATIONS);
        if(nVariations.size() > variantIndex) {
            if(nVariations.at(variantIndex).count(paramName) == 1)
                rval = nVariations.at(variantIndex).at(paramName);
        }
    }

    return rval;
}

std::string Configuration::getTestVariantParamString(Constants::Battery batt,
                                                     int testId, uint variantIndex,
                                                     const std::string & paramName) {
    std::string rval;

    /* Default value if any */
    const json & nDefaults = findBatteryDefaultSettNode(configRoot , batt);
    if(nDefaults.count(paramName) == 1)
        rval = nDefaults.at(paramName);

    /* Test specific value if any */
    const json & nTest = findTestSpecificNode(configRoot , batt , testId);
    if(nTest.count(paramName) == 1)
        rval = nTest.at(paramName);

    /* Variation specific value if any */
    if(nTest.count(TAGNAME_VARIATIONS) == 1) {
        const json & nVariations = nTest.at(TAGNAME_VARIATIONS);
        if(nVariations.size() > variantIndex) {
            if(nVariations.at(variantIndex).count(paramName) == 1)
                rval = nVariations.at(variantIndex).at(paramName);
        }
    }

    return rval;
}

tStringStringMap Configuration::getTestVariantParamMap(Constants::Battery batt,
                                                       int testId, uint variantIndex,
                                                       const std::string & paramName) {
    json nParams = json::object();

    /* Default value if any */
    const json & nDefaults = findBatteryDefaultSettNode(configRoot , batt);
    if(nDefaults.count(paramName) == 1)
        nParams = nDefaults.at(paramName);

    /* Test specific value if any */
    const json & nTest = findTestSpecificNode(configRoot , batt , testId);
    if(nTest.count(paramName) == 1)
        nParams = nTest.at(paramName);

    /* Variation specific value if any */
    if(nTest.count(TAGNAME_VARIATIONS) == 1) {
        const json & nVariations = nTest.at(TAGNAME_VARIATIONS);
        if(nVariations.size() > variantIndex) {
            if(nVariations.at(variantIndex).count(paramName) == 1)
                nParams = nVariations.at(variantIndex).at(paramName);
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

std::vector<int> Configuration::getBatteryDefaultTests(Constants::Battery battery) {
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
                                            Constants::Battery batt) {
    if(rootNode.empty())
        raiseBugException("empty json node");

    switch(batt) {
        case Constants::Battery::NIST_STS:
            if(rootNode.count(TAGNAME_NISTSTS_SETT) == 1)
                return rootNode.at(TAGNAME_NISTSTS_SETT);
            break;
        case Constants::Battery::DIEHARDER:
            if(rootNode.count(TAGNAME_DIEHARDER_SETT) == 1)
                return rootNode.at(TAGNAME_DIEHARDER_SETT);
            break;
        case Constants::Battery::TU01_SMALLCRUSH:
        case Constants::Battery::TU01_CRUSH:
        case Constants::Battery::TU01_BIGCRUSH:
        case Constants::Battery::TU01_RABBIT:
        case Constants::Battery::TU01_ALPHABIT:
        case Constants::Battery::TU01_BLOCK_ALPHABIT:
            if(rootNode.count(TAGNAME_TESTU01_SETT) == 1)
                return rootNode.at(TAGNAME_TESTU01_SETT);
            break;
        default:
            raiseBugException("invalid battery");
    }
    return {};
}

json Configuration::findBatteryDefaultSettNode(const json & rootNode,
                                               Constants::Battery batt) {
    if(rootNode.empty())
        raiseBugException("empty json node");

    json rval = findBatterySettingsNode(rootNode , batt);
    if(rval.empty())
        return {};

    switch(batt) {
        case Constants::Battery::NIST_STS:
        case Constants::Battery::DIEHARDER:
            if(rval.count(TAGNAME_DEFAULTS) == 1)
                return rval.at(TAGNAME_DEFAULTS);
            break;
        case Constants::Battery::TU01_SMALLCRUSH:
            if(rval.count(TAGNAME_DEFAULTS) == 1 &&
               rval.at(TAGNAME_DEFAULTS).count(TAGNAME_SCRUSH_BATT) == 1)
                return rval.at(TAGNAME_DEFAULTS).at(TAGNAME_SCRUSH_BATT);
            break;
        case Constants::Battery::TU01_CRUSH:
            if(rval.count(TAGNAME_DEFAULTS) == 1 &&
               rval.at(TAGNAME_DEFAULTS).count(TAGNAME_CRUSH_BATT) == 1)
                return rval.at(TAGNAME_DEFAULTS).at(TAGNAME_CRUSH_BATT);
            break;
        case Constants::Battery::TU01_BIGCRUSH:
            if(rval.count(TAGNAME_DEFAULTS) == 1 &&
               rval.at(TAGNAME_DEFAULTS).count(TAGNAME_BCRUSH_BATT) == 1)
                return rval.at(TAGNAME_DEFAULTS).at(TAGNAME_BCRUSH_BATT);
            break;
        case Constants::Battery::TU01_RABBIT:
            if(rval.count(TAGNAME_DEFAULTS) == 1 &&
               rval.at(TAGNAME_DEFAULTS).count(TAGNAME_RABBIT_BATT) == 1)
                return rval.at(TAGNAME_DEFAULTS).at(TAGNAME_RABBIT_BATT);
            break;
        case Constants::Battery::TU01_ALPHABIT:
            if(rval.count(TAGNAME_DEFAULTS) == 1 &&
               rval.at(TAGNAME_DEFAULTS).count(TAGNAME_ALPHABIT_BATT) == 1)
                return rval.at(TAGNAME_DEFAULTS).at(TAGNAME_ALPHABIT_BATT);
            break;
        case Constants::Battery::TU01_BLOCK_ALPHABIT:
            if(rval.count(TAGNAME_DEFAULTS) == 1 &&
               rval.at(TAGNAME_DEFAULTS).count(TAGNAME_BLALPHABIT_BATT) == 1)
                return rval.at(TAGNAME_DEFAULTS).at(TAGNAME_BLALPHABIT_BATT);
            break;
        default:
            raiseBugException("invalid battery");
    }
    return {};
}

json Configuration::findBatteryTestSettNode(const json & rootNode,
                                            Constants::Battery batt) {
    if(rootNode.empty())
        raiseBugException("empty json node");

    json rval = findBatterySettingsNode(rootNode , batt);
    if(rval.empty())
        return {};

    switch(batt) {
        case Constants::Battery::NIST_STS:
        case Constants::Battery::DIEHARDER:
            if(rval.count(TAGNAME_TEST_SPECIFIC_SETT) == 1)
                return rval.at(TAGNAME_TEST_SPECIFIC_SETT);
            break;
        case Constants::Battery::TU01_SMALLCRUSH:
            if(rval.count(TAGNAME_TEST_SPECIFIC_SETT) == 1 &&
               rval.at(TAGNAME_TEST_SPECIFIC_SETT).count(TAGNAME_SCRUSH_BATT) == 1)
                return rval.at(TAGNAME_TEST_SPECIFIC_SETT).at(TAGNAME_SCRUSH_BATT);
            break;
        case Constants::Battery::TU01_CRUSH:
            if(rval.count(TAGNAME_TEST_SPECIFIC_SETT) == 1 &&
               rval.at(TAGNAME_TEST_SPECIFIC_SETT).count(TAGNAME_CRUSH_BATT) == 1)
                return rval.at(TAGNAME_TEST_SPECIFIC_SETT).at(TAGNAME_CRUSH_BATT);
            break;
        case Constants::Battery::TU01_BIGCRUSH:
            if(rval.count(TAGNAME_TEST_SPECIFIC_SETT) == 1 &&
               rval.at(TAGNAME_TEST_SPECIFIC_SETT).count(TAGNAME_BCRUSH_BATT) == 1)
                return rval.at(TAGNAME_TEST_SPECIFIC_SETT).at(TAGNAME_BCRUSH_BATT);
            break;
        case Constants::Battery::TU01_RABBIT:
            if(rval.count(TAGNAME_TEST_SPECIFIC_SETT) == 1 &&
               rval.at(TAGNAME_TEST_SPECIFIC_SETT).count(TAGNAME_RABBIT_BATT) == 1)
                return rval.at(TAGNAME_TEST_SPECIFIC_SETT).at(TAGNAME_RABBIT_BATT);
            break;
        case Constants::Battery::TU01_ALPHABIT:
            if(rval.count(TAGNAME_TEST_SPECIFIC_SETT) == 1 &&
               rval.at(TAGNAME_TEST_SPECIFIC_SETT).count(TAGNAME_ALPHABIT_BATT) == 1)
                return rval.at(TAGNAME_TEST_SPECIFIC_SETT).at(TAGNAME_ALPHABIT_BATT);
            break;
        case Constants::Battery::TU01_BLOCK_ALPHABIT:
            if(rval.count(TAGNAME_TEST_SPECIFIC_SETT) == 1 &&
               rval.at(TAGNAME_TEST_SPECIFIC_SETT).count("block_alphabit") == 1)
                return rval.at(TAGNAME_TEST_SPECIFIC_SETT).at("block_alphabit");
            break;
        default:
            raiseBugException("invalid battery");
    }
    return {};
}

json Configuration::findTestSpecificNode(const json & rootNode, Constants::Battery batt , int testId) {
    if(rootNode.empty())
        raiseBugException("empty json node");

    json testSpecificSettNode = findBatteryTestSettNode(rootNode , batt);
    if(testSpecificSettNode.empty())
        return {};

    for(const json & el : testSpecificSettNode) {
        if(el.count(TAGNAME_TEST_ID) == 1 && el.at(TAGNAME_TEST_ID) == testId)
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

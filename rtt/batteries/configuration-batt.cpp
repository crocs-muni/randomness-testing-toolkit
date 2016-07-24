#include "configuration-batt.h"

namespace rtt {
namespace batteries {

const std::string Configuration::XPATH_DIEHARDER_DEFAULT_TESTS         = "DIEHARDER_SETTINGS/DEFAULT_TESTS";
const std::string Configuration::XPATH_DIEHARDER_DEFAULT_ARGUMENTS     = "DIEHARDER_SETTINGS/DEFAULT_ARGUMENTS";
const std::string Configuration::XPATH_DIEHARDER_DEFAULT_PSAMPLES      = "DIEHARDER_SETTINGS/DEFAULT_PSAMPLES";
const std::string Configuration::XPATH_DIEHARDER_TESTS_SETTINGS        = "DIEHARDER_SETTINGS/TESTS_SETTINGS";
const std::string Configuration::XPATH_DIEHARDER_ATTRIBUTE_TEST_INDEX  = "test";
const std::string Configuration::XPATH_DIEHARDER_TEST_ARGUMENTS        = "ARGUMENTS";
const std::string Configuration::XPATH_DIEHARDER_TEST_PSAMPLES         = "PSAMPLES";

const std::string Configuration::XPATH_NISTSTS_DEFAULT_TESTS         = "NIST_STS_SETTINGS/DEFAULT_TESTS";
const std::string Configuration::XPATH_NISTSTS_DEFAULT_STREAM_SIZE   = "NIST_STS_SETTINGS/DEFAULT_STREAM_SIZE";
const std::string Configuration::XPATH_NISTSTS_DEFAULT_STREAM_COUNT  = "NIST_STS_SETTINGS/DEFAULT_STREAM_COUNT";
const std::string Configuration::XPATH_NISTSTS_TEST_STREAM_SIZE      = "STREAM_SIZE";
const std::string Configuration::XPATH_NISTSTS_TEST_STREAM_COUNT     = "STREAM_COUNT";
const std::string Configuration::XPATH_NISTSTS_TEST_BLOCK_LENGTH     = "BLOCK_LENGTH";
const std::string Configuration::XPATH_NISTSTS_TESTS_SETTINGS        = "NIST_STS_SETTINGS/TESTS_SETTINGS";
const std::string Configuration::XPATH_NISTSTS_ATTRIBUTE_TEST_INDEX  = "test";

const std::string Configuration::XPATH_TU01_SMALL_CRUSH_DEFAULT_TESTS       = "TESTU01_SETTINGS/DEFAULT_TESTS_SCRUSH";
const std::string Configuration::XPATH_TU01_CRUSH_DEFAULT_TESTS             = "TESTU01_SETTINGS/DEFAULT_TESTS_CRUSH";
const std::string Configuration::XPATH_TU01_BIG_CRUSH_DEFAULT_TESTS         = "TESTU01_SETTINGS/DEFAULT_TESTS_BCRUSH";
const std::string Configuration::XPATH_TU01_RABBIT_DEFAULT_TESTS            = "TESTU01_SETTINGS/DEFAULT_TESTS_RABBIT";
const std::string Configuration::XPATH_TU01_ALPHABIT_DEFAULT_TESTS          = "TESTU01_SETTINGS/DEFAULT_TESTS_ALPHABIT";
const std::string Configuration::XPATH_TU01_BLOCK_ALPHABIT_DEFAULT_TESTS    = "TESTU01_SETTINGS/DEFAULT_TESTS_BLOCK_ALPHABIT";
const std::string Configuration::XPATH_TU01_DEFAULT_REPS                    = "TESTU01_SETTINGS/DEFAULT_REPETITIONS";
const std::string Configuration::XPATH_TU01_DEFAULT_BIT_NB                  = "TESTU01_SETTINGS/DEFAULT_BIT_NB";
const std::string Configuration::XPATH_TU01_DEFAULT_BIT_R                   = "TESTU01_SETTINGS/DEFAULT_BIT_R";
const std::string Configuration::XPATH_TU01_DEFAULT_BIT_S                   = "TESTU01_SETTINGS/DEFAULT_BIT_S";
const std::string Configuration::XPATH_TU01_DEFAULT_BIT_W                   = "TESTU01_SETTINGS/DEFAULT_BIT_W";
const std::string Configuration::XPATH_TU01_SMALL_CRUSH_SETTINGS            = "TESTU01_SETTINGS/SMALL_CRUSH_SETTINGS";
const std::string Configuration::XPATH_TU01_CRUSH_SETTINGS                  = "TESTU01_SETTINGS/CRUSH_SETTINGS";
const std::string Configuration::XPATH_TU01_BIG_CRUSH_SETTINGS              = "TESTU01_SETTINGS/BIG_CRUSH_SETTINGS";
const std::string Configuration::XPATH_TU01_RABBIT_SETTINGS                 = "TESTU01_SETTINGS/RABBIT_SETTINGS";
const std::string Configuration::XPATH_TU01_ALPHABIT_SETTINGS               = "TESTU01_SETTINGS/ALPHABIT_SETTINGS";
const std::string Configuration::XPATH_TU01_BLOCK_ALPHABIT_SETTINGS         = "TESTU01_SETTINGS/BLOCK_ALPHABIT_SETTINGS";
const std::string Configuration::XPATH_TU01_TEST_REPS                       = "REPETITIONS";
const std::string Configuration::XPATH_TU01_TEST_PARAMS                     = "PARAMS";
const std::string Configuration::XPATH_TU01_TEST_BIT_NB                     = "BIT_NB";
const std::string Configuration::XPATH_TU01_TEST_BIT_R                      = "BIT_R";
const std::string Configuration::XPATH_TU01_TEST_BIT_S                      = "BIT_S";
const std::string Configuration::XPATH_TU01_TEST_BIT_W                      = "BIT_W";
const std::string Configuration::XPATH_TU01_ATTRIBUTE_TEST_INDEX            = "test";
const std::string Configuration::XPATH_TU01_ATTRIBUTE_PAR_NAME              = "name";

Configuration Configuration::getInstance(const std::string & configFileName) {
    TiXmlNode * xmlCfg;
    loadXMLFile(xmlCfg , configFileName);

    Configuration conf;
    conf.loadDieharderVariables(xmlCfg);
    conf.loadNiststsVariables(xmlCfg);
    conf.loadTestU01Variables(xmlCfg);
    return conf;
}

std::vector<int> Configuration::getBatteryDefaultTests(Constants::Battery battery) const {
    switch(battery) {
    case Constants::Battery::DIEHARDER:             return dieharderDefaultTests;
    case Constants::Battery::NIST_STS:              return niststsDefaultTests;
    case Constants::Battery::TU01_SMALLCRUSH:       return tu01SmallCrushDefaultTests;
    case Constants::Battery::TU01_CRUSH:            return tu01CrushDefaultTests;
    case Constants::Battery::TU01_BIGCRUSH:         return tu01BigCrushDefaultTests;
    case Constants::Battery::TU01_RABBIT:           return tu01RabbitDefaultTests;
    case Constants::Battery::TU01_ALPHABIT:         return tu01AlphabitDefaultTests;
    case Constants::Battery::TU01_BLOCK_ALPHABIT:   return tu01BlockAlphabitDefaultTests;
    default:raiseBugException("invalid battery");
    }
}

int Configuration::getDieharderDefaultPSamples() const {
    return dieharderDefaultPSamples;
}

std::string Configuration::getDieharderDefaultArguments() const {
    return dieharderDefaultArguments;
}

int Configuration::getDieharderTestPSamples(int testIndex) const {
    if(dieharderTestPSamples.find(testIndex) == dieharderTestPSamples.end())
        return VALUE_INT_NOT_SET;

    return dieharderTestPSamples.at(testIndex);
}

std::string Configuration::getDieharderTestArguments(int testIndex) const {
    if(dieharderTestArguments.find(testIndex) == dieharderTestArguments.end())
        return "";

    return dieharderTestArguments.at(testIndex);
}

std::string Configuration::getNiststsDefaultStreamSize() const {
    return niststsDefaultStreamSize;
}

std::string Configuration::getNiststsDefaultStreamCount() const {
    return niststsDefaultStreamCount;
}

std::string Configuration::getNiststsTestStreamSize(int testIndex) const {
    if(niststsTestStreamSize.find(testIndex) == niststsTestStreamSize.end())
        return "";

    return niststsTestStreamSize.at(testIndex);
}

std::string Configuration::getNiststsTestStreamCount(int testIndex) const {
    if(niststsTestStreamCount.find(testIndex) == niststsTestStreamCount.end())
        return "";

    return niststsTestStreamCount.at(testIndex);
}

std::string Configuration::getNiststsTestBlockLength(int testIndex) const {
    if(niststsTestBlockLength.find(testIndex) == niststsTestBlockLength.end())
        return "";

    return niststsTestBlockLength.at(testIndex);
}

int Configuration::getTestu01DefaultRepetitions() const {
    return testu01DefaultRepetitions;
}

std::string Configuration::getTestU01DefaultBitNB() const {
    return testu01DefaultBitNB;
}

std::string Configuration::getTestU01DefaultBitR() const {
    return testu01DefaultBitR;
}

std::string Configuration::getTestU01DefaultBitS() const {
    return testu01DefaultBitS;
}

std::string Configuration::getTestU01DefaultBitW() const {
    return testu01DefaultBitW;
}

int Configuration::getTestU01BatteryTestRepetitions(Constants::Battery battery,
                                                    int testIndex) const {
    const std::map<int , int> * variable;
    switch(battery) {
    case Constants::Battery::TU01_SMALLCRUSH:
        variable = &tu01SmallCrushTestRepetitions;
        break;
    case Constants::Battery::TU01_CRUSH:
        variable = &tu01CrushTestRepetitions;
        break;
    case Constants::Battery::TU01_BIGCRUSH:
        variable = &tu01BigCrushTestRepetitions;
        break;
    case Constants::Battery::TU01_RABBIT:
        variable = &tu01RabbitTestRepetitions;
        break;
    case Constants::Battery::TU01_ALPHABIT:
        variable = &tu01AlphabitTestRepetitions;
        break;
    case Constants::Battery::TU01_BLOCK_ALPHABIT:
        variable = &tu01BlockAlphabitTestRepetitions;
        break;
    default:raiseBugException("invalid battery");
    }
    if(variable->find(testIndex) == variable->end())
        return VALUE_INT_NOT_SET;

    return variable->at(testIndex);
}

std::string Configuration::getTestU01BatteryTestParams(Constants::Battery battery,
                                                       int testIndex,
                                                       const std::string & parName) {
    const std::map<int , std::map<std::string , std::string>> * variable;
    switch(battery) {
    case Constants::Battery::TU01_SMALLCRUSH:
        variable = &tu01SmallCrushTestParams;
        break;
    case Constants::Battery::TU01_CRUSH:
        variable = &tu01CrushTestParams;
        break;
    case Constants::Battery::TU01_BIGCRUSH:
        variable = &tu01BigCrushTestParams;
        break;
    default:raiseBugException("invalid battery");
    }
    if(variable->find(testIndex) == variable->end())
        return "";
    if(variable->at(testIndex).find(parName) == variable->at(testIndex).end())
        return "";

    return variable->at(testIndex).at(parName);
}

std::string Configuration::getTestU01BatteryTestBitNB(Constants::Battery battery,
                                                      int testIndex) {
    const std::map<int , std::string> * variable;
    switch(battery) {
    case Constants::Battery::TU01_RABBIT:
        variable = &tu01RabbitTestBitNB;
        break;
    case Constants::Battery::TU01_ALPHABIT:
        variable = &tu01AlphabitTestBitNB;
        break;
    case Constants::Battery::TU01_BLOCK_ALPHABIT:
        variable = &tu01BlockAlphabitTestBitNB;
        break;
    default:raiseBugException("invalid battery");
    }
    if(variable->find(testIndex) == variable->end())
        return "";

    return variable->at(testIndex);
}

std::string Configuration::getTestU01BatteryTestBitR(Constants::Battery battery,
                                                     int testIndex) {
    const std::map<int , std::string> * variable;
    switch(battery) {
    case Constants::Battery::TU01_ALPHABIT:
        variable = &tu01AlphabitTestBitR;
        break;
    case Constants::Battery::TU01_BLOCK_ALPHABIT:
        variable = &tu01BlockAlphabitTestBitR;
        break;
    default:raiseBugException("invalid battery");
    }
    if(variable->find(testIndex) == variable->end())
        return "";

    return variable->at(testIndex);
}

std::string Configuration::getTestU01BatteryTestBitS(Constants::Battery battery,
                                                     int testIndex) {
    const std::map<int , std::string> * variable;
    switch(battery) {
    case Constants::Battery::TU01_ALPHABIT:
        variable = &tu01AlphabitTestBitS;
        break;
    case Constants::Battery::TU01_BLOCK_ALPHABIT:
        variable = &tu01BlockAlphabitTestBitS;
        break;
    default:raiseBugException("invalid battery");
    }
    if(variable->find(testIndex) == variable->end())
        return "";

    return variable->at(testIndex);
}

std::string Configuration::getTestU01BatteryTestBitW(Constants::Battery battery,
                                                     int testIndex) {
    const std::map<int , std::string> * variable;
    switch(battery) {
    case Constants::Battery::TU01_BLOCK_ALPHABIT:
        variable = &tu01BlockAlphabitTestBitW;
        break;
    default:raiseBugException("invalid battery");
    }
    if(variable->find(testIndex) == variable->end())
        return "";

    return variable->at(testIndex);
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

void Configuration::loadDieharderVariables(TiXmlNode * xmlCfg) {
    if(!xmlCfg)
        raiseBugException("null xml node");

    dieharderDefaultTests = getDefaultTests(xmlCfg , XPATH_DIEHARDER_DEFAULT_TESTS);
    dieharderDefaultPSamples = getIntValue(xmlCfg , XPATH_DIEHARDER_DEFAULT_PSAMPLES);
    dieharderDefaultArguments = getXMLElementValue(xmlCfg , XPATH_DIEHARDER_DEFAULT_ARGUMENTS);
    dieharderTestPSamples = createMapIntInt(xmlCfg ,
                                            XPATH_DIEHARDER_TESTS_SETTINGS ,
                                            XPATH_DIEHARDER_ATTRIBUTE_TEST_INDEX ,
                                            XPATH_DIEHARDER_TEST_PSAMPLES);
    dieharderTestArguments = createMapIntString(xmlCfg ,
                                                XPATH_DIEHARDER_TESTS_SETTINGS ,
                                                XPATH_DIEHARDER_ATTRIBUTE_TEST_INDEX ,
                                                XPATH_DIEHARDER_TEST_ARGUMENTS);
}

void Configuration::loadNiststsVariables(TiXmlNode * xmlCfg) {
    if(!xmlCfg)
        raiseBugException("null xml node");

    niststsDefaultTests = getDefaultTests(xmlCfg , XPATH_NISTSTS_DEFAULT_TESTS);
    niststsDefaultStreamCount = getXMLElementValue(xmlCfg , XPATH_NISTSTS_DEFAULT_STREAM_COUNT);
    niststsDefaultStreamSize = getXMLElementValue(xmlCfg , XPATH_NISTSTS_DEFAULT_STREAM_SIZE);
    niststsTestStreamCount = createMapIntString(xmlCfg ,
                                                XPATH_NISTSTS_TESTS_SETTINGS,
                                                XPATH_NISTSTS_ATTRIBUTE_TEST_INDEX,
                                                XPATH_NISTSTS_TEST_STREAM_COUNT);
    niststsTestStreamSize = createMapIntString(xmlCfg ,
                                               XPATH_NISTSTS_TESTS_SETTINGS,
                                               XPATH_NISTSTS_ATTRIBUTE_TEST_INDEX,
                                               XPATH_NISTSTS_TEST_STREAM_SIZE);
    niststsTestBlockLength = createMapIntString(xmlCfg ,
                                                XPATH_NISTSTS_TESTS_SETTINGS,
                                                XPATH_NISTSTS_ATTRIBUTE_TEST_INDEX,
                                                XPATH_NISTSTS_TEST_BLOCK_LENGTH);
}

void Configuration::loadTestU01Variables(TiXmlNode * xmlCfg) {
    if(!xmlCfg)
        raiseBugException("null xml node");
    /* Default repetitions */
    testu01DefaultRepetitions   = getIntValue(xmlCfg , XPATH_TU01_DEFAULT_REPS);
    /* Default NB, R, S, W */
    testu01DefaultBitNB         = getXMLElementValue(xmlCfg , XPATH_TU01_DEFAULT_BIT_NB);
    testu01DefaultBitR          = getXMLElementValue(xmlCfg , XPATH_TU01_DEFAULT_BIT_R);
    testu01DefaultBitS          = getXMLElementValue(xmlCfg , XPATH_TU01_DEFAULT_BIT_S);
    testu01DefaultBitW          = getXMLElementValue(xmlCfg , XPATH_TU01_DEFAULT_BIT_W);
    /* Default test constants */
    tu01SmallCrushDefaultTests      = getDefaultTests(xmlCfg , XPATH_TU01_SMALL_CRUSH_DEFAULT_TESTS);
    tu01CrushDefaultTests           = getDefaultTests(xmlCfg , XPATH_TU01_CRUSH_DEFAULT_TESTS);
    tu01BigCrushDefaultTests        = getDefaultTests(xmlCfg , XPATH_TU01_BIG_CRUSH_DEFAULT_TESTS);
    tu01RabbitDefaultTests          = getDefaultTests(xmlCfg , XPATH_TU01_RABBIT_DEFAULT_TESTS);
    tu01AlphabitDefaultTests        = getDefaultTests(xmlCfg , XPATH_TU01_ALPHABIT_DEFAULT_TESTS);
    tu01BlockAlphabitDefaultTests   = getDefaultTests(xmlCfg , XPATH_TU01_BLOCK_ALPHABIT_DEFAULT_TESTS);
    /* Test and battery specific repetitions */
    tu01SmallCrushTestRepetitions = createMapIntInt(xmlCfg ,
                                                    XPATH_TU01_SMALL_CRUSH_SETTINGS ,
                                                    XPATH_TU01_ATTRIBUTE_TEST_INDEX ,
                                                    XPATH_TU01_TEST_REPS);
    tu01CrushTestRepetitions = createMapIntInt(xmlCfg ,
                                               XPATH_TU01_CRUSH_SETTINGS ,
                                               XPATH_TU01_ATTRIBUTE_TEST_INDEX ,
                                               XPATH_TU01_TEST_REPS);
    tu01BigCrushTestRepetitions = createMapIntInt(xmlCfg ,
                                                  XPATH_TU01_BIG_CRUSH_SETTINGS ,
                                                  XPATH_TU01_ATTRIBUTE_TEST_INDEX ,
                                                  XPATH_TU01_TEST_REPS);
    tu01RabbitTestRepetitions = createMapIntInt(xmlCfg ,
                                                XPATH_TU01_RABBIT_SETTINGS ,
                                                XPATH_TU01_ATTRIBUTE_TEST_INDEX ,
                                                XPATH_TU01_TEST_REPS);
    tu01AlphabitTestRepetitions = createMapIntInt(xmlCfg ,
                                                  XPATH_TU01_ALPHABIT_SETTINGS ,
                                                  XPATH_TU01_ATTRIBUTE_TEST_INDEX ,
                                                  XPATH_TU01_TEST_REPS);
    tu01BlockAlphabitTestRepetitions = createMapIntInt(xmlCfg ,
                                                       XPATH_TU01_BLOCK_ALPHABIT_SETTINGS ,
                                                       XPATH_TU01_ATTRIBUTE_TEST_INDEX ,
                                                       XPATH_TU01_TEST_REPS);
    /* Test and battery specific additional parameters */
    tu01SmallCrushTestParams = createMapIntMap(xmlCfg ,
                                               XPATH_TU01_SMALL_CRUSH_SETTINGS ,
                                               XPATH_TU01_ATTRIBUTE_TEST_INDEX ,
                                               XPATH_TU01_TEST_PARAMS ,
                                               XPATH_TU01_ATTRIBUTE_PAR_NAME);
    tu01CrushTestParams = createMapIntMap(xmlCfg,
                                          XPATH_TU01_CRUSH_SETTINGS,
                                          XPATH_TU01_ATTRIBUTE_TEST_INDEX ,
                                          XPATH_TU01_TEST_PARAMS ,
                                          XPATH_TU01_ATTRIBUTE_PAR_NAME);
    tu01BigCrushTestParams = createMapIntMap(xmlCfg,
                                             XPATH_TU01_BIG_CRUSH_SETTINGS,
                                             XPATH_TU01_ATTRIBUTE_TEST_INDEX ,
                                             XPATH_TU01_TEST_PARAMS ,
                                             XPATH_TU01_ATTRIBUTE_PAR_NAME);
    /* Test and battery specific NB */
    tu01RabbitTestBitNB = createMapIntString(xmlCfg ,
                                             XPATH_TU01_RABBIT_SETTINGS ,
                                             XPATH_TU01_ATTRIBUTE_TEST_INDEX ,
                                             XPATH_TU01_TEST_BIT_NB);
    tu01AlphabitTestBitNB = createMapIntString(xmlCfg ,
                                               XPATH_TU01_ALPHABIT_SETTINGS ,
                                               XPATH_TU01_ATTRIBUTE_TEST_INDEX ,
                                               XPATH_TU01_TEST_BIT_NB);
    tu01BlockAlphabitTestBitNB = createMapIntString(xmlCfg ,
                                                    XPATH_TU01_BLOCK_ALPHABIT_SETTINGS ,
                                                    XPATH_TU01_ATTRIBUTE_TEST_INDEX ,
                                                    XPATH_TU01_TEST_BIT_NB);
    /* Test and battery specific R */
    tu01AlphabitTestBitR = createMapIntString(xmlCfg ,
                                              XPATH_TU01_ALPHABIT_SETTINGS ,
                                              XPATH_TU01_ATTRIBUTE_TEST_INDEX ,
                                              XPATH_TU01_TEST_BIT_R);
    tu01BlockAlphabitTestBitR = createMapIntString(xmlCfg ,
                                                   XPATH_TU01_BLOCK_ALPHABIT_SETTINGS ,
                                                   XPATH_TU01_ATTRIBUTE_TEST_INDEX ,
                                                   XPATH_TU01_TEST_BIT_R);

    /* Test and battery specific S */
    tu01AlphabitTestBitS = createMapIntString(xmlCfg ,
                                              XPATH_TU01_ALPHABIT_SETTINGS ,
                                              XPATH_TU01_ATTRIBUTE_TEST_INDEX ,
                                              XPATH_TU01_TEST_BIT_S);
    tu01BlockAlphabitTestBitS = createMapIntString(xmlCfg ,
                                                   XPATH_TU01_BLOCK_ALPHABIT_SETTINGS ,
                                                   XPATH_TU01_ATTRIBUTE_TEST_INDEX ,
                                                   XPATH_TU01_TEST_BIT_S);
    /* Test and battery specific W */
    tu01BlockAlphabitTestBitW = createMapIntString(xmlCfg ,
                                                   XPATH_TU01_BLOCK_ALPHABIT_SETTINGS ,
                                                   XPATH_TU01_ATTRIBUTE_TEST_INDEX ,
                                                   XPATH_TU01_TEST_BIT_W);
}

std::map<std::string , std::string> Configuration::createMapStringString(
        TiXmlNode * xmlCfg,
        const std::string & parentXpath,
        const std::string & keyAttribute,
        const std::string & valueTag) {
    if(!xmlCfg)
        raiseBugException("null xml node");

    TiXmlNode * parent = getXMLElement(xmlCfg , parentXpath);
    if(!parent || !parent->FirstChild())
        return {};

    std::map<std::string , std::string> rval;
    const char * key = NULL;
    std::string value;
    TiXmlElement * childEl = NULL;

    for(TiXmlNode * child = parent->FirstChild() ;
        child ; child = child->NextSibling()) {
        childEl = child->ToElement();
        key = childEl->Attribute(keyAttribute.c_str());
        if(!key || strlen(key) < 1)
            throw RTTException(objectInfo ,
                               "child element of tag " + parentXpath +
                               " must have attribute: " + keyAttribute);

        value = getXMLElementValue(child , valueTag);

        if(rval.find(key) != rval.end())
            throw RTTException(objectInfo ,
                               parentXpath + " tag contains multiple children with following " +
                               "value of attribute \"" + keyAttribute + "\": " + key);
        if(!value.empty())
            rval[key] = std::move(value);
    }

    return rval;
}

std::map<int, std::string> Configuration::createMapIntString(
        TiXmlNode * xmlCfg,
        const std::string & parentXpath,
        const std::string & keyAttribute,
        const std::string & valueTag) {
    if(!xmlCfg)
        raiseBugException("null xml node");

    std::map<std::string , std::string> tmp =
            createMapStringString(xmlCfg , parentXpath , keyAttribute , valueTag);
    std::map<int , std::string> rval;
    for(const auto & it : tmp) {
        try {
            rval[Utils::strtoi(it.first)] = it.second;
        } catch (std::runtime_error ex) {
            throw RTTException(objectInfo , parentXpath + " tag contains invalid child: " +
                               ex.what());
        }
    }
    return rval;
}

std::map<int, int> Configuration::createMapIntInt(
        TiXmlNode * xmlCfg,
        const std::string & parentXpath,
        const std::string & keyAttribute,
        const std::string & valueTag) {
    if(!xmlCfg)
        raiseBugException("null xml node");

    std::map<std::string , std::string> tmp =
            createMapStringString(xmlCfg , parentXpath , keyAttribute , valueTag);
    std::map<int , int> rval;
    for(const auto & it : tmp) {
        try {
            rval[Utils::strtoi(it.first)] = Utils::strtoi(it.second);
        } catch (std::runtime_error ex) {
            throw RTTException(objectInfo , parentXpath + " tag contains invalid child: " +
                               ex.what());
        }
    }
    return rval;
}

std::map<int, std::map<std::string, std::string> > Configuration::createMapIntMap(
        TiXmlNode *xmlCfg,
        const std::string &parentXpath,
        const std::string &mainKeyAttribute,
        const std::string &mainValueTag,
        const std::string &secKeyAttribute,
        const std::string &secValueTag) {
    if(!xmlCfg)
        raiseBugException("null xml node");

    TiXmlNode * parent = getXMLElement(xmlCfg , parentXpath);
    if(!parent || !parent->FirstChild())
        return {};

    std::map<int , std::map<std::string , std::string>> rval;
    const char * key = NULL;
    int keyInt = 0;
    std::map<std::string , std::string> value;
    TiXmlElement * childEl = NULL;

    for(TiXmlNode * child = parent->FirstChild() ;
        child ; child = child->NextSibling()) {
        childEl = child->ToElement();
        key = childEl->Attribute(mainKeyAttribute.c_str());
        if(!key || strlen(key) < 1)
            throw RTTException(objectInfo ,
                               "child element of tag " + parentXpath +
                               " must have attribute: " + mainKeyAttribute);
        try {
            keyInt = Utils::strtoi(key);
        } catch (std::runtime_error ex) {
            throw RTTException(objectInfo , parentXpath + " tag contains invalid child: " +
                               ex.what());
        }

        if(rval.find(keyInt) != rval.end())
            throw RTTException(objectInfo ,
                               parentXpath + " tag contains multiple children with following " +
                               "value of attribute \"" + mainKeyAttribute + "\": " + key);
        value = createMapStringString(child , mainValueTag , secKeyAttribute , secValueTag);
        if(!value.empty())
            rval[keyInt] = std::move(value);
    }
    return rval;
}

std::vector<int> Configuration::getDefaultTests(TiXmlNode * xmlCfg,
                                                const std::string & xpath) {
    if(!xmlCfg)
        raiseBugException("null xml node");

    std::string tmp = getXMLElementValue(xmlCfg , xpath);
    if(tmp.empty())
        return {};

    try {
        return Utils::parseStringWithIntRanges(tmp);
    } catch (std::runtime_error ex) {
        throw RTTException(objectInfo ,
                           "error in tag " + xpath + ": " + ex.what());
    }
}

int Configuration::getIntValue(TiXmlNode * xmlCfg, const std::string &xpath) {
    if(!xmlCfg)
        raiseBugException("null xml node");

    std::string tmp = getXMLElementValue(xmlCfg , xpath);
    if(tmp.empty())
        return VALUE_INT_NOT_SET;

    try {
        return Utils::strtoi(tmp);
    } catch (std::runtime_error ex) {
        throw RTTException(objectInfo ,
                           "error in tag " + xpath + ": " + ex.what());
    }
}

} // namespace batteries
} // namespace rtt

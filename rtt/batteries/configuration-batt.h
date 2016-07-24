#ifndef RTT_BATTERIES_CONFIGURATION_H
#define RTT_BATTERIES_CONFIGURATION_H

#include <map>

#include "rtt/constants.h"
#include "rtt/bugexception.h"
#include "rtt/rttexception.h"
#include "libs/tinyXML/xmlproc.h"

namespace rtt {
namespace batteries {

class Configuration {
public:
    /* Constant set to integer values that weren't set */
    static const int VALUE_INT_NOT_SET = -1;

    static Configuration getInstance(const std::string & configFileName);

    /* Getters for variables */
    /* Universal */
    std::vector<int> getBatteryDefaultTests(Constants::Battery battery) const;

    /* Dieharder */
    int getDieharderDefaultPSamples() const;

    std::string getDieharderDefaultArguments() const;

    int getDieharderTestPSamples(int testIndex) const;

    std::string getDieharderTestArguments(int testIndex) const;

    /* NIST STS */
    std::string getNiststsDefaultStreamSize() const;

    std::string getNiststsDefaultStreamCount() const;

    std::string getNiststsTestStreamSize(int testIndex) const;

    std::string getNiststsTestStreamCount(int testIndex) const;

    std::string getNiststsTestBlockLength(int testIndex) const;

    /* TestU01 */
    int getTestu01DefaultRepetitions() const;

    std::string getTestU01DefaultBitNB() const;

    std::string getTestU01DefaultBitR() const;

    std::string getTestU01DefaultBitS() const;

    std::string getTestU01DefaultBitW() const;

    int getTestU01BatteryTestRepetitions(Constants::Battery battery ,
                                         int testIndex) const;

    std::string getTestU01BatteryTestParams(Constants::Battery battery ,
                                            int testIndex ,
                                            const std::string & parName);

    std::string getTestU01BatteryTestBitNB(Constants::Battery battery,
                                           int testIndex);

    std::string getTestU01BatteryTestBitR(Constants::Battery battery,
                                          int testIndex);

    std::string getTestU01BatteryTestBitS(Constants::Battery battery,
                                          int testIndex);

    std::string getTestU01BatteryTestBitW(Constants::Battery battery,
                                          int testIndex);

private:
    /* XPaths inside config file */
    /* Dieharder constants */
    static const std::string XPATH_DIEHARDER_DEFAULT_TESTS;
    static const std::string XPATH_DIEHARDER_DEFAULT_ARGUMENTS;
    static const std::string XPATH_DIEHARDER_DEFAULT_PSAMPLES;
    static const std::string XPATH_DIEHARDER_TESTS_SETTINGS;
    static const std::string XPATH_DIEHARDER_ATTRIBUTE_TEST_INDEX;
    static const std::string XPATH_DIEHARDER_TEST_ARGUMENTS;
    static const std::string XPATH_DIEHARDER_TEST_PSAMPLES;

    /* NIST STS constants*/
    static const std::string XPATH_NISTSTS_DEFAULT_TESTS;
    static const std::string XPATH_NISTSTS_TESTS_SETTINGS;
    static const std::string XPATH_NISTSTS_DEFAULT_STREAM_SIZE;
    static const std::string XPATH_NISTSTS_DEFAULT_STREAM_COUNT;
    static const std::string XPATH_NISTSTS_TEST_STREAM_SIZE;
    static const std::string XPATH_NISTSTS_TEST_STREAM_COUNT;
    static const std::string XPATH_NISTSTS_TEST_BLOCK_LENGTH;
    static const std::string XPATH_NISTSTS_ATTRIBUTE_TEST_INDEX;

    /* TestU01 constants */
    static const std::string XPATH_TU01_SMALL_CRUSH_DEFAULT_TESTS;
    static const std::string XPATH_TU01_CRUSH_DEFAULT_TESTS;
    static const std::string XPATH_TU01_BIG_CRUSH_DEFAULT_TESTS;
    static const std::string XPATH_TU01_RABBIT_DEFAULT_TESTS;
    static const std::string XPATH_TU01_ALPHABIT_DEFAULT_TESTS;
    static const std::string XPATH_TU01_BLOCK_ALPHABIT_DEFAULT_TESTS;
    static const std::string XPATH_TU01_DEFAULT_REPS;
    static const std::string XPATH_TU01_DEFAULT_BIT_NB;
    static const std::string XPATH_TU01_DEFAULT_BIT_R;
    static const std::string XPATH_TU01_DEFAULT_BIT_S;
    static const std::string XPATH_TU01_DEFAULT_BIT_W;
    static const std::string XPATH_TU01_SMALL_CRUSH_SETTINGS;
    static const std::string XPATH_TU01_CRUSH_SETTINGS;
    static const std::string XPATH_TU01_BIG_CRUSH_SETTINGS;
    static const std::string XPATH_TU01_RABBIT_SETTINGS;
    static const std::string XPATH_TU01_ALPHABIT_SETTINGS;
    static const std::string XPATH_TU01_BLOCK_ALPHABIT_SETTINGS;
    static const std::string XPATH_TU01_TEST_REPS;
    static const std::string XPATH_TU01_TEST_PARAMS;
    static const std::string XPATH_TU01_TEST_BIT_NB;
    static const std::string XPATH_TU01_TEST_BIT_R;
    static const std::string XPATH_TU01_TEST_BIT_S;
    static const std::string XPATH_TU01_TEST_BIT_W;
    static const std::string XPATH_TU01_ATTRIBUTE_TEST_INDEX;
    static const std::string XPATH_TU01_ATTRIBUTE_PAR_NAME;

    /* Member variables */
    std::string objectInfo = "Battery Configuration";

    /* Variables for Dieharder */
    std::vector<int> dieharderDefaultTests;
    int dieharderDefaultPSamples;
    std::string dieharderDefaultArguments;
    std::map<int , int> dieharderTestPSamples;
    std::map<int , std::string> dieharderTestArguments;

    /* Variables for NIST STS */
    std::vector<int> niststsDefaultTests;
    std::string niststsDefaultStreamSize;
    std::string niststsDefaultStreamCount;
    std::map<int , std::string> niststsTestStreamSize;
    std::map<int , std::string> niststsTestStreamCount;
    std::map<int , std::string> niststsTestBlockLength;

    /* Variables for TestU01 */
    int testu01DefaultRepetitions;
    std::string testu01DefaultBitNB;
    std::string testu01DefaultBitR;
    std::string testu01DefaultBitS;
    std::string testu01DefaultBitW;

    /* Following groups of variables have variant for
     * one or more batteries in TestU01 (e.g. crush batteries
     * don't have variable BitNB, so there is no reason for
     * existence of that variable). They will be accessible
     * via getter for each group and for corresponding battery. */
    /* Default tests - all batteries */
    std::vector<int> tu01SmallCrushDefaultTests;
    std::vector<int> tu01CrushDefaultTests;
    std::vector<int> tu01BigCrushDefaultTests;
    std::vector<int> tu01RabbitDefaultTests;
    std::vector<int> tu01AlphabitDefaultTests;
    std::vector<int> tu01BlockAlphabitDefaultTests;

    /* Test repetitions - all batteries */
    std::map<int , int> tu01SmallCrushTestRepetitions;
    std::map<int , int> tu01CrushTestRepetitions;
    std::map<int , int> tu01BigCrushTestRepetitions;
    std::map<int , int> tu01RabbitTestRepetitions;
    std::map<int , int> tu01AlphabitTestRepetitions;
    std::map<int , int> tu01BlockAlphabitTestRepetitions;

    /* Test parameters - crush batteries */
    std::map<int , std::map<std::string , std::string>> tu01SmallCrushTestParams;
    std::map<int , std::map<std::string , std::string>> tu01CrushTestParams;
    std::map<int , std::map<std::string , std::string>> tu01BigCrushTestParams;

    /* BitNB - rabbit, alphabit, block alphabit */
    std::map<int , std::string> tu01RabbitTestBitNB;
    std::map<int , std::string> tu01AlphabitTestBitNB;
    std::map<int , std::string> tu01BlockAlphabitTestBitNB;

    /* BitR - alphabit, block alphabit */
    std::map<int , std::string> tu01AlphabitTestBitR;
    std::map<int , std::string> tu01BlockAlphabitTestBitR;

    /* BitS - alphabit, block alphabit */
    std::map<int , std::string> tu01AlphabitTestBitS;
    std::map<int , std::string> tu01BlockAlphabitTestBitS;

    /* BitW - block alphabit */
    std::map<int , std::string> tu01BlockAlphabitTestBitW;

    Configuration() {}


    void loadDieharderVariables(TiXmlNode * xmlCfg);
    void loadNiststsVariables(TiXmlNode * xmlCfg);
    void loadTestU01Variables(TiXmlNode * xmlCfg);

    /**
     * @brief createMapStringString Loads child tags of tag parentXpath into map.
     * Value in child attribute keyAttribute is used as map key and value in tag
     * valueTag is used as map value. Both key and value are strings. Value tag
     * doesn't have to exist in child, in that case child is not added into map.
     * If there are multiple children with same attribute value, error is raised.
     * @param xmlCfg config root
     * @param parentXpath path to parent tag
     * @param keyAttribute name of attribute tag that each child must have
     * @param valueTag xpath to child's tag with value. XPath is relative to child.
     * @return created map
     */
    std::map<std::string , std::string> createMapStringString(
            TiXmlNode * xmlCfg ,
            const std::string & parentXpath ,
            const std::string & keyAttribute ,
            const std::string & valueTag);

    /**
     * @brief createMapIntString Calls createMapStringString, converts key into int type.
     * If key is not convertible raises error. Values are left unchanged.
     * @param xmlCfg config root
     * @param parentXpath path to parent tag
     * @param keyAttribute name of attribute tag that each child must have
     * @param valueTag xpath to child's tag with value. XPath is relative to child.
     * @return created map
     */
    std::map<int , std::string> createMapIntString(
            TiXmlNode * xmlCfg ,
            const std::string & parentXpath ,
            const std::string & keyAttribute ,
            const std::string & valueTag);

    /**
     * @brief createMapIntString Calls createMapStringString, converts key and value into
     * int type. If they are not convertible raises error.
     * @param xmlCfg config root
     * @param parentXpath path to parent tag
     * @param keyAttribute name of attribute tag that each child must have
     * @param valueTag xpath to child's tag with value. XPath is relative to child.
     * @return created map
     */
    std::map<int , int> createMapIntInt(
            TiXmlNode * xmlCfg ,
            const std::string & parentXpath ,
            const std::string & keyAttribute ,
            const std::string & valueTag);

    /**
     * @brief createMapIntMap Maps values in secValueTag to keys in secKeyAttribute. Each of
     * these then maps to values in mainKeyAttribute. In practice: each parent has multiple
     * children and these children are parents passed to createMapStringString.
     * @param xmlCfg config root
     * @param parentXpath path to main parent node
     * @param mainKeyAttribute attribute that holds unique identifiers
     * @param mainValueTag path to tag with children - will be passed to createMapStringString
     * @param secKeyAttribute keys in associated maps
     * @param secValueTag tags with secondary values - if empty, the value is right in the tag
     * not it's child
     * @return map of maps
     */
    std::map<int , std::map<std::string , std::string>> createMapIntMap(
            TiXmlNode * xmlCfg,
            const std::string & parentXpath,
            const std::string & mainKeyAttribute,
            const std::string & mainValueTag,
            const std::string & secKeyAttribute,
            const std::string & secValueTag = "");

    std::vector<int> getDefaultTests(TiXmlNode * xmlCfg , const std::string & xpath);

    int getIntValue(TiXmlNode * xmlCfg , const std::string & xpath);
};

} // namespace batteries
} // namespace rtt

#endif // RTT_BATTERIES_CONFIGURATION_H

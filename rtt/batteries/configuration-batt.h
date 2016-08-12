#ifndef RTT_BATTERIES_CONFIGURATION_H
#define RTT_BATTERIES_CONFIGURATION_H

#include <map>
#include <algorithm>

#include "rtt/constants.h"
#include "rtt/bugexception.h"
#include "rtt/rttexception.h"
#include "libs/moderncppjson/json.hpp"

namespace rtt {
namespace batteries {

/* Just a convenience */
using json = nlohmann::json;

typedef std::map<int , int> tIntIntMap;
typedef std::map<int , std::string> tIntStringMap;
typedef std::map<std::string , std::string> tStringStringMap;

class Configuration {
public:
    /* JSON tag name inside config file */
    static const std::string TAGNAME_ROOT;
    static const std::string TAGNAME_DIEHARDER_SETT;
    static const std::string TAGNAME_NISTSTS_SETT;
    static const std::string TAGNAME_TESTU01_SETT;
    static const std::string TAGNAME_SCRUSH_BATT;
    static const std::string TAGNAME_CRUSH_BATT;
    static const std::string TAGNAME_BCRUSH_BATT;
    static const std::string TAGNAME_RABBIT_BATT;
    static const std::string TAGNAME_ALPHABIT_BATT;
    static const std::string TAGNAME_BLALPHABIT_BATT;
    static const std::string TAGNAME_DEFAULTS;
    static const std::string TAGNAME_TEST_SPECIFIC_SETT;
    static const std::string TAGNAME_DEFAULT_TESTS;
    static const std::string TAGNAME_TEST_ID;
    static const std::string TAGNAME_VARIATIONS;
    static const std::string TAGNAME_ARGUMENTS;
    static const std::string TAGNAME_PSAMPLES;
    static const std::string TAGNAME_STREAM_SIZE;
    static const std::string TAGNAME_STREAM_COUNT;
    static const std::string TAGNAME_BLOCK_LENGTH;
    static const std::string TAGNAME_REPETITIONS;
    static const std::string TAGNAME_BIT_NB;
    static const std::string TAGNAME_BIT_R;
    static const std::string TAGNAME_BIT_S;
    static const std::string TAGNAME_BIT_W;
    static const std::string TAGNAME_PARAMS;

    /* Constant set to integer values that weren't set */
    static const int VALUE_INT_NOT_SET = -1;

    static Configuration getInstance(const std::string & configFileName);

    /* Getters for variables */
    std::vector<int> getBatteryDefaultTests(Constants::Battery battery);

    uint getTestVariantsCount(Constants::Battery batt , int testId);

    int getTestVariantsParamInt(Constants::Battery batt ,
                                int testId , uint variantIndex ,
                                const std::string & paramName);

    std::string getTestVariantParamString(Constants::Battery batt ,
                                          int testId , uint variantIndex ,
                                          const std::string & paramName);

    tStringStringMap getTestVariantParamMap(Constants::Battery batt ,
                                            int testId , uint variantIndex ,
                                            const std::string & paramName);

private:
    /* Member variables */
    static const std::string objectInfo;
    json configRoot;

    /* Methods */
    Configuration() {}

    json findBatterySettingsNode(const json & rootNode ,
                                 Constants::Battery batt);

    json findBatteryDefaultSettNode(const json & rootNode ,
                                    Constants::Battery batt);

    json findBatteryTestSettNode(const json & rootNode ,
                                 Constants::Battery batt);

    json findTestSpecificNode(const json & batteryNode ,
                              Constants::Battery batt,
                              int testId);

    std::vector<int> parseTestConstants(json::array_t node);
};

} // namespace batteries
} // namespace rtt

#endif // RTT_BATTERIES_CONFIGURATION_H

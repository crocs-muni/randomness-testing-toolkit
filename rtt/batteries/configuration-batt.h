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

/**
 * @brief The Configuration class Stores configuration of the battery,
 * is read from the config file provided by the user.
 */
class Configuration {
public:
    /* JSON tag name inside config file */
    static const std::string TAGNAME_ROOT;
    static const std::string TAGNAME_DIEHARDER_SETT;
    static const std::string TAGNAME_NISTSTS_SETT;
    static const std::string TAGNAME_SCRUSH_SETT;
    static const std::string TAGNAME_CRUSH_SETT;
    static const std::string TAGNAME_BCRUSH_SETT;
    static const std::string TAGNAME_RABBIT_SETT;
    static const std::string TAGNAME_ALPHABIT_SETT;
    static const std::string TAGNAME_BLALPHABIT_SETT;
    static const std::string TAGNAME_DEFAULTS;
    static const std::string TAGNAME_TEST_SPECIFIC_SETT;
    static const std::string TAGNAME_DEFAULT_TESTS;
    static const std::string TAGNAME_TEST_ID;
    static const std::string TAGNAME_VARIANTS;
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

    /**
     * @brief getInstance
     * @param configFileName Name of the configuration file
     * @return initialized object
     */
    static Configuration getInstance(const std::string & configFileName);

    /**
     * @brief getBatteryDefaultTests
     * @param battery ID of the desired battery
     * @return IDs of the tests that are set for execution in the config files for given battery
     */
    std::vector<int> getBatteryDefaultTests(Constants::Battery battery);

    /**
     * @brief getTestVariantsCount Returns count of variants
     * @param batt Specifies battery
     * @param testId Specifies test
     * @return Count of defined variants of single specific test of single specific battery.
     */
    uint getTestVariantsCount(Constants::Battery batt , int testId);

    /**
     * @brief getTestVariantParamInt Returns integer value of variant parameter.
     * If there is no such variant parameter defined, then test or battery default value is returned.
     * @param batt Specifies battery
     * @param testId Specifies test
     * @param variantIdx Specifies variant
     * @param paramName Name of the parameter
     * @return Gets value of variant parameter of specific test and battery
     */
    int getTestVariantParamInt(Constants::Battery batt ,
                                int testId , uint variantIdx ,
                                const std::string & paramName);

    /**
     * @brief getTestVariantParamString Returns string value of variant parameter.
     * If there is no such variant parameter defined, then test or battery default value is returned.
     * @param batt Specifies battery
     * @param testId Specifies test
     * @param variantIdx Specifies variant
     * @param paramName Name of the parameter
     * @return Gets value of variant parameter of specific test and battery
     */
    std::string getTestVariantParamString(Constants::Battery batt ,
                                          int testId , uint variantIdx ,
                                          const std::string & paramName);

    /**
     * @brief getTestVariantParamMap Returns map value of variant parameter.
     * If there is no such variant parameter defined, then test or battery default value is returned.
     * @param batt Specifies battery
     * @param testId Specifies test
     * @param variantIdx Specifies variant
     * @param paramName Name of the parameter
     * @return Gets value of variant parameter of specific test and battery
     */
    tStringStringMap getTestVariantParamMap(Constants::Battery batt ,
                                            int testId , uint variantIdx ,
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

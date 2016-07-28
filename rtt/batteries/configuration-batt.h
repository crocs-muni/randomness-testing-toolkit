#ifndef RTT_BATTERIES_CONFIGURATION_H
#define RTT_BATTERIES_CONFIGURATION_H

#include <map>
#include <algorithm>

#include "rtt/constants.h"
#include "rtt/bugexception.h"
#include "rtt/rttexception.h"
#include "libs/tinyXML/xmlproc.h"
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
    int getTestu01DefaultRepetitions(Constants::Battery battery) const;

    std::string getTestU01DefaultBitNB(Constants::Battery battery) const;

    std::string getTestU01DefaultBitR(Constants::Battery battery) const;

    std::string getTestU01DefaultBitS(Constants::Battery battery) const;

    std::string getTestU01DefaultBitW(Constants::Battery battery) const;

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
    /* JSON tag name inside config file */
    // TBA!!!!

    /* Member variables */
    std::string objectInfo = "Battery Configuration";

    /* Variables for Dieharder */
    std::vector<int>            dhDefaultTests;
    int                         dhDefaultPSamples = VALUE_INT_NOT_SET;
    std::string                 dhDefaultArguments;
    std::map<int , int>         dhTestPSamples;
    std::map<int , std::string> dhTestArguments;

    /* Variables for NIST STS */
    std::vector<int>            stsDefaultTests;
    std::string                 stsDefaultStreamSize;
    std::string                 stsDefaultStreamCount;
    std::map<int , std::string> stsTestStreamSize;
    std::map<int , std::string> stsTestStreamCount;
    std::map<int , std::string> stsTestBlockSize;

    /* Variables for TestU01 */
    /* Defaults */
    std::map<Constants::Battery , int>                  tu01DefaultReps;
    std::map<Constants::Battery , std::string>          tu01DefaultBitNB;
    std::map<Constants::Battery , std::string>          tu01DefaultBitR;
    std::map<Constants::Battery , std::string>          tu01DefaultBitS;
    std::map<Constants::Battery , std::string>          tu01DefaultBitW;
    std::map<Constants::Battery , std::vector<int>>     tu01DefaultTests;
    /* Test specifics */
    std::map<Constants::Battery , tIntIntMap>                       tu01TestReps;
    std::map<Constants::Battery , std::map<int , tStringStringMap>> tu01TestParams;
    std::map<Constants::Battery , tIntStringMap>                    tu01TestBitNB;
    std::map<Constants::Battery , tIntStringMap>                    tu01TestBitR;
    std::map<Constants::Battery , tIntStringMap>                    tu01TestBitS;
    std::map<Constants::Battery , tIntStringMap>                    tu01TestBitW;

    Configuration() {}

    void loadDieharderVariables(const json::object_t & dhSettingsNode);
    void loadNiststsVariables(const json::object_t & stsSettingsNode);
    void loadTestU01Variables(const json::object_t & tu01SettingsNode);

    template <class K , class V>
    static void getKeyAndValue(const json::object_t & o ,
                               const std::string & key ,
                               const std::string & value ,
                               std::map<K , V> & map);

    template <class T>
    static T valueOrDefault(json::object_t o, const std::string & key, T && def);

    std::vector<int> parseTestConstants(json::array_t node);
};

} // namespace batteries
} // namespace rtt

#endif // RTT_BATTERIES_CONFIGURATION_H

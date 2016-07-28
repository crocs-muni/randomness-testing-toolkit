#include "configuration-batt.h"

namespace rtt {
namespace batteries {

Configuration Configuration::getInstance(const std::string & configFileName) {
    json root = json::parse(Utils::readFileToString(configFileName));

    Configuration conf;

    try {
        root = root.at("randomness-testing-toolkit");

        conf.loadDieharderVariables(root.at("dieharder-settings"));
        conf.loadNiststsVariables(root.at("nist-sts-settings"));
        conf.loadTestU01Variables(root.at("testu01-settings"));
    } catch (std::runtime_error ex) {
        throw RTTException(conf.objectInfo,
                           "error during JSON processing - " + (std::string)ex.what());
    } catch (std::out_of_range ex) {
        throw RTTException(conf.objectInfo,
                           "missing tag in JSON - " + (std::string)ex.what());
    }
    return conf;
}

std::vector<int> Configuration::getBatteryDefaultTests(Constants::Battery battery) const {
    switch(battery) {
    case Constants::Battery::DIEHARDER:             return dhDefaultTests;
    case Constants::Battery::NIST_STS:              return stsDefaultTests;
    case Constants::Battery::TU01_SMALLCRUSH:
    case Constants::Battery::TU01_CRUSH:
    case Constants::Battery::TU01_BIGCRUSH:
    case Constants::Battery::TU01_RABBIT:
    case Constants::Battery::TU01_ALPHABIT:
    case Constants::Battery::TU01_BLOCK_ALPHABIT:
        if(tu01DefaultTests.count(battery) != 1)
            return {};

        return tu01DefaultTests.at(battery);
    default:raiseBugException("invalid battery");
    }
}

int Configuration::getDieharderDefaultPSamples() const {
    return dhDefaultPSamples;
}

std::string Configuration::getDieharderDefaultArguments() const {
    return dhDefaultArguments;
}

int Configuration::getDieharderTestPSamples(int testIndex) const {
    if(dhTestPSamples.find(testIndex) == dhTestPSamples.end())
        return VALUE_INT_NOT_SET;

    return dhTestPSamples.at(testIndex);
}

std::string Configuration::getDieharderTestArguments(int testIndex) const {
    if(dhTestArguments.find(testIndex) == dhTestArguments.end())
        return "";

    return dhTestArguments.at(testIndex);
}

std::string Configuration::getNiststsDefaultStreamSize() const {
    return stsDefaultStreamSize;
}

std::string Configuration::getNiststsDefaultStreamCount() const {
    return stsDefaultStreamCount;
}

std::string Configuration::getNiststsTestStreamSize(int testIndex) const {
    if(stsTestStreamSize.find(testIndex) == stsTestStreamSize.end())
        return "";

    return stsTestStreamSize.at(testIndex);
}

std::string Configuration::getNiststsTestStreamCount(int testIndex) const {
    if(stsTestStreamCount.find(testIndex) == stsTestStreamCount.end())
        return "";

    return stsTestStreamCount.at(testIndex);
}

std::string Configuration::getNiststsTestBlockLength(int testIndex) const {
    if(stsTestBlockSize.find(testIndex) == stsTestBlockSize.end())
        return "";

    return stsTestBlockSize.at(testIndex);
}

int Configuration::getTestu01DefaultRepetitions(Constants::Battery battery) const {
    if(tu01DefaultReps.count(battery))
        return VALUE_INT_NOT_SET;

    return tu01DefaultReps.at(battery);
}

std::string Configuration::getTestU01DefaultBitNB(Constants::Battery battery) const {
    if(tu01DefaultBitNB.count(battery))
        return "";

    return tu01DefaultBitNB.at(battery);
}

std::string Configuration::getTestU01DefaultBitR(Constants::Battery battery) const {
    if(tu01DefaultBitR.count(battery) != 1)
        return "";

    return tu01DefaultBitR.at(battery);
}

std::string Configuration::getTestU01DefaultBitS(Constants::Battery battery) const {
    if(tu01DefaultBitS.count(battery) != 1)
        return "";

    return tu01DefaultBitS.at(battery);
}

std::string Configuration::getTestU01DefaultBitW(Constants::Battery battery) const {
    if(tu01DefaultBitW.count(battery) != 1)
        return "";

    return tu01DefaultBitW.at(battery);
}

int Configuration::getTestU01BatteryTestRepetitions(Constants::Battery battery,
                                                    int testIndex) const {
    if(tu01TestReps.count(battery) != 1)
        return VALUE_INT_NOT_SET;
    if(tu01TestReps.at(battery).count(testIndex) != 1)
        return VALUE_INT_NOT_SET;

    return tu01TestReps.at(battery).at(testIndex);
}

std::string Configuration::getTestU01BatteryTestParams(Constants::Battery battery,
                                                       int testIndex,
                                                       const std::string & parName) {
    if(tu01TestParams.count(battery) != 1)
        return "";
    if(tu01TestParams.at(battery).count(testIndex) != 1)
        return "";
    if(tu01TestParams.at(battery).at(testIndex).count(parName) != 1)
        return "";

    return tu01TestParams.at(battery).at(testIndex).at(parName);
}

std::string Configuration::getTestU01BatteryTestBitNB(Constants::Battery battery,
                                                      int testIndex) {
    if(tu01TestBitNB.count(battery) != 1)
        return "";
    if(tu01TestBitNB.at(battery).count(testIndex) != 1)
        return "";

    return tu01TestBitNB.at(battery).at(testIndex);
}

std::string Configuration::getTestU01BatteryTestBitR(Constants::Battery battery,
                                                     int testIndex) {
    if(tu01TestBitR.count(battery) != 1)
        return "";
    if(tu01TestBitR.at(battery).count(testIndex) != 1)
        return "";

    return tu01TestBitR.at(battery).at(testIndex);
}

std::string Configuration::getTestU01BatteryTestBitS(Constants::Battery battery,
                                                     int testIndex) {
    if(tu01TestBitS.count(battery) != 1)
        return "";
    if(tu01TestBitS.at(battery).count(testIndex) != 1)
        return "";

    return tu01TestBitS.at(battery).at(testIndex);
}

std::string Configuration::getTestU01BatteryTestBitW(Constants::Battery battery,
                                                     int testIndex) {
    if(tu01TestBitW.count(battery) != 1)
        return "";
    if(tu01TestBitW.at(battery).count(testIndex) != 1)
        return "";

    return tu01TestBitW.at(battery).at(testIndex);
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

void Configuration::loadDieharderVariables(/*TiXmlNode * xmlCfg*/const json::object_t & dhSettingsNode) {
    if(dhSettingsNode.empty())
        throw RTTException(objectInfo , "empty Dieharder settings");

    if(dhSettingsNode.count("defaults") == 1) {
        const auto & nDefaults = dhSettingsNode.at("defaults");

        dhDefaultTests =
                parseTestConstants(valueOrDefault(nDefaults , "tests" , json::array_t()));
        if(nDefaults.count("psamples") == 1)
            dhDefaultPSamples = nDefaults.at("psamples");
        dhDefaultArguments =
                valueOrDefault(nDefaults , "arguments" , std::string());
    }

    if(dhSettingsNode.count("test-specific-settings") == 1) {
        const auto & nTestSpecific = dhSettingsNode.at("test-specific-settings");

        std::for_each(nTestSpecific.begin() , nTestSpecific.end() ,
                      [this] (const json::object_t & o) {
            getKeyAndValue(o , "test" , "psamples" , dhTestPSamples);
        });

        std::for_each(nTestSpecific.begin() , nTestSpecific.end() ,
                      [this] (const json::object_t & o) {
            getKeyAndValue(o , "test" , "arguments" , dhTestArguments);
        });

    }
}

void Configuration::loadNiststsVariables(const json::object_t & stsSettingsNode) {
    if(stsSettingsNode.empty())
        throw RTTException(objectInfo , "empty NIST STS settings");

    if(stsSettingsNode.count("defaults") == 1) {
        const json::object_t & nDefaults = stsSettingsNode.at("defaults");

        stsDefaultTests =
                parseTestConstants(valueOrDefault(nDefaults , "tests" , json::array_t()));
        stsDefaultStreamSize =
                valueOrDefault(nDefaults , "stream-size" , std::string());
        stsDefaultStreamCount =
                valueOrDefault(nDefaults , "stream-count" , std::string());
    }

    if(stsSettingsNode.count("test-specific-settings") == 1) {
        const auto & nTestSpecific = stsSettingsNode.at("test-specific-settings");

        std::for_each(nTestSpecific.begin() , nTestSpecific.end() ,
                      [this] (const json::object_t & o) {
           getKeyAndValue(o , "test" , "stream-count" , stsTestStreamCount);
        });
        std::for_each(nTestSpecific.begin() , nTestSpecific.end() ,
                      [this] (const json::object_t & o) {
            getKeyAndValue(o , "test" , "stream-size" , stsTestStreamSize);
        });
        std::for_each(nTestSpecific.begin() , nTestSpecific.end() ,
                      [this] (const json::object_t & o) {
             getKeyAndValue(o , "test" , "block-size" , stsTestBlockSize);
        });
    }
}

void Configuration::loadTestU01Variables(const json::object_t & tu01SettingsNode) {
    if(tu01SettingsNode.empty())
        throw RTTException(objectInfo , "empty TestU01 settings");

    using Battery = Constants::Battery;

    if(tu01SettingsNode.count("defaults") == 1) {
        const auto & nDefaults = tu01SettingsNode.at("defaults");

        if(nDefaults.count("small-crush") == 1) {
            const auto & nScDefaults = nDefaults.at("small-crush");

            tu01DefaultTests[Battery::TU01_SMALLCRUSH] =
                    parseTestConstants(valueOrDefault(nScDefaults , "tests" , json::array_t()));
            if(nScDefaults.count("repetitions"))
                tu01DefaultReps[Battery::TU01_SMALLCRUSH] = nScDefaults.at("repetitions");
        }
        if(nDefaults.count("crush") == 1) {
            const auto & nCDefaults = nDefaults.at("crush");

            tu01DefaultTests[Battery::TU01_CRUSH] =
                    parseTestConstants(valueOrDefault(nCDefaults , "tests" , json::array_t()));
            if(nCDefaults.count("repetitions"))
                tu01DefaultReps[Battery::TU01_CRUSH] = nCDefaults.at("repetitions");
        }
        if(nDefaults.count("big-crush") == 1) {
            const auto & nBcDefaults = nDefaults.at("big-crush");

            tu01DefaultTests[Battery::TU01_BIGCRUSH] =
                    parseTestConstants(valueOrDefault(nBcDefaults , "tests" , json::array_t()));
            if(nBcDefaults.count("repetitions"))
                tu01DefaultReps[Battery::TU01_BIGCRUSH] = nBcDefaults.at("repetitions");
        }
        if(nDefaults.count("rabbit") == 1) {
            const auto & nRabDefaults = nDefaults.at("rabbit");

            tu01DefaultTests[Battery::TU01_RABBIT] =
                    parseTestConstants(valueOrDefault(nRabDefaults , "tests" , json::array_t()));
            if(nRabDefaults.count("repetitions"))
                tu01DefaultReps[Battery::TU01_RABBIT] = nRabDefaults.at("repetitions");
            tu01DefaultBitNB[Battery::TU01_RABBIT] =
                    valueOrDefault(nRabDefaults , "bit-nb" , std::string());
        }
        if(nDefaults.count("alphabit") == 1) {
            const auto & nAbDefaults = nDefaults.at("alphabit");

            tu01DefaultTests[Battery::TU01_ALPHABIT] =
                    parseTestConstants(valueOrDefault(nAbDefaults , "tests" , json::array_t()));
            if(nAbDefaults.count("repetitions"))
                tu01DefaultReps[Battery::TU01_ALPHABIT] = nAbDefaults.at("repetitions");
            tu01DefaultBitNB[Battery::TU01_ALPHABIT] =
                    valueOrDefault(nAbDefaults , "bit-nb" , std::string());
            tu01DefaultBitR[Battery::TU01_ALPHABIT] =
                    valueOrDefault(nAbDefaults , "bit-r" , std::string());
            tu01DefaultBitS[Battery::TU01_ALPHABIT] =
                    valueOrDefault(nAbDefaults , "bit-s" , std::string());
        }
        if(nDefaults.count("block-alphabit") == 1) {
            const auto & nBAbDefaults = nDefaults.at("block-alphabit");

            tu01DefaultTests[Battery::TU01_BLOCK_ALPHABIT] =
                    parseTestConstants(valueOrDefault(nBAbDefaults , "tests" , json::array_t()));
            if(nBAbDefaults.count("repetitions"))
                tu01DefaultReps[Battery::TU01_ALPHABIT] = nBAbDefaults.at("repetitions");
            tu01DefaultBitNB[Battery::TU01_BLOCK_ALPHABIT] =
                    valueOrDefault(nBAbDefaults , "bit-nb" , std::string());
            tu01DefaultBitR[Battery::TU01_BLOCK_ALPHABIT] =
                    valueOrDefault(nBAbDefaults , "bit-r" , std::string());
            tu01DefaultBitS[Battery::TU01_BLOCK_ALPHABIT] =
                    valueOrDefault(nBAbDefaults , "bit-s" , std::string());
            tu01DefaultBitW[Battery::TU01_BLOCK_ALPHABIT] =
                    valueOrDefault(nBAbDefaults , "bit-w" , std::string());
        }
    }

    if(tu01SettingsNode.count("test-specific-settings") == 1) {
        const auto & nTestSpecific = tu01SettingsNode.at("test-specific-settings");

        if(nTestSpecific.count("small-crush") == 1) {
            const auto & nScTestSpecific = nTestSpecific.at("small-crush");

            tIntIntMap repsMap;
            std::for_each(nScTestSpecific.begin() , nScTestSpecific.end() ,
                          [&repsMap] (const json::object_t & o) {
                getKeyAndValue(o , "test" , "repetitions" , repsMap);
            });
            tu01TestReps[Battery::TU01_SMALLCRUSH] = std::move(repsMap);

            /* IMPLEMENT PARAMETERS EXTRACTION!!! */
            /*std::map<int , tStringStringMap> paramsMap;

            std::for_each(nScTestSpecific.begin() , nScTestSpecific.end() ,
                          [&paramsMap] (const json::object_t & o) {
                if(o.count("parameters") == 1) {
                    const auto & node = o.at("parameters");
                    std::for_each(node.begin() , node.end() ,
                                  [&paramsMap] (const json::object_t o) {
                        getKey
                    });
                }

            });*/

        }
        if(nTestSpecific.count("crush") == 1) {
            const auto & nCTestSpecific = nTestSpecific.at("crush");

            tIntIntMap repsMap;
            std::for_each(nCTestSpecific.begin() , nCTestSpecific.end() ,
                          [&repsMap] (const json::object_t & o) {
                getKeyAndValue(o , "test" , "repetitions" , repsMap);
            });
            tu01TestReps[Battery::TU01_CRUSH] = std::move(repsMap);
        }
        if(nTestSpecific.count("big-crush") == 1) {
            const auto & nBcTestSpecific = nTestSpecific.at("big-crush");

            tIntIntMap repsMap;
            std::for_each(nBcTestSpecific.begin() , nBcTestSpecific.end() ,
                          [&repsMap] (const json::object_t & o) {
                getKeyAndValue(o , "test" , "repetitions" , repsMap);
            });
            tu01TestReps[Battery::TU01_BIGCRUSH] = std::move(repsMap);
        }
        if(nTestSpecific.count("rabbit") == 1) {
            const auto & nRabTestSpecific = nTestSpecific.at("rabbit");

            tIntIntMap repsMap;
            std::for_each(nRabTestSpecific.begin() , nRabTestSpecific.end() ,
                          [&repsMap] (const json::object_t & o) {
                getKeyAndValue(o , "test" , "repetitions" , repsMap);
            });
            tu01TestReps[Battery::TU01_RABBIT] = std::move(repsMap);

            tIntStringMap bitNbMap;
            std::for_each(nRabTestSpecific.begin() , nRabTestSpecific.end() ,
                          [&bitNbMap] (const json::object_t & o) {
                getKeyAndValue(o , "test" , "bit-nb" , bitNbMap);
            });
            tu01TestBitNB[Battery::TU01_RABBIT] = std::move(bitNbMap);
        }
        if(nTestSpecific.count("alphabit") == 1) {
            const auto & nAlTestSpecific = nTestSpecific.at("alphabit");

            tIntIntMap repsMap;
            std::for_each(nAlTestSpecific.begin() , nAlTestSpecific.end() ,
                          [&repsMap] (const json::object_t & o) {
                getKeyAndValue(o , "test" , "repetitions" , repsMap);
            });
            tu01TestReps[Battery::TU01_ALPHABIT] = std::move(repsMap);

            tIntStringMap bitNbMap;
            std::for_each(nAlTestSpecific.begin() , nAlTestSpecific.end() ,
                          [&bitNbMap] (const json::object_t & o) {
                getKeyAndValue(o , "test" , "bit-nb" , bitNbMap);
            });
            tu01TestBitNB[Battery::TU01_ALPHABIT] = std::move(bitNbMap);

            tIntStringMap bitRMap;
            std::for_each(nAlTestSpecific.begin() , nAlTestSpecific.end() ,
                          [&bitRMap] (const json::object_t & o) {
               getKeyAndValue(o , "test" , "bit-r" , bitRMap);
            });
            tu01TestBitR[Battery::TU01_ALPHABIT] = std::move(bitRMap);

            tIntStringMap bitSMap;
            std::for_each(nAlTestSpecific.begin() , nAlTestSpecific.end() ,
                          [&bitSMap] (const json::object_t & o) {
                getKeyAndValue(o , "test" , "bit-s" , bitSMap);
            });
            tu01TestBitS[Battery::TU01_ALPHABIT] = std::move(bitSMap);
        }
        if(nTestSpecific.count("block-alphabit") == 1) {
            const auto & nBAlTestSpecific = nTestSpecific.at("block-alphabit");

            tIntIntMap repsMap;
            std::for_each(nBAlTestSpecific.begin() , nBAlTestSpecific.end() ,
                          [&repsMap] (const json::object_t & o) {
                getKeyAndValue(o , "test" , "repetitions" , repsMap);
            });
            tu01TestReps[Battery::TU01_BLOCK_ALPHABIT] = std::move(repsMap);

            tIntStringMap bitNbMap;
            std::for_each(nBAlTestSpecific.begin() , nBAlTestSpecific.end() ,
                          [&bitNbMap] (const json::object_t & o) {
                getKeyAndValue(o , "test" , "bit-nb" , bitNbMap);
            });
            tu01TestBitNB[Battery::TU01_BLOCK_ALPHABIT] = std::move(bitNbMap);

            tIntStringMap bitRMap;
            std::for_each(nBAlTestSpecific.begin() , nBAlTestSpecific.end() ,
                          [&bitRMap] (const json::object_t & o) {
               getKeyAndValue(o , "test" , "bit-r" , bitRMap);
            });
            tu01TestBitR[Battery::TU01_BLOCK_ALPHABIT] = std::move(bitRMap);

            tIntStringMap bitSMap;
            std::for_each(nBAlTestSpecific.begin() , nBAlTestSpecific.end() ,
                          [&bitSMap] (const json::object_t & o) {
                getKeyAndValue(o , "test" , "bit-s" , bitSMap);
            });
            tu01TestBitS[Battery::TU01_BLOCK_ALPHABIT] = std::move(bitSMap);

            tIntStringMap bitWMap;
            std::for_each(nBAlTestSpecific.begin() , nBAlTestSpecific.end() ,
                          [&bitWMap] (const json::object_t & o) {
                getKeyAndValue(o , "test" , "bit-w" , bitWMap);
            });
            tu01TestBitW[Battery::TU01_BLOCK_ALPHABIT] = std::move(bitWMap);
        }
    }
}

template <class K , class V>
void Configuration::getKeyAndValue(const json::object_t & o,
                                   const std::string & key,
                                   const std::string & value,
                                   std::map<K , V> & map) {
    if(o.count(key) == 1 && o.count(value) == 1 && map.count(o.at(key)) == 0) {
        map[o.at(key)] = o.at(value);
    }
}

template <class T>
static T Configuration::valueOrDefault(json::object_t o, const std::string & key, T && def) {
    if(o.count(key) == 1)
        return o.at(key);

    return def;
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

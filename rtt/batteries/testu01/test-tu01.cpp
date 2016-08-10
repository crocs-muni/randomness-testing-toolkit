#include "rtt/batteries/testu01/test-tu01.h"

namespace rtt {
namespace batteries {
namespace testu01 {

std::mutex outputFile_mux;

std::unique_ptr<Test> Test::getInstance(int testIndex ,
                                        const GlobalContainer & container) {
    std::unique_ptr<Test> t (new Test(testIndex , container));

    std::tie(t->logicName ,
             t->paramNames ,
             t->statisticNames) =
            TestConstants::getTu01TestData(t->battery , t->testIndex);

    /* Repetitions - mandatory */
    t->repetitions =
            t->batteryConfiguration->getTestU01BatteryTestRepetitions(t->battery ,
                                                                      t->testIndex);
    if(t->repetitions == Configuration::VALUE_INT_NOT_SET)
        t->repetitions = t->batteryConfiguration->getTestu01DefaultRepetitions(t->battery);
    if(t->repetitions == Configuration::VALUE_INT_NOT_SET)
        throw RTTException(t->objectInfo , Strings::TEST_ERR_REPS_NOT_SET);

    /* Getting params - only for Crush batteries - optional */
    if(t->battery == Constants::Battery::TU01_SMALLCRUSH ||
            t->battery == Constants::Battery::TU01_CRUSH ||
            t->battery == Constants::Battery::TU01_BIGCRUSH) {
        tParam tmp;
        for(const auto & par : t->paramNames) {
            tmp.first = par;
            tmp.second =
                    t->batteryConfiguration->getTestU01BatteryTestParams(t->battery ,
                                                                         t->testIndex ,
                                                                         par);
            if(!tmp.second.empty())
                t->params.push_back(tmp);
        }
        if(!t->params.empty() && t->params.size() != t->paramNames.size())
            throw RTTException(t->objectInfo , Strings::TEST_ERR_PARAM_INCOMPLETE);
    }

    /* Getting nb - Rabbit and (Block) Alphabit - mandatory */
    if(t->battery == Constants::Battery::TU01_RABBIT ||
            t->battery == Constants::Battery::TU01_ALPHABIT ||
            t->battery == Constants::Battery::TU01_BLOCK_ALPHABIT) {
        t->bit_nb = t->batteryConfiguration->getTestU01BatteryTestBitNB(t->battery ,
                                                                        t->testIndex);
        if(t->bit_nb.empty())
            t->bit_nb = t->batteryConfiguration->getTestU01DefaultBitNB(t->battery);
        if(t->bit_nb.empty())
            throw RTTException(t->objectInfo , Strings::TEST_ERR_BITNB_NOT_SET);
    }
    /* Getting r s - (Block) Alphabit - mandatory */
    if(t->battery == Constants::Battery::TU01_ALPHABIT ||
            t->battery == Constants::Battery::TU01_BLOCK_ALPHABIT) {
        t->bit_r = t->batteryConfiguration->getTestU01BatteryTestBitR(t->battery ,
                                                                      t->testIndex);
        if(t->bit_r.empty())
            t->bit_r = t->batteryConfiguration->getTestU01DefaultBitR(t->battery);
        if(t->bit_r.empty())
            throw RTTException(t->objectInfo , Strings::TEST_ERR_BITR_NOT_SET);

        t->bit_s = t->batteryConfiguration->getTestU01BatteryTestBitS(t->battery ,
                                                                      t->testIndex);
        if(t->bit_s.empty())
            t->bit_s = t->batteryConfiguration->getTestU01DefaultBitS(t->battery);
        if(t->bit_s.empty())
            throw RTTException(t->objectInfo , Strings::TEST_ERR_BITS_NOT_SET);
    }
    /* Getting w - Block Alphabit - optional */
    if(t->battery == Constants::Battery::TU01_BLOCK_ALPHABIT) {
        t->bit_w = t->batteryConfiguration->getTestU01BatteryTestBitW(t->battery ,
                                                                      t->testIndex);
        if(t->bit_w.empty())
            t->bit_w = t->batteryConfiguration->getTestU01DefaultBitW(t->battery);
    }
    /* Setting battery arguments and input */
    t->batteryArgs = t->createArgs();
    t->batteryInput = "";

    return t;
}

std::vector<std::string> Test::getTestUserSettings() const {
    std::stringstream rval;
    rval << "Repetitions: " << repetitions << std::endl;
    if(battery == Constants::Battery::TU01_RABBIT ||
            battery == Constants::Battery::TU01_ALPHABIT ||
            battery == Constants::Battery::TU01_BLOCK_ALPHABIT)
        rval << "Bit NB: " << bit_nb << std::endl;

    if(battery == Constants::Battery::TU01_ALPHABIT ||
            battery == Constants::Battery::TU01_BLOCK_ALPHABIT) {
        rval << "Bit R: " << bit_r << std::endl;
        rval << "Bit S: " << bit_s << std::endl;
    }

    if(battery == Constants::Battery::TU01_BLOCK_ALPHABIT &&
            !bit_w.empty()) {
        rval << "Bit W: " << bit_w << std::endl;
    }

    if(!params.empty() &&
            (battery == Constants::Battery::TU01_SMALLCRUSH ||
            battery == Constants::Battery::TU01_CRUSH ||
            battery == Constants::Battery::TU01_BIGCRUSH)) {
        for(const tParam & par : params)
            rval << par.first << " = " << par.second << std::endl;
    }

    return Utils::split(rval.str() , '\n');
}

std::vector<std::string> Test::getStatistics() const {
    return statisticNames;
}

std::vector<std::vector<std::string>> Test::getTestsParameters() const {
    if(!executed)
        throw RTTException(objectInfo , Strings::TEST_ERR_NO_EXEC_RES);

    std::vector<std::vector<std::string>> rval;
    std::string singleTestParameters;

    for(const auto & subTest : subTestsParameters) {
        for(const auto & testParam : subTest) {
            singleTestParameters.append(testParam.first);
            singleTestParameters.append(" = ");
            singleTestParameters.append(testParam.second);
            singleTestParameters.append("\n");
        }
        rval.push_back(Utils::split(singleTestParameters , '\n'));
        singleTestParameters.clear();
    }

    return rval;
}

int Test::getRepetitions() const {
    return repetitions;
}

uint Test::getSubTestCount() const {
    if(!executed)
        throw RTTException(objectInfo , Strings::TEST_ERR_NO_EXEC_RES);

    return subTestCount;
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
std::string Test::createArgs() const {
    std::stringstream arguments;
    arguments << "testu01 ";
    /* Setting battery mode */
    arguments << "-m ";
    switch(battery) {
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
        throw std::runtime_error(Strings::ERR_INVALID_BATTERY);
    }
    /* Test number option */
    arguments << "-t " << testIndex << " ";
    /* Input file option */
    arguments << "-i " << binaryDataPath << " ";
    /* Repetitions option */
    if(repetitions != 1)
        arguments << "-r " << repetitions << " ";
    /* Custom parameters option */
    if(params.size() > 0) {
        arguments << "--params ";
        for(auto i : params)
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

    return arguments.str();
}

void Test::processBatteryOutput() {
    static const std::regex RE_PVALUE {
        "p-value of test {23}: *?("
        "eps|"                            /* Just "eps" */
        "1 - eps1|"                       /* Just "1 - eps1" */
        "0\\.\\d{2,4}|"                   /* Decimal rounded from 2 to 4 digits */
        "(1 -  ?)?\\d\\.\\de-\\d{1,3}"    /* Decimal in scientific notation that can be preceeded by "1 - " */
        ") *?(\\*\\*\\*\\*\\*)?\\n"       /* Capture ending "*****" - pvalue is suspect */
    };

    auto testLog = batteryOutput.getStdOut();
    /* Extract settings must be called ASAP -
     * it sets subTestCount variable */
    extractSettingsFromLog(testLog);

    auto begin = std::sregex_iterator(testLog.begin(),
                                      testLog.end(),
                                      RE_PVALUE);
    auto end   = std::sregex_iterator();

    long pValCount = std::distance(begin , end);
    if(pValCount == 0) {
        logger->warn(objectInfo + Strings::TEST_ERR_NO_PVALS_EXTRACTED);
        return;
    }

    /*if(pValCount % repetitions != 0) {
        logger->warn(objectInfo + Strings::TEST_ERR_PVALS_BAD_COUNT);
        return;
    }
    statCount = pValCount / repetitions;*/
    if(pValCount % (repetitions * subTestCount) != 0) {
        logger->warn(objectInfo + Strings::TEST_ERR_PVALS_BAD_COUNT);
        return;
    }
    statCount = pValCount / (repetitions * subTestCount);

    if(statCount != statisticNames.size()) {
        /* So this normally doesn't happen but(!) some tests have variable
         * output based on their parameters. For example scomp_LempevZiv has
         * different output when executed from Crush battery and Rabbit battery.
         * In that case, say that to user and use unknown statistics names. */
        logger->warn(objectInfo + Strings::TEST_ERR_UNKNOWN_STATISTICS);
        std::vector<std::string> newStatNames;
        for(size_t i = 1 ; i <= statCount ; ++i)
            newStatNames.push_back("Unknown " + Utils::itostr(i));
        statisticNames = std::move(newStatNames);
    }

    tTestPvals pValues;

    for( ; begin != end ; ) {
        for(uint i = 0 ; i < statCount ; ++i) {
            std::smatch match = *begin;
            try {
                pValues.push_back(
                            convertStringToDouble(match[1].str() , match[2].str()));
            } catch (std::runtime_error ex) {
                logger->warn(objectInfo + Strings::TEST_ERR_EXCEPTION_DURING_THREAD + ex.what());
                results.clear();
                return;
            }

            ++begin;
        }
        results.push_back(std::move(pValues));
        pValues.clear();
    }
}

void Test::extractSettingsFromLog(const std::string & testLog) {
    /* Find out how many tests were executed. Specific test name is not used here
     * since sometimes another test is executed and only its statistics are
     * processed by main test. Logic test names then doesn't match
     * and regex with specific test name would detect nothing. */
    std::regex RE_TEST_HEADER { logicName + " test:" };
    //const static std::regex RE_TEST_HEADER { "\\w+? test:" };
    subTestCount = std::distance(
            std::sregex_iterator(testLog.begin() , testLog.end() , RE_TEST_HEADER),
            std::sregex_iterator()
    ) / repetitions;

    if(subTestCount == 0) {
        logger->warn(objectInfo + ": No settings extracted. "
                                  "Subtest detection failed.");
        subTestCount = 1;
        return;
    }

    /* Constructing regex for capturing parameter values */
    std::string regexString;
    for(uint i = 0 ; i < paramNames.size() ; ++i) {
        regexString.append("\\s+?" + paramNames.at(i) + " +?= +?([^\\s,]+?)");
        if(i + 1 != paramNames.size()) {
            regexString.append(",");
        } else {
            regexString.append("\\s");
        }
    }
    /* Extracting values of settings from log */
    std::regex RE_PAR_VALUE_CAP { regexString };
    auto begin = std::sregex_iterator(testLog.begin() ,
                                      testLog.end() ,
                                      RE_PAR_VALUE_CAP);
    auto end   = std::sregex_iterator();
    if(std::distance(begin , end) != (subTestCount * repetitions)) {
        logger->warn(objectInfo + ": No settings extracted. "
                                  "Parameter matching failed.");
        return;
    }
    for( ; begin != end ; ++begin) {
        std::smatch match = *begin;
        tParam singleParameter;
        std::vector<tParam> singleTestSettings;
        for(uint i = 0 ; i < paramNames.size() ; ++i) {
            singleParameter.first = paramNames.at(i);
            singleParameter.second = match[i + 1].str();
            singleTestSettings.push_back(singleParameter);
        }
        subTestsParameters.push_back(singleTestSettings);
    }
    /* Extracting w from logs - Only in Block Alphabit battery. */
    if(battery == Constants::Battery::TU01_BLOCK_ALPHABIT) {
        std::regex RE_W_VALUE_CAP {
            "\\sw = +?([1-9]+?)\\s"
        };
        auto begin = std::sregex_iterator(testLog.begin() ,
                                          testLog.end() ,
                                          RE_W_VALUE_CAP);
        auto end   = std::sregex_iterator();
        if(std::distance(begin , end) != (subTestCount * repetitions)) {
            logger->warn(objectInfo + ": Settings extraction error. "
                                      "Bit parameter w matching failed.");
            return;
        }
        for(uint i = 0 ; begin != end ; ++begin, ++i) {
            std::smatch match = *begin;
            tParam tmp;
            tmp.first = "w";
            tmp.second = match[1].str();
            subTestsParameters.at(i).push_back(tmp);
        }
    }
}

double Test::convertStringToDouble(const std::string & num,
                                   const std::string & oneMinus) {
    if(num == "eps") {
        return 1.0E-300;
    } else if(num == "1 - eps1") {
        return 1 - 1.0E-15;
    } else if(num.find('e') == std::string::npos) {
        return Utils::strtod(num);
    } else {
        std::string tmp = num;
        tmp.erase(0 , oneMinus.length());
        std::vector<std::string> splitted = Utils::split(tmp , 'e');
        double base = Utils::strtod(splitted.at(0));
        double exp = Utils::strtod(splitted.at(1));
        base *= pow(10.0 , exp);
        if(oneMinus.empty()) {
            return base;
        } else {
            return 1 - base;
        }
    }
}

} // namespace testu01
} // namespace batteries
} // namespace rtt


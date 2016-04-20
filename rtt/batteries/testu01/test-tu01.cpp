#include "rtt/batteries/testu01/test-tu01.h"

namespace rtt {
namespace batteries {
namespace testu01 {

std::unique_ptr<Test> Test::getInstance(int testIndex ,
                                        const GlobalContainer & container) {
    std::unique_ptr<Test> t (new Test(testIndex , container));

    std::tie(t->logicName ,
             t->paramNames ,
             t->statisticNames) =
            TestConstants::getTu01TestData(t->battery , t->testIndex);

    /* Repetitions */
    t->repetitions =
            t->batteryConfiguration->getTestU01BatteryTestRepetitions(t->battery ,
                                                                      t->testIndex);
    if(t->repetitions == Configuration::VALUE_INT_NOT_SET)
        t->repetitions = t->batteryConfiguration->getTestu01DefaultRepetitions();
    if(t->repetitions == Configuration::VALUE_INT_NOT_SET)
        throw RTTException(t->objectInfo , "repetitions not set");

    /* Getting params - only for Crush batteries */
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
            throw RTTException(t->objectInfo , "incomplete parameter settings");
    }

    /* Getting nb - Rabbit and Alphabit */
    if(t->battery == Constants::Battery::TU01_RABBIT ||
            t->battery == Constants::Battery::TU01_ALPHABIT) {
        t->bit_nb = t->batteryConfiguration->getTestU01BatteryTestBitNB(t->battery ,
                                                                        t->testIndex);
        if(t->bit_nb.empty())
            t->bit_nb = t->batteryConfiguration->getTestu01DefaultBitNB();
        if(t->bit_nb.empty())
            throw RTTException(t->objectInfo , "bit_nb option not set");
    }
    /* Getting r s - Alphabit */
    if(t->battery == Constants::Battery::TU01_ALPHABIT) {
        t->bit_r = t->batteryConfiguration->getTestU01BatteryTestBitR(t->battery ,
                                                                      t->testIndex);
        if(t->bit_r.empty())
            t->bit_r = t->batteryConfiguration->getTestu01DefaultBitR();
        if(t->bit_r.empty())
            throw RTTException(t->objectInfo , "bit_r option not set");

        t->bit_s = t->batteryConfiguration->getTestU01BatteryTestBitS(t->battery ,
                                                                      t->testIndex);
        if(t->bit_s.empty())
            t->bit_s = t->batteryConfiguration->getTestu01DefaultBitS();
        if(t->bit_s.empty())
            throw RTTException(t->objectInfo , "bit_s option not set");
    }
    return t;
}

void Test::execute() {
    /* This method is turned into thread.
     * Will deadlock if run without main thread. */

    testLog = TestRunner::executeBinary(executablePath ,
                                        createArgs());

    extractPvalues();
    executed = true;
}

std::vector<std::string> Test::getParameters() const {
    std::stringstream rval;
    rval << "Repetitions: " << repetitions << std::endl;
    if(battery == Constants::Battery::TU01_RABBIT ||
            battery == Constants::Battery::TU01_ALPHABIT)
        rval << "Bit NB: " << bit_nb << std::endl;

    if(battery == Constants::Battery::TU01_ALPHABIT) {
        rval << "Bit R: " << bit_r << std::endl;
        rval << "Bit S: " << bit_s << std::endl;
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
    default:
        throw std::runtime_error("unknown battery");
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
        arguments << "--bit_s " << bit_s;

    return arguments.str();
}

void Test::extractPvalues() {
    static const std::regex RE_PVALUE {
        "p-value of test {23}: *?("
        "eps|"                            /* Just "eps" */
        "1 - eps1|"                       /* Just "1 - eps1" */
        "0\\.\\d{2,4}|"                   /* Decimal rounded from 2 to  digits */
        "(1 -  ?)?\\d\\.\\de-\\d{1,3}"    /* Decimal in scientific notation that can be preceeded by "1 - " */
        ") *?(\\*\\*\\*\\*\\*)?\\n"       /* Capture ending "*****" - pvalue is suspect */
    };

    auto begin = std::sregex_iterator(testLog.begin() , testLog.end() , RE_PVALUE);
    auto end = std::sregex_iterator();

    int pValCount = std::distance(begin , end);
    if(pValCount == 0) {
        std::cout << "[WARNING] No pValues were extracted" << std::endl;
        return;
    }

    if(pValCount % repetitions != 0) {
        std::cout << "[WARNING] " << objectInfo << ": p-values can't be extracted from log. "
                     "Number of p-values present is not divisible by "
                                                   "number of repetitions per test." << std::endl;
        return;
    }
    statCount = pValCount / repetitions;
    if(statCount != statisticNames.size()) {
        /* So this normally doesn't happen but(!) some tests have variable
         * output based on their parameters. For example scomp_LempevZiv has
         * different output when executed from Crush battery and Rabbit battery.
         * In that case, say that to user and use unknown statistics names. */
        std::cout << "[WARNING] Number of statistics extracted from log differs from default number."
                     " Inspect the log for correct statistics names." << std::endl;
        std::vector<std::string> newStatNames;
        for(size_t i = 1 ; i <= statCount ; ++i)
            newStatNames.push_back("Unknown " + Utils::itostr(i));
        statisticNames = std::move(newStatNames);
    }

    tTestPvals pValues;

    for(; begin != end ;) {
        for(uint i = 0 ; i < statCount ; ++i) {
            std::smatch match = *begin;
            try {
                pValues.push_back(
                            convertStringToDouble(match[1].str() , match[2].str()));
            } catch (std::runtime_error ex) {
                std::cout << "[WARNING] " << objectInfo << ": error happened: " << ex.what() <<
                             " test won't be further processed." << std::endl;
                results.clear();
                return;
            }

            ++begin;
        }
        results.push_back(std::move(pValues));
        pValues.clear();
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


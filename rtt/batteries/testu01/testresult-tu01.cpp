#include "testresult-tu01.h"

namespace rtt {
namespace batteries {
namespace testu01 {

const static std::regex RE_SUBTEST (
      "\nGenerator providing data from binary file.\n"
      "([^]*?)"  /* This will capture output of one subtest */
      "(?=\nGenerator providing data from binary file.\n|$)"
);

const static std::regex RE_PVALUES (
      "p-value of test {23}: *?("
      "eps|"                            /* Just "eps" */
      "1 - eps1|"                       /* Just "1 - eps1" */
      "0\\.\\d{2,4}|"                   /* Decimal rounded from 2 to 4 digits */
      "(1 -  ?)?\\d\\.\\de-\\d{1,3}"    /* Decimal in scientific notation that can be preceeded by "1 - " */
      ") *?(\\*\\*\\*\\*\\*)?\\n"       /* Capture ending "*****" - pvalue is suspect */
);

static const std::regex RE_W_PARAM (
      "\\sw = +?([1-9]+?)\\s"
);

const static std::regex RE_PVALUES_1LVL (
      "\n=== First level p-values/statistics of the test ===\n"
      "([^]*?)" /* This will capture printed p-values in the log */
      "\n===================================================\n"
);

std::unique_ptr<TestResult> TestResult::getInstance(
        const std::vector<ITest *> & tests) {
    if(tests.empty())
        raiseBugException("empty tests");

    std::unique_ptr<TestResult> r (new TestResult(
                                       tests.at(0)->getLogger(),
                                       tests.at(0)->getLogicName()));


    auto endIt = std::sregex_iterator();
    std::vector<result::SubTestResult> tmpSubTestResults;
    std::vector<result::Statistic> tmpStatistics;
    std::vector<std::pair<std::string, std::string>> tmpParamVec;
    std::vector<double> tmpPValuesVec;

    r->battery = tests.at(0)->getBatteryArg();

    /* Single test processing */
    for(const ITest * test : tests) {
        /* Single variant processing */
        for(IVariant * variant : test->getVariants()) {
            testu01::Variant * tu01Var =
                    dynamic_cast<Variant *>(variant);
            r->objectInfo = tu01Var->getObjectInfo();

            /* Split log into subtests */
            std::string variantLog = tu01Var->getBatteryOutput().getStdOut();

            auto subTestIt = std::sregex_iterator(
                                 variantLog.begin(),
                                 variantLog.end(),
                                 RE_SUBTEST);

            /* Single subtest processing */
            for(; subTestIt != endIt ; ++subTestIt) {
                std::smatch match = *subTestIt;
                std::string subTestLog = match[1].str();

                tmpStatistics = r->extractStatistics(
                                   subTestLog,
                                   tu01Var->getStatisticNames());

                /* Test settings extraction */
                tmpParamVec = r->extractTestParameters(
                                  subTestLog,
                                  tu01Var->getExtractableParamNames());

                /* P-values extraction */
                tmpPValuesVec = r->extractPValues(subTestLog);

                /* Creation of a result of the subtest */
                auto tmpSubTestRes = result::SubTestResult::getInstance(
                                         std::move(tmpStatistics),
                                         std::move(tmpPValuesVec));

                /* Additional subtest specifics */
                tmpSubTestRes.setTestParameters(
                            std::move(tmpParamVec));

                /* Add subtest result to collection of results */
                tmpSubTestResults.push_back(std::move(tmpSubTestRes));
            }
            r->varRes.push_back(result::VariantResult::getInstance(
                                    tmpSubTestResults,
                                    tu01Var->getUserSettings(),
                                    tu01Var->getBatteryOutput()));
            tmpSubTestResults.clear();
        }
    }
    return r;
}

std::vector<result::Statistic> TestResult::extractStatistics(
        const std::string & testLog, std::vector<std::string> statNames) {
    std::vector<result::Statistic> rval;

    auto pValIt = std::sregex_iterator(
                      testLog.begin(),
                      testLog.end(),
                      RE_PVALUES);
    auto endIt = std::sregex_iterator();
    if(static_cast<size_t>(std::distance(pValIt, endIt)) != statNames.size()) {
        statNames.clear();
        for(uint i = 0 ; i < std::distance(pValIt , endIt) ; ++i)
            statNames.push_back("Unknown " + Utils::itostr(i));
        logger->warn(objectInfo +
                     Strings::TEST_ERR_UNKNOWN_STATISTICS);
    }
    for(uint i = 0 ; pValIt != endIt ; ++i , ++pValIt) {
        std::smatch match = *pValIt;
        double pVal = convertStringToDouble(match[1].str(),
                                            match[2].str());
        rval.push_back(result::Statistic::getInstance(statNames.at(i), pVal));
    }
    return rval;
}

double TestResult::convertStringToDouble(const std::string & num,
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
        std::vector<std::string> splitted =
                Utils::split(tmp , 'e');
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

std::vector<std::pair<std::string, std::string>> TestResult::extractTestParameters(
        const std::string & testLog,
        std::vector<std::string> paramNames) {
    std::vector<std::pair<std::string, std::string>> rval;
    std::regex RE_PARAM = buildParamRegex(paramNames);
    auto paramIt = std::sregex_iterator(testLog.begin(),
                                        testLog.end(),
                                        RE_PARAM);
    auto endIt = std::sregex_iterator();
    if(std::distance(paramIt , endIt) != 1)
        throw RTTException(objectInfo,
                           "parameter extraction failed");
    std::smatch paramMatch = *paramIt;
    for(uint i = 0 ; i < paramNames.size() ; ++i) {
        rval.push_back({paramNames.at(i), paramMatch[i + 1].str()});
    }
    /* Extracting w in Block Alphabit */
    if(battery.getBatteryId() == Constants::BatteryID::TU01_BLOCK_ALPHABIT) {

        auto wParamIt = std::sregex_iterator(
                            testLog.begin(),
                            testLog.end(),
                            RE_W_PARAM);
        if(std::distance(wParamIt, endIt) != 1) {
            throw RTTException(objectInfo,
                               "extraction of parameter \"w\" failed");
        }
        std::smatch wMatch = *wParamIt;
        //rval.push_back("w = " + wMatch[1].str());
        rval.push_back({"w", wMatch[1].str()});
    }

    return rval;
}

std::vector<double> TestResult::extractPValues(const std::string & testLog) {

    std::smatch m;
    std::regex_search(testLog, m, RE_PVALUES_1LVL);
    if(m.empty())
        return {};

    auto pValsSplit = Utils::split(m[1], '\n');
    std::vector<double> rval;
    rval.reserve(pValsSplit.size());

    for(auto pVal : pValsSplit)
        rval.push_back(Utils::strtod(pVal));

    return rval;
}

std::regex TestResult::buildParamRegex(
        std::vector<std::string> paramNames) {
    std::stringstream rval;
    for(uint i = 0 ; i < paramNames.size() ; ++i) {
        rval << "\\s+?" << paramNames.at(i) << " +?= +?([^\\s,]+?)";
        if(i + 1 != paramNames.size()) {
            rval << ",";
        } else {
            rval << "\\s";
        }
    }
    return std::regex(rval.str());
}


} // namespace testu01
} // namespace batteries
} // namespace rtt

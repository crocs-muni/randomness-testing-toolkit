#include "testresult-sts.h"

#include "libs/cephes/cephes.h"

namespace rtt {
namespace batteries {
namespace niststs {

std::unique_ptr<TestResult> TestResult::getInstance(
        const std::vector<ITest *> & tests) {
    if(tests.empty())
        raiseBugException("empty tests");

    std::unique_ptr<TestResult> r (new TestResult(
                                       tests.at(0)->getLogger(),
                                       tests.at(0)->getLogicName()));

    std::vector<result::SubTestResult> tmpSubTestResults;
    std::vector<result::Statistic> tmpStatistics;


    /* Single test processing */
    for(const ITest * test : tests) {
        /* Single variant processing */
        for(IVariant * variant : test->getVariants()) {
            Variant * stsVar =
                    dynamic_cast<Variant *>(variant);
            r->objectInfo = stsVar->getObjectInfo();
            auto variantPVals = getVariantPValues(stsVar);

            /* Single subtest processing */
            tmpSubTestResults.reserve(variantPVals.size());
            for(const std::vector<double> & subTestPVals : variantPVals) {
                if(subTestPVals.empty()) {
                    r->logger->warn(r->objectInfo + 
                                    ": no p-values extracted in subtest");
                    continue;
                }
                tmpStatistics.push_back(result::Statistic::getInstance(
                                            "Chi-Square",
                                            chi2_stat(subTestPVals)));
                tmpSubTestResults.push_back(result::SubTestResult::getInstance(
                                                tmpStatistics, subTestPVals));
                tmpStatistics.clear();
            }
            r->varRes.push_back(result::VariantResult::getInstance(
                                    tmpSubTestResults,
                                    stsVar->getUserSettings(),
                                    stsVar->getBatteryOutput()));
            tmpSubTestResults.clear();
        }
    }
    r->evaluateSetPassed();
    return r;
}

static const std::regex RE_RND_EXC_PVALUES (
      ".*x = -4.*p_value = ([0|1]?\\.[0-9]+?)\\n"
      ".*x = -3.*p_value = ([0|1]?\\.[0-9]+?)\\n"
      ".*x = -2.*p_value = ([0|1]?\\.[0-9]+?)\\n"
      ".*x = -1.*p_value = ([0|1]?\\.[0-9]+?)\\n"
      ".*x =  1.*p_value = ([0|1]?\\.[0-9]+?)\\n"
      ".*x =  2.*p_value = ([0|1]?\\.[0-9]+?)\\n"
      ".*x =  3.*p_value = ([0|1]?\\.[0-9]+?)\\n"
      ".*x =  4.*p_value = ([0|1]?\\.[0-9]+?)\\n"
);

static const std::regex RE_RND_EXC_VAR_PVALUES(
      ".*\\(x = -9\\).*p-value = ([0|1]?\\.[0-9]+?)\\n"
      ".*\\(x = -8\\).*p-value = ([0|1]?\\.[0-9]+?)\\n"
      ".*\\(x = -7\\).*p-value = ([0|1]?\\.[0-9]+?)\\n"
      ".*\\(x = -6\\).*p-value = ([0|1]?\\.[0-9]+?)\\n"
      ".*\\(x = -5\\).*p-value = ([0|1]?\\.[0-9]+?)\\n"
      ".*\\(x = -4\\).*p-value = ([0|1]?\\.[0-9]+?)\\n"
      ".*\\(x = -3\\).*p-value = ([0|1]?\\.[0-9]+?)\\n"
      ".*\\(x = -2\\).*p-value = ([0|1]?\\.[0-9]+?)\\n"
      ".*\\(x = -1\\).*p-value = ([0|1]?\\.[0-9]+?)\\n"
      ".*\\(x =  1\\).*p-value = ([0|1]?\\.[0-9]+?)\\n"
      ".*\\(x =  2\\).*p-value = ([0|1]?\\.[0-9]+?)\\n"
      ".*\\(x =  3\\).*p-value = ([0|1]?\\.[0-9]+?)\\n"
      ".*\\(x =  4\\).*p-value = ([0|1]?\\.[0-9]+?)\\n"
      ".*\\(x =  5\\).*p-value = ([0|1]?\\.[0-9]+?)\\n"
      ".*\\(x =  6\\).*p-value = ([0|1]?\\.[0-9]+?)\\n"
      ".*\\(x =  7\\).*p-value = ([0|1]?\\.[0-9]+?)\\n"
      ".*\\(x =  8\\).*p-value = ([0|1]?\\.[0-9]+?)\\n"
      ".*\\(x =  9\\).*p-value = ([0|1]?\\.[0-9]+?)\\n"
);

std::vector<std::vector<double>> TestResult::getVariantPValues(
        Variant * variant) {
    if(variant->getTestId() == 12) {
        /* Random excursion test */
        uint subTestCount = 8; // THIS IS IMPORTANT!!!


        std::vector<std::vector<double>> rval(subTestCount);
        auto testLog = variant->getBatteryOutput().getStdOut();
        auto subTestIt = std::sregex_iterator(
                             testLog.begin(), testLog.end(),
                             RE_RND_EXC_PVALUES);
        auto endIt = std::sregex_iterator();

        for(; subTestIt != endIt ; ++subTestIt) {
            std::smatch match = *subTestIt;
            for(uint i = 1 ; i <= subTestCount ; ++i)
                rval.at(i - 1).push_back(Utils::strtod(match[i].str()));
        }
        return rval;
    } else if(variant->getTestId() == 13) {
        /* Random excursion variant */
        uint subTestCount = 18; // THIS IS ALSO IMPORTANT!!!


        std::vector<std::vector<double>> rval(subTestCount);
        auto testLog = variant->getBatteryOutput().getStdOut();
        auto subTestIt = std::sregex_iterator(
                             testLog.begin(), testLog.end(),
                             RE_RND_EXC_VAR_PVALUES);
        auto endIt = std::sregex_iterator();

        for(; subTestIt != endIt ; ++subTestIt) {
            std::smatch match = *subTestIt;
            for(uint i = 1 ; i <= subTestCount ; ++i) {
                rval.at(i - 1).push_back(Utils::strtod(match[i].str()));
            }
        }
        return rval;
    } else {
        /* The rest of tests */
        std::vector<std::vector<double>> rval;
        std::vector<double> pValVec;
        std::vector<std::string> pValVecStr;

        for(const std::string & pValFile : variant->getPValueFiles()) {
            pValVecStr = Utils::split(pValFile, '\n');

            for(const std::string & pVal : pValVecStr)
                pValVec.push_back(Utils::strtod(pVal));

            rval.push_back(std::move(pValVec));
            pValVec.clear();
        }
        return rval;
    }
}

/* Following code is taken from NIST STS source code */
/* Used for calculation of Chi2 statistic */
double TestResult::chi2_stat(std::vector<double> pvals) {
    int streamCount = pvals.size();
    int j, pos , expCount;
    double chi2 , uniformity;

    std::vector<int> freqPerBin(10 , 0);

    std::sort(pvals.begin() , pvals.end());
    for(j = 0 ; j <  streamCount ; ++j) {
        pos = (int)floor(pvals.at(j)*10);
        if(pos == 10)
            pos--;
        ++freqPerBin[pos];
    }
    chi2 = 0.0;
    expCount =  streamCount/10;
    if(expCount == 0) {
        uniformity = 0.0;
    } else {
        for (j = 0 ; j < 10 ; ++j)
            chi2 += pow(freqPerBin[j]-expCount, 2)/expCount;

        uniformity = Cephes::cephes_igamc(9.0/2.0, chi2/2.0);
    }
    return uniformity;
}

} // namespace niststs
} // namespace batteries
} // namespace rtt

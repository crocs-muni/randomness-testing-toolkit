#include "rtt/batteries/niststs/battery-sts.h"

#include "rtt/batteries/iresult-batt.h"

namespace rtt {
namespace batteries {
namespace niststs {

std::unique_ptr<Battery> Battery::getInstance(const GlobalContainer & container) {
    std::unique_ptr<Battery> b (new Battery(container));
    return b;
}

void Battery::processStoredResults() {
    if(!executed)
        throw RTTException(objectInfo , Strings::BATT_ERR_NO_EXEC_PROC);

    for(const auto & test : tests) {
        std::vector<ITest *> tsts = { test.get() };
        std::shared_ptr<IResult> res = IResult::getInstance(tsts);
        res->writeResults(storage.get(), 6);
    }
    storage->finalizeReport();

//    if(!executed)
//        throw RTTException(objectInfo , Strings::BATT_ERR_NO_EXEC_PROC);

//    logger->info(objectInfo + Strings::BATT_INFO_PROCESSING_STARTED);

//    /* Result storage */
//    for(auto & test : tests) {
//        storage->addNewTest(test->getLogicName());
//        storage->setUserSettings(test->getTestUserSettings());

//        /* Writing issues */
//        storage->setRuntimeIssues(test->getBatteryStdErr(),
//                                  test->getBatteryErrors(),
//                                  test->getBatteryWarnings());

//        std::vector<tTestPvals> results = test->getResults();
//        /* There are always two statistics in NIST STS, namely
//         * Chi-square and Proportion */
//        std::vector<std::string> statistics = test->getStatistics();
//        bool propStatFailed;
//        std::string propStat;

//        if(results.size() == 1) { /* Single test */
//            storage->addStatisticResult(statistics.at(0) ,
//                                        chi2_stat(results.at(0)) , 6);
//            propStat = proportionStat(results.at(0) , &propStatFailed);
//            storage->addStatisticResult(statistics.at(1) , propStat ,
//                                        propStatFailed);
//            storage->addPValues(results.at(0) , 6);
//        } else { /* Multiple subtests */
//            for(const auto & result : results) {
//                storage->addSubTest();
//                storage->addStatisticResult(statistics.at(0) ,
//                                            chi2_stat(result) , 6);
//                propStat = proportionStat(result , &propStatFailed);
//                storage->addStatisticResult(statistics.at(1) , propStat ,
//                                            propStatFailed);
//                storage->addPValues(result , 6);
//                storage->finalizeSubTest();
//            }
//        }
//        storage->finalizeTest();
//    }
//    storage->finalizeReport();
//    logger->info(objectInfo + Strings::BATT_INFO_PROCESSING_COMPLETE);
}

std::string Battery::proportionStat(tTestPvals pvals , bool * failed) {
    int passCount = 0;
    double p_hat = 1.0 - Constants::MATH_ALPHA;
    double proportion_threshold_max =
            (p_hat + 3.0 * sqrt((p_hat*Constants::MATH_ALPHA)/pvals.size())) * pvals.size();
    double proportion_threshold_min =
            (p_hat - 3.0 * sqrt((p_hat*Constants::MATH_ALPHA)/pvals.size())) * pvals.size();
    for(const auto & val : pvals) {
        if(val >= Constants::MATH_ALPHA)
            ++passCount;
    }
    if(passCount < proportion_threshold_min || passCount > proportion_threshold_max)
        *failed = true;
    else
        *failed = false;

    return {Utils::itostr(passCount) + "/" + Utils::itostr(pvals.size())};
}

/* Following code is taken from NIST STS source code */
/* Used for calculation of Chi2 statistic */
double Battery::chi2_stat(tTestPvals pvals) {
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

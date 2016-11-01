#ifndef RTT_STORAGE_ISTORAGE_H
#define RTT_STORAGE_ISTORAGE_H

#include <string>
#include <vector>

#include "rtt/globalcontainer.h"
#include "rtt/batteries/itestresult-batt.h"

namespace rtt {
namespace storage {

class IStorage {
public:
    static std::unique_ptr<IStorage> getInstance(const GlobalContainer & container);

    virtual ~IStorage() {}

    virtual void writeResults(const std::vector<batteries::ITestResult *> & testResults) = 0;

//    virtual void addNewTest(const std::string & testName) = 0;
//    virtual void finalizeTest() = 0;

//    virtual void addVariant() = 0;
//    virtual void finalizeVariant() = 0;

//    virtual void addSubTest() = 0;
//    virtual void finalizeSubTest() = 0;

//    virtual void setTestResult(bool passed) = 0;

//    virtual void setTestPartialAlpha(double alpha) = 0;

//    virtual void setUserSettings(const std::vector<std::string> & options) = 0;

//    virtual void setTestParameters(const std::vector<std::string> & parameters) = 0;

//    virtual void setWarningMessages(const std::vector<std::string> & warnings) = 0;

//    virtual void setErrorMessages(const std::vector<std::string> & errors) = 0;

//    virtual void setStdErrMessages(const std::vector<std::string> & stderr) = 0;

//    virtual void addStatisticResult(
//            const std::string & statName ,
//            double value , int precision, bool passed) = 0;

//    virtual void addPValues(const std::vector<double> & pvals , int precision = 6) = 0;

//    virtual void finalizeReport() = 0;
};

} // namespace storage
} // namespace rtt

#endif // RTT_STORAGE_ISTORAGE_H

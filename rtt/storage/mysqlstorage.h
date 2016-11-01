#ifndef RTT_STORAGE_MYSQLSTORAGE_H
#define RTT_STORAGE_MYSQLSTORAGE_H

#include <memory>
#include <cstdint>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>

#include "rtt/globalcontainer.h"
#include "rtt/storage/istorage.h"

namespace rtt {
namespace storage {

class MySQLStorage : public IStorage {
public:
    static std::unique_ptr<MySQLStorage> getInstance(const GlobalContainer & container);

    void writeResults(const std::vector<batteries::ITestResult *> & testResults);

private:
    /*
    =================
    *** Variables ***
    =================
    */
    static const std::string objectInfo;
    /* Pointers to global objects */
    CliOptions * cliOptions;
    ToolkitSettings * toolkitSettings;

    time_t creationTime;
    Constants::Battery battId;

    sql::Driver * driver;
    std::unique_ptr<sql::Connection> conn;
    std::uint64_t dbBatteryId = 0;
    std::uint64_t currDbTestId = 0;
    std::uint64_t currDbVariantId = 0;
    std::uint64_t currDbSubtestId = 0;
    int currTestIdx = 0;
    int currSubtestIdx = 0;
    int currVariantIdx = 0;
    int totalTestCount = 0;
    int passedTestCount = 0;

    /*
    ===============
    *** Methods ***
    ===============
    */
    MySQLStorage() {}

    void addNewTest(const std::string & testName);
    void finalizeTest();

    void addVariant();
    void finalizeVariant();

    void addSubTest();
    void finalizeSubTest();

    void setTestResult(bool passed);

    void setTestPartialAlpha(double alpha);

    void setUserSettings(const std::vector<std::string> & options);

    void setTestParameters(const std::vector<std::string> & options);

    void setWarningMessages(const std::vector<std::string> & warnings);

    void setErrorMessages(const std::vector<std::string> & errors);

    void setStdErrMessages(const std::vector<std::string> & stderr);

    void addStatisticResult(
            const std::string & statName ,
            double value, bool passed);

    void addPValues(const std::vector<double> & pvals);

    void finalizeReport();

    std::uint64_t getLastInsertedId();
};

} // namespace storage
} // namespace rtt

#endif // RTT_STORAGE_MYSQLSTORAGE_H

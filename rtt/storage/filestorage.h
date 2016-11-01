#ifndef RTT_STORAGE_FILESTORAGE_H
#define RTT_STORAGE_FILESTORAGE_H

#include <algorithm>
#include <memory>
#include <string>
#include <vector>
#include <iomanip>

#include "rtt/globalcontainer.h"
#include "rtt/storage/istorage.h"

namespace rtt {
namespace storage {

typedef std::vector<std::string> tStringVector;

class FileStorage : public IStorage {
public:
    static std::unique_ptr<FileStorage> getInstance(const GlobalContainer & container);

    void writeResults(const std::vector<batteries::ITestResult *> & testResults);

private:
    /*
    =================
    *** Constants ***
    =================
    */
    /* Strings in report */
    static const std::string STRING_PASSED_PROP;

    /* Other constants */
    static const size_t MISC_TAB_SIZE;
    static const size_t MISC_COL_WIDTH;
    static const uint FLOAT_PRECISION;

    /*
    =================
    *** Variables ***
    =================
    */
    /* Pointers to global objects */
    CliOptions * cliOptions;
    ToolkitSettings * toolkitSettings;

    time_t creationTime;
    Constants::Battery battId;
    std::string inFilePath;
    std::string outFilePath;
    std::string mainOutFilePath;
    std::stringstream report;
    int passedTestsCount = 0;
    int totalTestsCount = 0;
    std::string passedTestProp;
    int indent = 0;
    int currentSubtest = 0;
    int currentVariant = 0;

    /*
    ===============
    *** Methods ***
    ===============
    */
    FileStorage() {}

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
            double value , int precision , bool passed);

    void addPValues(
            const std::vector<double> & pvals,
            int precision);

    void finalizeReport();

    void makeReportHeader();

    std::string doIndent() const;

    void addResultToTableFile() const;

    void loadMainTable(tStringVector & header,
                       tStringVector & fileNames,
                       std::vector<tStringVector> & tableData) const;

    void saveMainTable(const tStringVector & header,
                       const tStringVector & fileNames,
                       const std::vector<tStringVector> & tableData) const;

    void addNewRow(tStringVector & fileNames,
                   std::vector<tStringVector> & tableData) const;

    static std::string stripSpacesFromString(const std::string & str);
};

} // namespace storage
} // namespace rtt

#endif // RTT_STORAGE_FILESTORAGE_H

#ifndef RTT_OUTPUT_FILE_STORAGE_H
#define RTT_OUTPUT_FILE_STORAGE_H

#include <algorithm>
#include <memory>
#include <string>
#include <vector>
#include <iomanip>

#include "libs/tinyXML/xmlproc.h"

#include "rtt/clioptions.h"
#include "rtt/output/ioutput-out.h"

namespace rtt {
namespace output {
namespace file {

typedef std::vector<std::string> tStringVector;

class Storage : public IOutput {
public:
    /* XPath constants */
    static const std::string XPATH_FILE_MAIN;
    static const std::string XPATH_DIR_DH;
    static const std::string XPATH_DIR_NIST;
    static const std::string XPATH_DIR_TU01_SC;
    static const std::string XPATH_DIR_TU01_C;
    static const std::string XPATH_DIR_TU01_BC;
    static const std::string XPATH_DIR_TU01_RB;
    static const std::string XPATH_DIR_TU01_AB;

    /* Other constants */
    static const size_t MISC_TAB_SIZE;
    static const size_t MISC_COL_WIDTH;

    static std::unique_ptr<Storage> getInstance(TiXmlNode * root ,
                                                const CliOptions & options ,
                                                const time_t & creationTime);

    void addNewTest(const std::string & testName);

    void setTestOptions(const std::vector<std::string> & options);

    void addSubTest();

    void addStatisticResult(const std::string & statName , double value , int precision = 2);

    void addStatisticResult(const std::string & statName , const std::string & value , bool failed);

    void addPValues(const std::vector<double> & pvals, int precision = 2);

    void finalizeSubTest();

    void finalizeTest();

    void finalizeReport();

private:
    /*
    =================
    *** Variables ***
    =================
    */
    time_t creationTime;
    Constants::Battery batteryConstant;
    std::string inFilePath;
    std::string outFilePath;
    std::string mainOutFilePath;
    std::stringstream report;
    int passedStatisticsCount = 0;
    int totalStatisticsCount = 0;
    std::string passedTestProp;
    int indent = 0;
    int currentSubtest = 0;

    /*
    ===============
    *** Methods ***
    ===============
    */
    Storage() {}

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

} // namespace file
} // namespace output
} // namespace rtt

#endif // RTT_OUTPUT_FILE_STORAGE_H

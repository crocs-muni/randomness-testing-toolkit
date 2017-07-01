#include "filestorage.h"

namespace rtt {
namespace storage {

const std::string FileStorage::STRING_PASSED_PROP       = "Passed/Total tests: ";
const std::string FileStorage::STRING_BATTERY_WARNINGS  = "Battery warnings:\n";
const std::string FileStorage::STRING_BATTERY_ERRORS    = "Battery errors:\n";

const size_t FileStorage::MISC_TAB_SIZE     = 4;
const size_t FileStorage::MISC_COL_WIDTH    = 30;
const uint FileStorage::FLOAT_PRECISION     = 8;

std::unique_ptr<FileStorage> FileStorage::getInstance(const GlobalContainer & container) {
    std::unique_ptr<FileStorage> s (new FileStorage());
    s->rttCliOptions   = container.getRttCliOptions();
    s->toolkitSettings = container.getToolkitSettings();
    s->creationTime    = container.getCreationTime();
    s->battery         = s->rttCliOptions->getBatteryArg();
    s->inFilePath      = s->rttCliOptions->getInputDataPath();

    /* Getting file name for main output file */
    s->mainOutFilePath = s->toolkitSettings->getRsFileOutFile();

    /* Creating file name for test report file */
    auto binFileName = Utils::getLastItemInPath(s->inFilePath);
    std::replace(binFileName.begin(), binFileName.end(), '.', '_');
    auto datetime = Utils::formatRawTime(s->creationTime , "%Y%m%d%H%M%S");
    s->outFilePath = s->toolkitSettings->getRsFileBatteryDir(s->battery);
    s->outFilePath.append(datetime + "-" + binFileName + "-report.txt");

    return s;
}

void FileStorage::init() {
    if(initialized)
        raiseBugException("storage was already initialized");

    initialized = true;
    makeReportHeader();
}

void FileStorage::writeResults(const std::vector<batteries::ITestResult *> & testResults) {
    if(!initialized)
        raiseBugException("storage wasn't initialized");

    if(testResults.empty())
        raiseBugException("empty results");

    for(const auto & testRes : testResults) {
        addNewTest(testRes->getTestName());
        if(testRes->getOptionalPassed().second) {
            setTestResult(testRes->getOptionalPassed().first);
            setTestPartialAlpha(testRes->getPartialAlpha());
        }

        const auto & variantResults = testRes->getVariantResults();
        for(const auto & varRes : variantResults) {
            if(variantResults.size() > 1)
                addVariant();

            setUserSettings(varRes.getUserSettings());
            setWarningMessages(varRes.getBatteryOutput().getWarnings());
            setErrorMessages(varRes.getBatteryOutput().getErrors());
            setStdErrMessages(Utils::split(varRes.getBatteryOutput().getStdErr(), '\n'));

            const auto & subResults = varRes.getSubResults();
            for(const batteries::result::SubTestResult & subRes : subResults) {
                if(subResults.size() > 1)
                    addSubTest();

                setTestParameters(subRes.getTestParameters());

                for(const batteries::result::Statistic & stat : subRes.getStatistics()) {
                    addStatisticResult(stat.getName(), stat.getValue(), FLOAT_PRECISION,
                                       testRes->isPValuePassing(stat.getValue()));
                }

                if(subRes.getPvalues().size() > 0)
                    addPValues(subRes.getPvalues(), FLOAT_PRECISION);

                if(subResults.size() > 1)
                    finalizeSubTest();
            }

            if(variantResults.size() > 1)
                finalizeVariant();
        }
        finalizeTest();
    }
}

void FileStorage::close() {
    if(!initialized)
        raiseBugException("storage wasn't initialized");

    finalizeReport();

    /* Storing report */
    Utils::createDirectory(Utils::getPathWithoutLastItem(outFilePath));
    Utils::saveStringToFile(outFilePath , report.str());

    /* Adding result into table file */
    /* Files with same name as the file processed in
     * this run will be assigned new results */
    addResultToTableFile();

    /* Reset storage state */
    report.str(std::string());
    passedTestsCount = 0;
    totalTestsCount = 0;
    passedTestProp = "";
    indent = 0;
    currSubtest = 0;
    currVariant = 0;
}

void FileStorage::addBatteryError(const std::string & error) {
    addBatteryErrors({error});
}

void FileStorage::addBatteryErrors(const std::vector<std::string> & errors) {
    if(errors.empty())
        return;

    std::string errorStr;
    for(const auto & e : errors)
        errorStr.append("    " + e + "\n");

    std::string reportStr = report.str();
    size_t pos = reportStr.find(STRING_BATTERY_ERRORS);
    if(pos == std::string::npos)
        raiseBugException(STRING_BATTERY_ERRORS + " not found in report");

    reportStr.insert(pos + STRING_BATTERY_ERRORS.length(), errorStr);
    report.str(reportStr);
}

void FileStorage::addBatteryWarning(const std::string & warning) {
    addBatteryWarnings({warning});
}

void FileStorage::addBatteryWarnings(const std::vector<std::string> & warnings) {
    if(warnings.empty())
        return;

    std::string warningStr;
    for(const auto & w : warnings)
        warningStr.append("    " + w + "\n");

    std::string reportStr = report.str();
    size_t pos = reportStr.find(STRING_BATTERY_WARNINGS);
    if(pos == std::string::npos)
        raiseBugException(STRING_BATTERY_WARNINGS + " not found in report");

    reportStr.insert(pos + STRING_BATTERY_WARNINGS.length(), warningStr);
    report.str(reportStr);
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
void FileStorage::addNewTest(const std::string & testName) {
    report << "-----------------------------------------------------------" << std::endl;
    report << testName << " test results:" << std::endl;
    ++indent;
}

void FileStorage::finalizeTest() {
    report << "-----------------------------------------------------------"
           << std::endl << std::endl;
    --indent;
    currVariant = 0;
    currSubtest = 0;
}

void FileStorage::addVariant() {
    ++currVariant;
    report << doIndent() << "Variant " << currVariant << ":" << std::endl;
    ++indent;
}

void FileStorage::finalizeVariant() {
    --indent;
    report << doIndent() << "^^^^^^^^^^^^" << std::endl;
    currSubtest = 0;
    report << std::endl;
}

void FileStorage::addSubTest() {
    ++currSubtest;
    report << doIndent() << "Subtest " << currSubtest << ":" << std::endl;
    ++indent;
}

void FileStorage::finalizeSubTest() {
    --indent;
    report << doIndent() << "############" << std::endl;
    report << std::endl;
}

void FileStorage::setTestResult(bool passed) {
    report << doIndent() << "Result: ";
    ++totalTestsCount;
    if(passed) {
        ++passedTestsCount;
        report << "Passed" << std::endl;
    }
    else
        report << "FAILED" << std::endl;
}

void FileStorage::setTestPartialAlpha(double alpha) {
    report << doIndent() << "Test partial alpha: " << alpha << std::endl;
    report << std::endl;
}

void FileStorage::setUserSettings(
        const std::vector<std::pair<std::string, std::string> > & options) {
    report << doIndent() << "User settings: " << std::endl;
    ++indent;
    std::string spaces = doIndent();
    for(const auto & i : options)
        report << spaces << i.first << ": " << i.second << std::endl;
    --indent;
    report << doIndent() << "************" << std::endl;
    report << std::endl;
}

void FileStorage::setTestParameters(
        const std::vector<std::pair<std::string, std::string>> & options) {
    if(options.empty())
        return;

    report << doIndent() << "Test parameters: " << std::endl;
    ++indent;
    std::string spaces = doIndent();
    for(const auto & i : options)
        report << spaces << i.first << " = " << i.second << std::endl;
    --indent;
    report << doIndent() << "%%%%%%%%%%" << std::endl;
    report << std::endl;
}

void FileStorage::setWarningMessages(const std::vector<std::string> & warnings) {
    if(warnings.empty())
        return;

    report << doIndent() << "Warnings in log: " << std::endl;
    ++indent;
    auto spaces = doIndent();
    for(const auto & i : warnings)
        report << spaces << i << std::endl;
    --indent;
    report << doIndent() << "!!!!!!!!!!!!" << std::endl << std::endl;
}

void FileStorage::setErrorMessages(const std::vector<std::string> & errors) {
    if(errors.empty())
        return;

    report << doIndent() << "Error messages: " << std::endl;
    ++indent;
    auto spaces = doIndent();
    for(const auto & i : errors)
        report << spaces << i << std::endl;
    --indent;
    report << doIndent() << "!!!!!!!!!!!!" << std::endl << std::endl;
}

void FileStorage::setStdErrMessages(const std::vector<std::string> & stderr) {
    if(stderr.empty())
        return;

    report << doIndent() << "Standard error output: " << std::endl;
    ++indent;
    auto spaces = doIndent();
    for(const auto & i : stderr)
        report << spaces << i << std::endl;
    --indent;
    report << doIndent() << "!!!!!!!!!!!!" << std::endl << std::endl;
}

void FileStorage::addStatisticResult(const std::string & statName,
                                     double value, int precision, bool passed) {
    std::stringstream tmp;
    tmp << doIndent() << statName <<" statistic p-value: "
        << std::setprecision(precision) << std::fixed << value;
    report << std::setw(58) << std::left << tmp.str();

    if(passed)
        report << " Passed" << std::endl;
    else
        report << " FAILED!!!" << std::endl;
}

void FileStorage::addPValues(const std::vector<double> & pvals , int precision) {
    report << doIndent() << "p-values: " << std::endl;
    ++indent;
    std::string spaces = doIndent();

    size_t pvalPerRow = 5;
    for(size_t ctr = 0 ; ctr < pvals.size() ; ) {
        report << spaces;
        for(size_t col = 0 ; col < std::min(pvalPerRow , pvals.size() - ctr) ; ++col) {
            report << std::setprecision(precision)
                   << std::fixed << pvals.at(ctr + col) << " ";
        }
        report << std::endl;
        ctr += pvalPerRow;
    }

    --indent;
    report << doIndent() << "============" << std::endl;
}

void FileStorage::finalizeReport() {
    /* Add passed tests proportion at the end of report */
    passedTestProp = { Utils::itostr(passedTestsCount) + "/" + Utils::itostr(totalTestsCount) };
    std::string reportStr = report.str();
    size_t pos = reportStr.find(STRING_PASSED_PROP);
    reportStr.insert(pos + STRING_PASSED_PROP.length(), passedTestProp);
    report.str(reportStr);
}

void FileStorage::makeReportHeader() {
    report << "***** Randomness Testing Toolkit data stream analysis report *****" << std::endl;
    report << "Date:    " << Utils::formatRawTime(creationTime , "%d-%m-%Y") << std::endl;
    report << "File:    " << inFilePath << std::endl;
    report << "Battery: " << battery.getName() << std::endl;
    report << std::endl;
    report << "Alpha:   " << std::setw(3) << Constants::MATH_ALPHA << std::endl;
    report << "Epsilon: " << Constants::MATH_EPS << std::endl;
    report << std::endl;
    report << STRING_PASSED_PROP << std::endl;
    report << std::endl;
    report << STRING_BATTERY_ERRORS << std::endl;
    report << STRING_BATTERY_WARNINGS << std::endl << std::endl;
}

std::string FileStorage::doIndent() const {
    if(indent > 0)
        return std::string(indent * MISC_TAB_SIZE, ' ');
    else
        return "";
}

void FileStorage::addResultToTableFile() const {
    if(Utils::fileExist(mainOutFilePath)) {
        /* Table file already exist */
        tStringVector header;
        tStringVector fileNames;
        std::vector<tStringVector> tableData;
        /* Loading file into table variables */
        loadMainTable(header , fileNames , tableData);

        /* Looking for file name - if table already has row
         * with same file name as I am processing here,
         * only new information is added to this row.
         * Otherwise new row is added. */
        std::vector<std::string>::iterator fileRow =
                std::find(fileNames.begin() , fileNames.end() , inFilePath);
        if(fileRow != fileNames.end()) {
            /* Row with same filename is present, modifying this row */
            int rowIndex = std::distance(fileNames.begin() , fileRow);
            tableData.at(rowIndex).at(0) =
                    Utils::formatRawTime(creationTime , "%Y-%m-%d %H:%M:%S");
            tableData.at(rowIndex).at(static_cast<int>(battery.getBatteryId())) = passedTestProp;
        } else {
            /* Adding new row */
            addNewRow(fileNames , tableData);
        }

        /* Saving table variables into file. */
        saveMainTable(header , fileNames , tableData);
    } else {
        /* File doesn't exist, create brand new table file with single new result */
        tStringVector header;
        tStringVector fileNames;
        std::vector<tStringVector> tableData;

        /* Creating header */
        header.push_back("Input file path");
        header.push_back("Time of last update");
        for(int i = 1 ; i < static_cast<int>(Constants::BatteryID::LAST_ITEM) ; ++i)
            header.push_back(BatteryArg::getName(static_cast<Constants::BatteryID>(i)));

        /* Adding new row */
        addNewRow(fileNames , tableData);

        /* Table variables are now complete, save into file */
        saveMainTable(header , fileNames , tableData);
    }
}

void FileStorage::loadMainTable(tStringVector & header,
                            tStringVector & fileNames,
                            std::vector<tStringVector> & tableData) const {
    std::string table = std::move(Utils::readFileToString(mainOutFilePath));
    tStringVector lines = Utils::split(table , '\n');
    if(lines.empty())
        throw std::runtime_error("can't load table: file is empty");

    /* Parsing header */
    header = std::move(Utils::split(lines.at(0) , '^'));

    /* Parsing rows */
    tStringVector row;
    for(size_t i = 1 ; i < lines.size() ; ++i) {
        row = std::move(Utils::split(lines.at(i) , '^'));
        if(row.size() != 1)
            throw std::runtime_error("input table corrupted: "
                                     "non header row contains more than one \"^\"");

        row = std::move(Utils::split(row.at(0) , '|'));
        if(row.size() != header.size())
            throw std::runtime_error("input table corrupted: "
                                     "row " + Utils::itostr(i) + " has "
                                     "different number of columns than header");
        fileNames.push_back(stripSpacesFromString(row.at(0)));
        tableData.push_back({row.begin() + 1 , row.end()});
    }
}

void FileStorage::saveMainTable(const tStringVector & header,
                            const tStringVector & fileNames,
                            const std::vector<tStringVector> & tableData) const {
    if(fileNames.size() != tableData.size())
        throw std::runtime_error("can't create output table: number of filenames and"
                                 " number of table data rows does not match");

    /* First columnt is aligned to left, rest right */
    bool first = true;
    std::stringstream table;

    /* Creating header */
    for(const std::string & val : header) {
        table << "^";
        table << std::setw(MISC_COL_WIDTH);
        if(first){
            table << std::left;
            first = false;
        }
        else /* This else is maybe useless */
            table << std::right;
        table << val;
    }
    table << "^" << std::endl;

    /* Inserting rows */
    for(size_t i = 0 ; i < fileNames.size() ; ++i) {
        table << "^";
        table << std::setw(MISC_COL_WIDTH) << std::left;
        table << fileNames.at(i);
        table << std::right;
        for(const std::string & val : tableData.at(i)) {
            table << "|";
            table << std::setw(MISC_COL_WIDTH);
            table << val;
        }
        table << "|" << std::endl;
    }

    /* Saving table to file */
    Utils::createDirectory(Utils::getPathWithoutLastItem(mainOutFilePath));
    Utils::saveStringToFile(mainOutFilePath , table.str());
}

void FileStorage::addNewRow(tStringVector & fileNames,
                        std::vector<tStringVector> & tableData) const {
    /* Add file path to file names column */
    fileNames.push_back(inFilePath);
    /* Add data into corresponding row */
    /* Column count is total batteries count + first column for last update info */
    tStringVector row(static_cast<int>(Constants::BatteryID::LAST_ITEM) , "");
    row.at(0) = Utils::formatRawTime(creationTime , "%Y-%m-%d %H:%M:%S");
    row.at(static_cast<int>(battery.getBatteryId())) = passedTestProp;
    tableData.push_back(std::move(row));
}

std::string FileStorage::stripSpacesFromString(const std::string & str) {
    size_t start = str.find_first_not_of(" ");
    size_t end = str.find_last_not_of(" ");
    return str.substr(start , end + 1);
}

} // namespace storage
} // namespace rtt

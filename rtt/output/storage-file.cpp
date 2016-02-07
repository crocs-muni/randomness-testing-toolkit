#include "storage-file.h"

namespace rtt {
namespace output {
namespace file {

const std::string Storage::XPATH_DIR_DH         = "TOOLKIT_SETTINGS/OUTPUT/FILE/DIEHARDER_DIR";
const std::string Storage::XPATH_DIR_NIST       = "TOOLKIT_SETTINGS/OUTPUT/FILE/NIST_STS_DIR";
const std::string Storage::XPATH_DIR_TU01_SC    = "TOOLKIT_SETTINGS/OUTPUT/FILE/TU01_SMALLCRUSH_DIR";
const std::string Storage::XPATH_DIR_TU01_C     = "TOOLKIT_SETTINGS/OUTPUT/FILE/TU01_CRUSH_DIR";
const std::string Storage::XPATH_DIR_TU01_BC    = "TOOLKIT_SETTINGS/OUTPUT/FILE/TU01_BIGCRUSH_DIR";
const std::string Storage::XPATH_DIR_TU01_RB    = "TOOLKIT_SETTINGS/OUTPUT/FILE/TU01_RABBIT_DIR";
const std::string Storage::XPATH_DIR_TU01_AB    = "TOOLKIT_SETTINGS/OUTPUT/FILE/TU01_ALPHABIT_DIR";

const size_t Storage::MISC_TAB_SIZE = 4;

std::unique_ptr<Storage> Storage::getInstance(TiXmlNode * root ,
                                              const CliOptions & options ,
                                              const time_t & creationTime) {
    std::unique_ptr<Storage> storage (new Storage());
    storage->creationTime = creationTime;
    storage->batteryConstant = options.getBattery();
    storage->inFilePath = options.getBinFilePath();

    std::string dirXPath;
    switch(storage->batteryConstant) {
    case Constants::BATTERY_DIEHARDER       : dirXPath = XPATH_DIR_DH; break;
    case Constants::BATTERY_NIST_STS        : dirXPath = XPATH_DIR_NIST; break;
    case Constants::BATTERY_TU01_SMALLCRUSH : dirXPath = XPATH_DIR_TU01_SC; break;
    case Constants::BATTERY_TU01_CRUSH      : dirXPath = XPATH_DIR_TU01_C; break;
    case Constants::BATTERY_TU01_BIGCRUSH   : dirXPath = XPATH_DIR_TU01_BC; break;
    case Constants::BATTERY_TU01_RABBIT     : dirXPath = XPATH_DIR_TU01_RB; break;
    case Constants::BATTERY_TU01_ALPHABIT   : dirXPath = XPATH_DIR_TU01_AB; break;
    default:
        throw std::runtime_error("unknown battery constant: " +
                                 Utils::itostr(options.getBattery()));
    }

    std::string binFileName = Utils::getLastItemInPath(storage->inFilePath);
    std::string datetime = Utils::formatRawTime(storage->creationTime , "%Y%m%d%H%M%S");
    storage->outFilePath = getXMLElementValue(root , dirXPath);
    if(!storage->outFilePath.empty() && storage->outFilePath.back() != '/')
        storage->outFilePath.append("/");
    storage->outFilePath.append(datetime + "-" + binFileName + ".report");

    storage->makeReportHeader();

    return storage;
}

void Storage::addNewTest(const std::string & testName) {
    report << "---------------------------------------------------" << std::endl;
    report << testName << " test results:" << std::endl;
    ++indent;
}

void Storage::setTestOptions(const std::vector<std::string> & options) {
    report << doIndent() << "Test settings: " << std::endl;
    ++indent;
    std::string tabs = doIndent();
    for(const std::string & i : options)
        report << tabs << i << std::endl;
    --indent;
    report << doIndent() << "************" << std::endl;
    report << std::endl;
}

void Storage::addSubTest() {
    ++currentSubtest;
    report << doIndent() << "Subtest " << currentSubtest << ":" << std::endl;
    ++indent;
}

void Storage::addStatisticResult(const std::string & statName, double value) {
    report << doIndent() << statName << " statistic: " << value << std::endl;
}

void Storage::addStatisticResult(const std::string & statName , const std::string & value) {
    report << doIndent() << statName << " statistic: " << value << std::endl;
}

void Storage::addPValues(const std::vector<double> & pvals) {
    report << doIndent() << "p-values: " << std::endl;
    ++indent;
    std::string tabs = doIndent();
    for(const double & i : pvals)
        report << tabs << i << std::endl;
    --indent;
    report << doIndent() << "============" << std::endl;
}

void Storage::finalizeSubTest() {
    --indent;
    report << doIndent() << "############" << std::endl;
    report << std::endl;
}

void Storage::finalizeTest() {
    report << "---------------------------------------------------" << std::endl << std::endl;
    --indent;
    currentSubtest = 0;
}

void Storage::finalizeReport() {
    Utils::createDirectory(Utils::getPathWithoutLastItem(outFilePath));
    Utils::saveStringToFile(outFilePath , report.str());
}

void Storage::makeReportHeader() {
    report << "***** Randomness Testing Toolkit file analysis report *****" << std::endl;
    report << "Date:    " << Utils::formatRawTime(creationTime , "%d-%m-%Y") << std::endl;
    report << "File:    " << inFilePath << std::endl;
    report << "Battery: " << Constants::batteryToString(batteryConstant) << std::endl;
    report << std::endl << std::endl;
}

std::string Storage::doIndent() {
    if(indent > 0)
        return std::string(indent * MISC_TAB_SIZE, ' ');
    else
        return "";
}

} // namespace file
} // namespace output
} // namespace rtt


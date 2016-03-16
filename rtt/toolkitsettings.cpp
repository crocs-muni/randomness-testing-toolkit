#include "toolkitsettings.h"

namespace rtt {

/* Constant definition */
const std::string ToolkitSettings::XPATH_LOGGER_DIR_PREFIX              = "LOGGER/DIR_PREFIX";
const std::string ToolkitSettings::XPATH_LOGGER_RUN_LOG_DIR             = "LOGGER/RUN_LOG_DIR";
const std::string ToolkitSettings::XPATH_LOGGER_DIEHARDER_DIR           = "LOGGER/DIEHARDER_DIR";
const std::string ToolkitSettings::XPATH_LOGGER_NISTSTS_DIR             = "LOGGER/NIST_STS_DIR";
const std::string ToolkitSettings::XPATH_LOGGER_TU01_SCRUSH_DIR         = "LOGGER/TU01_SMALLCRUSH_DIR";
const std::string ToolkitSettings::XPATH_LOGGER_TU01_CRUSH_DIR          = "LOGGER/TU01_CRUSH_DIR";
const std::string ToolkitSettings::XPATH_LOGGER_TU01_BCRUSH_DIR         = "LOGGER/TU01_BIGCRUSH_DIR";
const std::string ToolkitSettings::XPATH_LOGGER_TU01_RABBIT_DIR         = "LOGGER/TU01_RABBIT_DIR";
const std::string ToolkitSettings::XPATH_LOGGER_TU01_ALPHABIT_DIR       = "LOGGER/TU01_ALPHABIT_DIR";

const std::string ToolkitSettings::XPATH_RS_FILE_OUTPUT_FILE            = "RESULT_STORAGE/FILE/OUTPUT_FILE";
const std::string ToolkitSettings::XPATH_RS_FILE_DIR_PREFIX             = "RESULT_STORAGE/FILE/DIR_PREFIX";
const std::string ToolkitSettings::XPATH_RS_FILE_DIEHARDER_DIR          = "RESULT_STORAGE/FILE/DIEHARDER_DIR";
const std::string ToolkitSettings::XPATH_RS_FILE_NISTSTS_DIR            = "RESULT_STORAGE/FILE/NIST_STS_DIR";
const std::string ToolkitSettings::XPATH_RS_FILE_TU01_SCRUSH_DIR        = "RESULT_STORAGE/FILE/TU01_SMALLCRUSH_DIR";
const std::string ToolkitSettings::XPATH_RS_FILE_TU01_CRUSH_DIR         = "RESULT_STORAGE/FILE/TU01_CRUSH_DIR";
const std::string ToolkitSettings::XPATH_RS_FILE_TU01_BCRUSH_DIR        = "RESULT_STORAGE/FILE/TU01_BIGCRUSH_DIR";
const std::string ToolkitSettings::XPATH_RS_FILE_TU01_RABBIT_DIR        = "RESULT_STORAGE/FILE/TU01_RABBIT_DIR";
const std::string ToolkitSettings::XPATH_RS_FILE_TU01_ALPHABIT_DIR      = "RESULT_STORAGE/FILE/TU01_ALPHABIT_DIR";

const std::string ToolkitSettings::XPATH_BINARIES_DIEHARDER             = "BINARIES/DIEHARDER";
const std::string ToolkitSettings::XPATH_BINARIES_NISTSTS               = "BINARIES/NIST_STS";
const std::string ToolkitSettings::XPATH_BINARIES_TESTU01               = "BINARIES/TESTU01";

const std::string ToolkitSettings::XPATH_MISC_NISTSTS_MAIN_RESULT_DIR   = "MISCELANEOUS/NIST_STS/MAIN_RESULT_DIR";

ToolkitSettings ToolkitSettings::getInstance(const std::string & configFileName) {
    TiXmlNode * xmlCfg = NULL;
    loadXMLFile(xmlCfg , configFileName);

    ToolkitSettings ts;

    /* Variables are set below. If new battery or variables are added set them here.
     * Ideally follow organization that is already here. */
    /* Logger directories */
    std::string dirPfx      = ts.getDirValue(xmlCfg , XPATH_LOGGER_DIR_PREFIX , false);
    ts.loggerRunLogDir      = dirPfx + ts.getDirValue(xmlCfg , XPATH_LOGGER_RUN_LOG_DIR);
    ts.loggerDieharderDir   = dirPfx + ts.getDirValue(xmlCfg , XPATH_LOGGER_DIEHARDER_DIR);
    ts.loggerNiststsDir     = dirPfx + ts.getDirValue(xmlCfg , XPATH_LOGGER_NISTSTS_DIR);
    ts.loggerSCrushDir      = dirPfx + ts.getDirValue(xmlCfg , XPATH_LOGGER_TU01_SCRUSH_DIR);
    ts.loggerCrushDir       = dirPfx + ts.getDirValue(xmlCfg , XPATH_LOGGER_TU01_CRUSH_DIR);
    ts.loggerBCrushDir      = dirPfx + ts.getDirValue(xmlCfg , XPATH_LOGGER_TU01_BCRUSH_DIR);
    ts.loggerRabbitDir      = dirPfx + ts.getDirValue(xmlCfg , XPATH_LOGGER_TU01_RABBIT_DIR);
    ts.loggerAlphabitDir    = dirPfx + ts.getDirValue(xmlCfg , XPATH_LOGGER_TU01_ALPHABIT_DIR);

    /* Result storage directories */
    /* File */
    dirPfx                  = ts.getDirValue(xmlCfg , XPATH_RS_FILE_DIR_PREFIX , false);
    ts.rsFileOutFile        = ts.getStringValue(xmlCfg , XPATH_RS_FILE_OUTPUT_FILE);
    ts.rsFileDieharderDir   = dirPfx + ts.getDirValue(xmlCfg , XPATH_RS_FILE_DIEHARDER_DIR);
    ts.rsFileNiststsDir     = dirPfx + ts.getDirValue(xmlCfg , XPATH_RS_FILE_NISTSTS_DIR);
    ts.rsFileSCrushDir      = dirPfx + ts.getDirValue(xmlCfg , XPATH_RS_FILE_TU01_SCRUSH_DIR);
    ts.rsFileCrushDir       = dirPfx + ts.getDirValue(xmlCfg , XPATH_RS_FILE_TU01_CRUSH_DIR);
    ts.rsFileBCrushDir      = dirPfx + ts.getDirValue(xmlCfg , XPATH_RS_FILE_TU01_BCRUSH_DIR);
    ts.rsFileRabbitDir      = dirPfx + ts.getDirValue(xmlCfg , XPATH_RS_FILE_TU01_RABBIT_DIR);
    ts.rsFileAlphabitDir    = dirPfx + ts.getDirValue(xmlCfg , XPATH_RS_FILE_TU01_ALPHABIT_DIR);
    /* Database */
    // not yet!

    /* Binaries locations */
    ts.binaryDieharder  = ts.getStringValue(xmlCfg , XPATH_BINARIES_DIEHARDER);
    ts.binaryNiststs    = ts.getStringValue(xmlCfg , XPATH_BINARIES_NISTSTS);
    ts.binaryTestU01    = ts.getStringValue(xmlCfg , XPATH_BINARIES_TESTU01);

    /* Miscelaneous variables */
    ts.miscNiststsMainResDir = ts.getDirValue(xmlCfg , XPATH_MISC_NISTSTS_MAIN_RESULT_DIR);

    free(xmlCfg);
    return ts;
}

std::string ToolkitSettings::getLoggerRunLogDir() const {
    return loggerRunLogDir;
}

std::string ToolkitSettings::getRsFileOutFile() const {
    return rsFileOutFile;
}

std::string ToolkitSettings::getLoggerBatteryDir(Constants::Battery battery) const {
    return getBatteryVariable(VariableType::loggerDir , battery);
}

std::string ToolkitSettings::getRsFileBatteryDir(Constants::Battery battery) const {
    return getBatteryVariable(VariableType::rsFileDir , battery);
}

std::string ToolkitSettings::getBinaryBattery(Constants::Battery battery) const {
    return getBatteryVariable(VariableType::binary , battery);
}
std::string ToolkitSettings::getMiscNiststsMainResDir() const {
    return miscNiststsMainResDir;
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

std::string ToolkitSettings::getBatteryVariable(VariableType variableType,
                                                Constants::Battery battery) const {
    /* This is main getter so that all of it is in one place (for future modifications).
     * If new battery is added - create new case for that constant, add it below.
     * If new VariableType is added - add its case into each battery. Also add method
     * for accessing it (see methods getLoggerBatteryDir, getBinaryBattery, etc...)*/
    switch(battery) {
    case Constants::Battery::NIST_STS: {
        switch(variableType) {
        case VariableType::binary:    return binaryNiststs;
        case VariableType::loggerDir: return loggerNiststsDir;
        case VariableType::rsFileDir: return rsFileNiststsDir;
        default:raiseBugException("invalid variable type");
        }
    }
    case Constants::Battery::DIEHARDER: {
        switch(variableType) {
        case VariableType::binary:    return binaryDieharder;
        case VariableType::loggerDir: return loggerDieharderDir;
        case VariableType::rsFileDir: return rsFileDieharderDir;
        default:raiseBugException("invalid variable type");
        }
    }
    case Constants::Battery::TU01_SMALLCRUSH: {
        switch(variableType) {
        case VariableType::binary:    return binaryTestU01;
        case VariableType::loggerDir: return loggerSCrushDir;
        case VariableType::rsFileDir: return rsFileSCrushDir;
        default:raiseBugException("invalid variable type");
        }
    }
    case Constants::Battery::TU01_CRUSH: {
        switch(variableType) {
        case VariableType::binary:    return binaryTestU01;
        case VariableType::loggerDir: return loggerCrushDir;
        case VariableType::rsFileDir: return rsFileCrushDir;
        default:raiseBugException("invalid variable type");
        }
    }
    case Constants::Battery::TU01_BIGCRUSH: {
        switch(variableType) {
        case VariableType::binary:    return binaryTestU01;
        case VariableType::loggerDir: return loggerBCrushDir;
        case VariableType::rsFileDir: return rsFileBCrushDir;
        default:raiseBugException("invalid variable type");
        }
    }
    case Constants::Battery::TU01_RABBIT: {
        switch(variableType) {
        case VariableType::binary:    return binaryTestU01;
        case VariableType::loggerDir: return loggerBCrushDir;
        case VariableType::rsFileDir: return rsFileRabbitDir;
        default:raiseBugException("invalid variable type");
        }
    }
    case Constants::Battery::TU01_ALPHABIT: {
        switch(variableType) {
        case VariableType::binary:    return binaryTestU01;
        case VariableType::loggerDir: return loggerAlphabitDir;
        case VariableType::rsFileDir: return rsFileAlphabitDir;
        default:raiseBugException("invalid variable type");
        }
    }
    default:raiseBugException("invalid battery");
    }
}

std::string ToolkitSettings::getDirValue(TiXmlNode * xmlConfig,
                                         const std::string & xpath,
                                         bool mandatory) {
    if(!xmlConfig)
        raiseBugException("null xml node");

    std::string rval = getXMLElementValue(xmlConfig , xpath);

    /* Check for existence, if empty and mandatory then fail,
     * otherwise return empty */
    if(rval.empty()) {
        if(mandatory)
            throw RTTException(objectInfo ,
                               "empty or nonexistent tag: " + xpath);
        else
            return rval;
    }
    /* Value is directory path, append "/" if it is not present */
    if(rval.back() != '/')
        rval.append("/");

    return rval;
}

std::string ToolkitSettings::getStringValue(TiXmlNode * xmlConfig,
                                            const std::string & xpath,
                                            bool mandatory) {
    if(!xmlConfig)
        raiseBugException("null xml node");

    std::string rval = getXMLElementValue(xmlConfig , xpath);

    if(mandatory && rval.empty())
        throw RTTException(objectInfo ,
                           "empty or nonexistent tag: " + xpath);
    else
        return rval;
}

int ToolkitSettings::getIntegerValue(TiXmlNode * xmlConfig,
                                     const std::string & xpath,
                                     bool mandatory) {
    if(!xmlConfig)
        raiseBugException("null xml node");

    std::string tmp = getXMLElementValue(xmlConfig , xpath);

    if(tmp.empty()) {
        if(mandatory)
            throw RTTException(objectInfo ,
                               "empty or nonexistent tag: " + xpath);
        else
            return 0;
    }

    try {
        return Utils::strtoi(tmp);
    } catch (std::runtime_error ex) {
        throw RTTException(objectInfo ,
                           "error in tag " + xpath + ": " + ex.what());
    }
}

} // namespace rtt


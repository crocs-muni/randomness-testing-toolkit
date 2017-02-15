#include "toolkitsettings.h"

namespace rtt {

const std::string ToolkitSettings::objectInfo = "Toolkit Settings";

const std::string ToolkitSettings::JSON_ROOT                         = "toolkit-settings";
const std::string ToolkitSettings::JSON_LOG                          = "logger";
const std::string ToolkitSettings::JSON_LOG_DIR_PFX                  = "dir-prefix";
const std::string ToolkitSettings::JSON_LOG_RUN_LOG_DIR              = "run-log-dir";
const std::string ToolkitSettings::JSON_LOG_DH_DIR                   = "dieharder-dir";
const std::string ToolkitSettings::JSON_LOG_NIST_DIR                 = "nist-sts-dir";
const std::string ToolkitSettings::JSON_LOG_TU01SC_DIR               = "tu01-smallcrush-dir";
const std::string ToolkitSettings::JSON_LOG_TU01C_DIR                = "tu01-crush-dir";
const std::string ToolkitSettings::JSON_LOG_TU01BC_DIR               = "tu01-bigcrush-dir";
const std::string ToolkitSettings::JSON_LOG_TU01RAB_DIR              = "tu01-rabbit-dir";
const std::string ToolkitSettings::JSON_LOG_TU01AB_DIR               = "tu01-alphabit-dir";
const std::string ToolkitSettings::JSON_LOG_TU01BAB_DIR              = "tu01-blockalphabit-dir";
const std::string ToolkitSettings::JSON_RS                           = "result-storage";
const std::string ToolkitSettings::JSON_RS_FILE                      = "file";
const std::string ToolkitSettings::JSON_RS_FILE_DIR_PFX              = "dir-prefix";
const std::string ToolkitSettings::JSON_RS_FILE_MAIN_FILE            = "main-file";
const std::string ToolkitSettings::JSON_RS_FILE_DH_DIR               = "dieharder-dir";
const std::string ToolkitSettings::JSON_RS_FILE_NIST_DIR             = "nist-sts-dir";
const std::string ToolkitSettings::JSON_RS_FILE_TU01SC_DIR           = "tu01-smallcrush-dir";
const std::string ToolkitSettings::JSON_RS_FILE_TU01C_DIR            = "tu01-crush-dir";
const std::string ToolkitSettings::JSON_RS_FILE_TU01BC_DIR           = "tu01-bigcrush-dir";
const std::string ToolkitSettings::JSON_RS_FILE_TU01RAB_DIR          = "tu01-rabbit-dir";
const std::string ToolkitSettings::JSON_RS_FILE_TU01AB_DIR           = "tu01-alphabit-dir";
const std::string ToolkitSettings::JSON_RS_FILE_TU01BAB_DIR          = "tu01-blockalphabit-dir";
const std::string ToolkitSettings::JSON_RS_MYSQL_DB                  = "mysql-db";
const std::string ToolkitSettings::JSON_RS_MYSQL_DB_ADDRESS          = "address";
const std::string ToolkitSettings::JSON_RS_MYSQL_DB_NAME             = "name";
const std::string ToolkitSettings::JSON_RS_MYSQL_DB_CRED_FILE        = "credentials-file";
const std::string ToolkitSettings::JSON_RS_MYSQL_DB_CRED_FILE_ROOT   = "credentials";
const std::string ToolkitSettings::JSON_RS_MYSQL_DB_CRED_FILE_NAME   = "username";
const std::string ToolkitSettings::JSON_RS_MYSQL_DB_CRED_FILE_PWD    = "password";
const std::string ToolkitSettings::JSON_BINARIES                     = "binaries";
const std::string ToolkitSettings::JSON_BINARIES_NIST                = "nist-sts";
const std::string ToolkitSettings::JSON_BINARIES_DH                  = "dieharder";
const std::string ToolkitSettings::JSON_BINARIES_TU01                = "testu01";
const std::string ToolkitSettings::JSON_MISC                         = "miscelaneous";
const std::string ToolkitSettings::JSON_MISC_NIST                    = "nist-sts";
const std::string ToolkitSettings::JSON_MISC_NIST_MAIN_RES_DIR       = "main-result-dir";
const std::string ToolkitSettings::JSON_EXEC                         = "execution";
const std::string ToolkitSettings::JSON_EXEC_MAX_PAR_TESTS           = "max-parallel-tests";



ToolkitSettings ToolkitSettings::getInstance(const std::string & cfgFileName) {
    json nRoot;
    try {
        nRoot = json::parse(Utils::readFileToString(cfgFileName));
    } catch (std::exception & ex) {
        throw RTTException(objectInfo,
                           "error during JSON parsing (" + cfgFileName +
                           ") - " + (std::string)ex.what());
    }

    if(nRoot.count(JSON_ROOT) != 1)
        throw RTTException(objectInfo , "missing root tag - " + JSON_ROOT);
    nRoot = nRoot.at(JSON_ROOT);

    ToolkitSettings ts;

    /* Variables are set below. If new battery or variables are added set them here.
     * Ideally follow organization that is already here. */

    /*** Logger directories ***/
    if(nRoot.count(JSON_LOG) != 1)
        throw RTTException(objectInfo , "missing tag with logger settings - " + JSON_LOG);
    {
        json nLogger            = nRoot.at(JSON_LOG);
        auto dirPfx             = parseDirectoryPath(nLogger , JSON_LOG_DIR_PFX , false);
        ts.loggerRunLogDir      = dirPfx + parseDirectoryPath(nLogger , JSON_LOG_RUN_LOG_DIR);
        ts.loggerDieharderDir   = dirPfx + parseDirectoryPath(nLogger , JSON_LOG_DH_DIR);
        ts.loggerNiststsDir     = dirPfx + parseDirectoryPath(nLogger , JSON_LOG_NIST_DIR);
        ts.loggerSCrushDir      = dirPfx + parseDirectoryPath(nLogger , JSON_LOG_TU01SC_DIR);
        ts.loggerCrushDir       = dirPfx + parseDirectoryPath(nLogger , JSON_LOG_TU01C_DIR);
        ts.loggerBCrushDir      = dirPfx + parseDirectoryPath(nLogger , JSON_LOG_TU01BC_DIR);
        ts.loggerRabbitDir      = dirPfx + parseDirectoryPath(nLogger , JSON_LOG_TU01RAB_DIR);
        ts.loggerAlphabitDir    = dirPfx + parseDirectoryPath(nLogger , JSON_LOG_TU01AB_DIR);
        ts.loggerBlAlphabitDir  = dirPfx + parseDirectoryPath(nLogger , JSON_LOG_TU01BAB_DIR);
    }

    /*** Result storage settings ***/
    if(nRoot.count(JSON_RS) != 1)
        throw RTTException(objectInfo , "missing tag with result storage settings - " + JSON_RS);
    {
        json nResultStorage = nRoot.at(JSON_RS);

        /** File storage **/
        if(nResultStorage.count(JSON_RS_FILE) != 1)
            throw RTTException(objectInfo , "missing tag with file storage settings - " + JSON_RS_FILE);
        {
            json nFile              = nResultStorage.at(JSON_RS_FILE);
            auto dirPfx             = parseDirectoryPath(nFile , JSON_RS_FILE_DIR_PFX , false);
            ts.rsFileOutFile        = parseStringValue(nFile , JSON_RS_FILE_MAIN_FILE);
            ts.rsFileDieharderDir   = dirPfx + parseDirectoryPath(nFile , JSON_RS_FILE_DH_DIR);
            ts.rsFileNiststsDir     = dirPfx + parseDirectoryPath(nFile , JSON_RS_FILE_NIST_DIR);
            ts.rsFileSCrushDir      = dirPfx + parseDirectoryPath(nFile , JSON_RS_FILE_TU01SC_DIR);
            ts.rsFileCrushDir       = dirPfx + parseDirectoryPath(nFile , JSON_RS_FILE_TU01C_DIR);
            ts.rsFileBCrushDir      = dirPfx + parseDirectoryPath(nFile , JSON_RS_FILE_TU01BC_DIR);
            ts.rsFileRabbitDir      = dirPfx + parseDirectoryPath(nFile , JSON_RS_FILE_TU01RAB_DIR);
            ts.rsFileAlphabitDir    = dirPfx + parseDirectoryPath(nFile , JSON_RS_FILE_TU01AB_DIR);
            ts.rsFileBlAlphabitDir  = dirPfx + parseDirectoryPath(nFile , JSON_RS_FILE_TU01BAB_DIR);
        }

        /** Database storage **/
        if(nResultStorage.count(JSON_RS_MYSQL_DB) != 1)
            throw RTTException(objectInfo , "missing tag with mysql db storage settings - " + JSON_RS_MYSQL_DB);
        {
            json nMysql                 = nResultStorage.at(JSON_RS_MYSQL_DB);
            ts.rsMysqlAddress           = parseStringValue(nMysql, JSON_RS_MYSQL_DB_ADDRESS);
            ts.rsMysqlDbName            = parseStringValue(nMysql, JSON_RS_MYSQL_DB_NAME);
            ts.rsMysqlCredentialsFile   = parseStringValue(nMysql, JSON_RS_MYSQL_DB_CRED_FILE);
        }
    }


    /*** Binaries locations ***/
    if(nRoot.count(JSON_BINARIES) != 1)
        throw RTTException(objectInfo , "missing tag with binaries locations - " + JSON_BINARIES);
    {
        json nBinaries      = nRoot.at(JSON_BINARIES);
        ts.binaryDieharder  = parseStringValue(nBinaries , JSON_BINARIES_DH);
        ts.binaryNiststs    = parseStringValue(nBinaries , JSON_BINARIES_NIST);
        ts.binaryTestU01    = parseStringValue(nBinaries , JSON_BINARIES_TU01);
    }

    /* Check existence of binaries */
    if(!Utils::fileExist(ts.binaryDieharder))
        throw RTTException(ts.objectInfo, Strings::ERR_FILE_OPEN_FAIL + ts.binaryDieharder);
    if(!Utils::fileExist(ts.binaryNiststs))
        throw RTTException(ts.objectInfo, Strings::ERR_FILE_OPEN_FAIL + ts.binaryNiststs);
    if(!Utils::fileExist(ts.binaryTestU01))
        throw RTTException(ts.objectInfo, Strings::ERR_FILE_OPEN_FAIL + ts.binaryTestU01);

    /*** Miscelaneous variables ***/
    if(nRoot.count(JSON_MISC) != 1)
        throw RTTException(objectInfo , "missing tag with miscelaneous settings - " + JSON_MISC);
    {
        json nMisc = nRoot.at(JSON_MISC);
        /** NIST STS **/
        if(nMisc.count(JSON_MISC_NIST) != 1)
            throw RTTException(objectInfo , "missing tag with nist sts misc settings - " + JSON_MISC_NIST);
        {
            json nMiscNist              = nMisc.at(JSON_MISC_NIST);
            ts.miscNiststsMainResDir    = parseDirectoryPath(nMiscNist , JSON_MISC_NIST_MAIN_RES_DIR);
        }
    }


    /*** Battery execution related variables ***/
    if(nRoot.count(JSON_EXEC) != 1)
        throw RTTException(objectInfo , "missing tag with battery execution settings - " + JSON_EXEC);
    {
        json nExec = nRoot.at(JSON_EXEC);
        ts.execMaximumThreads = parseIntegerValue(nExec , JSON_EXEC_MAX_PAR_TESTS , false);
    }

    return ts;
}

std::string ToolkitSettings::getLoggerRunLogDir() const {
    return loggerRunLogDir;
}

std::string ToolkitSettings::getLoggerRunLogFileName() const {
    return loggerRunLogDir + Utils::formatRawTime(Utils::getRawTime() , "%Y%m%d%H%M%S") + ".log";
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

int ToolkitSettings::getExecMaximumThreads() const {
    return execMaximumThreads;
}

std::string ToolkitSettings::getRsMysqlAddress() const {
    return rsMysqlAddress;
}

std::string ToolkitSettings::getRsMysqlDbName() const {
    return rsMysqlDbName;
}

std::string ToolkitSettings::getRsMysqlUserName() const {
    json nCred;
    try {
        nCred = json::parse(Utils::readFileToString(rsMysqlCredentialsFile));
    } catch (std::exception & ex) {
        throw RTTException(objectInfo,
                           "error during JSON parsing (" + rsMysqlCredentialsFile + ") - "
                           + std::string(ex.what()));
    }

    if(nCred.count(JSON_RS_MYSQL_DB_CRED_FILE_ROOT) != 1)
        throw RTTException(objectInfo, "missing root tag in credentials file - " + JSON_RS_MYSQL_DB_CRED_FILE_ROOT);
    nCred = nCred.at(JSON_RS_MYSQL_DB_CRED_FILE_ROOT);

    return parseStringValue(nCred, JSON_RS_MYSQL_DB_CRED_FILE_NAME);
}

std::string ToolkitSettings::getRsMysqlPwd() const {
    json nCred;
    try {
        nCred = json::parse(Utils::readFileToString(rsMysqlCredentialsFile));
    } catch (std::exception & ex) {
        throw RTTException(objectInfo,
                           "error during JSON parsing (" + rsMysqlCredentialsFile + ") - "
                           + std::string(ex.what()));
    }

    if(nCred.count(JSON_RS_MYSQL_DB_CRED_FILE_ROOT) != 1)
        throw RTTException(objectInfo, "missing root tag in credentials file - " + JSON_RS_MYSQL_DB_CRED_FILE_ROOT);
    nCred = nCred.at(JSON_RS_MYSQL_DB_CRED_FILE_ROOT);

    return parseStringValue(nCred, JSON_RS_MYSQL_DB_CRED_FILE_PWD);
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
        case VariableType::loggerDir: return loggerRabbitDir;
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
    case Constants::Battery::TU01_BLOCK_ALPHABIT: {
        switch(variableType) {
        case VariableType::binary:    return binaryTestU01;
        case VariableType::loggerDir: return loggerBlAlphabitDir;
        case VariableType::rsFileDir: return rsFileBlAlphabitDir;
        default:raiseBugException("invalid variable type");
        }
    }
    default:raiseBugException("invalid battery");
    }
}

std::string ToolkitSettings::parseDirectoryPath(const json::object_t & parenttag,
                                                const std::string & childTagName,
                                                bool mandatory) {
    auto rval = parseStringValue(parenttag , childTagName , mandatory);
    if(rval.back() != '/')
        rval.append("/");

    return rval;
}

std::string ToolkitSettings::parseStringValue(const json::object_t & parenttag,
                                              const std::string & childTagName,
                                              bool mandatory) {
    try {
        if(parenttag.count(childTagName) != 1) {
            if(mandatory)
                throw RTTException(objectInfo , "missing tag: " + childTagName);

            return "";
        } else {
            return parenttag.at(childTagName);
        }
    } catch (std::domain_error ex) {
        throw RTTException(objectInfo , "failed to parse value in tag: "
                           + childTagName + " - " + ex.what());
    }
}

int ToolkitSettings::parseIntegerValue(const json::object_t & parenttag,
                                               const std::string & childTagName,
                                               bool mandatory) {
    try {
        if(parenttag.count(childTagName) != 1) {
            if(mandatory)
                throw RTTException(objectInfo , "missing tag: " + childTagName);

            return 0;
        } else {
            return parenttag.at(childTagName);
        }
    } catch (std::domain_error ex) {
        throw RTTException(objectInfo , "failed to parse value in tag: "
                           + childTagName + " - " + ex.what());
    }
}

} // namespace rtt


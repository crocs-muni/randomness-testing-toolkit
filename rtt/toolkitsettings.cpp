#include "toolkitsettings.h"

namespace rtt {

const std::string ToolkitSettings::objectInfo = "Toolkit Settings";

const std::string ToolkitSettings::JSON_ROOT                         = "toolkit-settings";
const std::string ToolkitSettings::JSON_LOG                          = ToolkitSettings::JSON_ROOT + "/logger";
const std::string ToolkitSettings::JSON_LOG_DIR_PFX                  = ToolkitSettings::JSON_LOG + "/dir-prefix";
const std::string ToolkitSettings::JSON_LOG_RUN_LOG_DIR              = ToolkitSettings::JSON_LOG + "/run-log-dir";
const std::string ToolkitSettings::JSON_LOG_DH_DIR                   = ToolkitSettings::JSON_LOG + "/dieharder-dir";
const std::string ToolkitSettings::JSON_LOG_NIST_DIR                 = ToolkitSettings::JSON_LOG + "/nist-sts-dir";
const std::string ToolkitSettings::JSON_LOG_TU01SC_DIR               = ToolkitSettings::JSON_LOG + "/tu01-smallcrush-dir";
const std::string ToolkitSettings::JSON_LOG_TU01C_DIR                = ToolkitSettings::JSON_LOG + "/tu01-crush-dir";
const std::string ToolkitSettings::JSON_LOG_TU01BC_DIR               = ToolkitSettings::JSON_LOG + "/tu01-bigcrush-dir";
const std::string ToolkitSettings::JSON_LOG_TU01RAB_DIR              = ToolkitSettings::JSON_LOG + "/tu01-rabbit-dir";
const std::string ToolkitSettings::JSON_LOG_TU01AB_DIR               = ToolkitSettings::JSON_LOG + "/tu01-alphabit-dir";
const std::string ToolkitSettings::JSON_LOG_TU01BAB_DIR              = ToolkitSettings::JSON_LOG + "/tu01-blockalphabit-dir";
const std::string ToolkitSettings::JSON_RS                           = ToolkitSettings::JSON_ROOT + "/result-storage";
const std::string ToolkitSettings::JSON_RS_FILE                      = ToolkitSettings::JSON_RS + "/file";
const std::string ToolkitSettings::JSON_RS_FILE_DIR_PFX              = ToolkitSettings::JSON_RS_FILE + "/dir-prefix";
const std::string ToolkitSettings::JSON_RS_FILE_MAIN_FILE            = ToolkitSettings::JSON_RS_FILE + "/main-file";
const std::string ToolkitSettings::JSON_RS_FILE_DH_DIR               = ToolkitSettings::JSON_RS_FILE + "/dieharder-dir";
const std::string ToolkitSettings::JSON_RS_FILE_NIST_DIR             = ToolkitSettings::JSON_RS_FILE + "/nist-sts-dir";
const std::string ToolkitSettings::JSON_RS_FILE_TU01SC_DIR           = ToolkitSettings::JSON_RS_FILE + "/tu01-smallcrush-dir";
const std::string ToolkitSettings::JSON_RS_FILE_TU01C_DIR            = ToolkitSettings::JSON_RS_FILE + "/tu01-crush-dir";
const std::string ToolkitSettings::JSON_RS_FILE_TU01BC_DIR           = ToolkitSettings::JSON_RS_FILE + "/tu01-bigcrush-dir";
const std::string ToolkitSettings::JSON_RS_FILE_TU01RAB_DIR          = ToolkitSettings::JSON_RS_FILE + "/tu01-rabbit-dir";
const std::string ToolkitSettings::JSON_RS_FILE_TU01AB_DIR           = ToolkitSettings::JSON_RS_FILE + "/tu01-alphabit-dir";
const std::string ToolkitSettings::JSON_RS_FILE_TU01BAB_DIR          = ToolkitSettings::JSON_RS_FILE + "/tu01-blockalphabit-dir";
const std::string ToolkitSettings::JSON_RS_MYSQL_DB                  = ToolkitSettings::JSON_RS + "/mysql-db";
const std::string ToolkitSettings::JSON_RS_MYSQL_DB_ADDRESS          = ToolkitSettings::JSON_RS_MYSQL_DB + "/address";
const std::string ToolkitSettings::JSON_RS_MYSQL_DB_PORT             = ToolkitSettings::JSON_RS_MYSQL_DB + "/port";
const std::string ToolkitSettings::JSON_RS_MYSQL_DB_NAME             = ToolkitSettings::JSON_RS_MYSQL_DB + "/name";
const std::string ToolkitSettings::JSON_RS_MYSQL_DB_CRED_FILE        = ToolkitSettings::JSON_RS_MYSQL_DB + "/credentials-file";
const std::string ToolkitSettings::JSON_RS_MYSQL_DB_CRED_FILE_ROOT   = "credentials";
const std::string ToolkitSettings::JSON_RS_MYSQL_DB_CRED_FILE_NAME   = ToolkitSettings::JSON_RS_MYSQL_DB_CRED_FILE_ROOT + "/username";
const std::string ToolkitSettings::JSON_RS_MYSQL_DB_CRED_FILE_PWD    = ToolkitSettings::JSON_RS_MYSQL_DB_CRED_FILE_ROOT + "/password";
const std::string ToolkitSettings::JSON_BINARIES                     = ToolkitSettings::JSON_ROOT + "/binaries";
const std::string ToolkitSettings::JSON_BINARIES_NIST                = ToolkitSettings::JSON_BINARIES + "/nist-sts";
const std::string ToolkitSettings::JSON_BINARIES_DH                  = ToolkitSettings::JSON_BINARIES + "/dieharder";
const std::string ToolkitSettings::JSON_BINARIES_TU01                = ToolkitSettings::JSON_BINARIES + "/testu01";
const std::string ToolkitSettings::JSON_MISC                         = ToolkitSettings::JSON_ROOT + "/miscelaneous";
const std::string ToolkitSettings::JSON_MISC_NIST                    = ToolkitSettings::JSON_MISC + "/nist-sts";
const std::string ToolkitSettings::JSON_MISC_NIST_MAIN_RES_DIR       = ToolkitSettings::JSON_MISC_NIST + "/main-result-dir";
const std::string ToolkitSettings::JSON_EXEC                         = ToolkitSettings::JSON_ROOT + "/execution";
const std::string ToolkitSettings::JSON_EXEC_MAX_PAR_TESTS           = ToolkitSettings::JSON_EXEC + "/max-parallel-tests";
const std::string ToolkitSettings::JSON_EXEC_TEST_TIMEOUT            = ToolkitSettings::JSON_EXEC + "/test-timeout-seconds";



ToolkitSettings ToolkitSettings::getInstance(const std::string & cfgFileName) {
    json nRoot;
    try {
        nRoot = json::parse(Utils::readFileToString(cfgFileName));
    } catch (std::exception & ex) {
        throw RTTException(objectInfo,
                           getParsingErrorMessage(ex.what(), cfgFileName));
    }

    if(nRoot.count(JSON_ROOT) != 1)
        throw RTTException(objectInfo,
                           getParsingErrorMessage("missing root tag",
                                                  cfgFileName, JSON_ROOT));
    nRoot = nRoot.at(JSON_ROOT);

    ToolkitSettings ts;

    /* Variables are set below. If new battery or variables are added set them here.
     * Ideally follow organization that is already here. */

    /*** Logger directories ***/
    if(nRoot.count(Utils::getLastItemInPath(JSON_LOG)) != 1)
        throw RTTException(objectInfo ,
                           getParsingErrorMessage("missing tag with logger settings",
                                                  cfgFileName, JSON_LOG));
    {
        json nLogger            = nRoot.at(Utils::getLastItemInPath(JSON_LOG));
        auto dirPfx             = parseDirectoryPath(nLogger , JSON_LOG_DIR_PFX , cfgFileName ,  false);
        ts.loggerRunLogDir      = dirPfx + parseDirectoryPath(nLogger , JSON_LOG_RUN_LOG_DIR , cfgFileName);
        ts.loggerDieharderDir   = dirPfx + parseDirectoryPath(nLogger , JSON_LOG_DH_DIR , cfgFileName);
        ts.loggerNiststsDir     = dirPfx + parseDirectoryPath(nLogger , JSON_LOG_NIST_DIR , cfgFileName);
        ts.loggerSCrushDir      = dirPfx + parseDirectoryPath(nLogger , JSON_LOG_TU01SC_DIR , cfgFileName);
        ts.loggerCrushDir       = dirPfx + parseDirectoryPath(nLogger , JSON_LOG_TU01C_DIR , cfgFileName);
        ts.loggerBCrushDir      = dirPfx + parseDirectoryPath(nLogger , JSON_LOG_TU01BC_DIR , cfgFileName);
        ts.loggerRabbitDir      = dirPfx + parseDirectoryPath(nLogger , JSON_LOG_TU01RAB_DIR , cfgFileName);
        ts.loggerAlphabitDir    = dirPfx + parseDirectoryPath(nLogger , JSON_LOG_TU01AB_DIR , cfgFileName);
        ts.loggerBlAlphabitDir  = dirPfx + parseDirectoryPath(nLogger , JSON_LOG_TU01BAB_DIR , cfgFileName);
    }

    /*** Result storage settings ***/
    if(nRoot.count(Utils::getLastItemInPath(JSON_RS)) != 1)
        throw RTTException(objectInfo ,
                           getParsingErrorMessage("missing tag with result storage settings",
                                                  cfgFileName, JSON_RS));
    {
        json nResultStorage = nRoot.at(Utils::getLastItemInPath(JSON_RS));

        /** File storage **/
        if(nResultStorage.count(Utils::getLastItemInPath(JSON_RS_FILE)) != 1)
            throw RTTException(objectInfo ,
                               getParsingErrorMessage("missing tag with file storage settings",
                                                      cfgFileName, JSON_RS_FILE));
        {
            json nFile              = nResultStorage.at(Utils::getLastItemInPath(JSON_RS_FILE));
            auto dirPfx             = parseDirectoryPath(nFile , JSON_RS_FILE_DIR_PFX , cfgFileName , false);
            ts.rsFileOutFile        = parseStringValue(nFile , JSON_RS_FILE_MAIN_FILE , cfgFileName);
            ts.rsFileDieharderDir   = dirPfx + parseDirectoryPath(nFile , JSON_RS_FILE_DH_DIR , cfgFileName);
            ts.rsFileNiststsDir     = dirPfx + parseDirectoryPath(nFile , JSON_RS_FILE_NIST_DIR , cfgFileName);
            ts.rsFileSCrushDir      = dirPfx + parseDirectoryPath(nFile , JSON_RS_FILE_TU01SC_DIR , cfgFileName);
            ts.rsFileCrushDir       = dirPfx + parseDirectoryPath(nFile , JSON_RS_FILE_TU01C_DIR , cfgFileName);
            ts.rsFileBCrushDir      = dirPfx + parseDirectoryPath(nFile , JSON_RS_FILE_TU01BC_DIR , cfgFileName);
            ts.rsFileRabbitDir      = dirPfx + parseDirectoryPath(nFile , JSON_RS_FILE_TU01RAB_DIR , cfgFileName);
            ts.rsFileAlphabitDir    = dirPfx + parseDirectoryPath(nFile , JSON_RS_FILE_TU01AB_DIR , cfgFileName);
            ts.rsFileBlAlphabitDir  = dirPfx + parseDirectoryPath(nFile , JSON_RS_FILE_TU01BAB_DIR , cfgFileName);
        }

        /** Database storage **/
        if(nResultStorage.count(Utils::getLastItemInPath(JSON_RS_MYSQL_DB)) != 1)
            throw RTTException(objectInfo ,
                               getParsingErrorMessage("missing tag with mysql db settings",
                                                      cfgFileName, JSON_RS_MYSQL_DB));
        {
            json nMysql                 = nResultStorage.at(Utils::getLastItemInPath(JSON_RS_MYSQL_DB));
            ts.rsMysqlAddress           = parseStringValue(nMysql, JSON_RS_MYSQL_DB_ADDRESS , cfgFileName);
            ts.rsMysqlPort              = parseStringValue(nMysql, JSON_RS_MYSQL_DB_PORT , cfgFileName);
            ts.rsMysqlDbName            = parseStringValue(nMysql, JSON_RS_MYSQL_DB_NAME , cfgFileName);
            ts.rsMysqlCredentialsFile   = parseStringValue(nMysql, JSON_RS_MYSQL_DB_CRED_FILE , cfgFileName);
        }
    }


    /*** Binaries locations ***/
    if(nRoot.count(Utils::getLastItemInPath(JSON_BINARIES)) != 1)
        throw RTTException(objectInfo ,
                           getParsingErrorMessage("missing tag with binaries locations",
                                                  cfgFileName, JSON_BINARIES));
    {
        json nBinaries      = nRoot.at(Utils::getLastItemInPath(JSON_BINARIES));
        ts.binaryDieharder  = parseStringValue(nBinaries , JSON_BINARIES_DH , cfgFileName);
        ts.binaryNiststs    = parseStringValue(nBinaries , JSON_BINARIES_NIST , cfgFileName);
        ts.binaryTestU01    = parseStringValue(nBinaries , JSON_BINARIES_TU01 , cfgFileName);
    }

    /* Check existence of binaries */
    if(!Utils::fileExist(ts.binaryDieharder))
        throw RTTException(ts.objectInfo, Strings::ERR_FILE_OPEN_FAIL + ts.binaryDieharder);
    if(!Utils::fileExist(ts.binaryNiststs))
        throw RTTException(ts.objectInfo, Strings::ERR_FILE_OPEN_FAIL + ts.binaryNiststs);
    if(!Utils::fileExist(ts.binaryTestU01))
        throw RTTException(ts.objectInfo, Strings::ERR_FILE_OPEN_FAIL + ts.binaryTestU01);

    /*** Miscelaneous variables ***/
    if(nRoot.count(Utils::getLastItemInPath(JSON_MISC)) != 1)
        throw RTTException(objectInfo ,
                           getParsingErrorMessage("missing tag with miscelaneous settings",
                                                  cfgFileName, JSON_MISC));
    {
        json nMisc = nRoot.at(Utils::getLastItemInPath(JSON_MISC));
        /** NIST STS **/
        if(nMisc.count(Utils::getLastItemInPath(JSON_MISC_NIST)) != 1)
            throw RTTException(objectInfo ,
                               getParsingErrorMessage("missing tag with nist sts misc settings",
                                                      cfgFileName, JSON_MISC_NIST));
        {
            json nMiscNist              = nMisc.at(Utils::getLastItemInPath(JSON_MISC_NIST));
            ts.miscNiststsMainResDir    = parseDirectoryPath(nMiscNist , JSON_MISC_NIST_MAIN_RES_DIR , cfgFileName);
        }
    }


    /*** Battery execution related variables ***/
    if(nRoot.count(Utils::getLastItemInPath(JSON_EXEC)) != 1)
        throw RTTException(objectInfo ,
                           getParsingErrorMessage("missing tag with battery execution settings",
                                                  cfgFileName, JSON_EXEC));
    {
        json nExec = nRoot.at(Utils::getLastItemInPath(JSON_EXEC));
        ts.execMaximumThreads = parseIntegerValue(nExec , JSON_EXEC_MAX_PAR_TESTS , cfgFileName);
        ts.execTestTimeout = parseIntegerValue(nExec, JSON_EXEC_TEST_TIMEOUT, cfgFileName);
    }

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

int ToolkitSettings::getExecMaximumThreads() const {
    return execMaximumThreads;
}

std::string ToolkitSettings::getRsMysqlAddress() const {
    return rsMysqlAddress;
}

std::string ToolkitSettings::getRsMysqlPort() const {
   return rsMysqlPort;
}

std::string ToolkitSettings::getRsMysqlDbName() const {
    return rsMysqlDbName;
}

int ToolkitSettings::getExecTestTimeout() const {
    return execTestTimeout;
}

std::string ToolkitSettings::getRsMysqlUserName() const {
    json nCred;
    try {
        nCred = json::parse(Utils::readFileToString(rsMysqlCredentialsFile));
    } catch (std::exception & ex) {
        throw RTTException(objectInfo,
                           getParsingErrorMessage(ex.what(), rsMysqlCredentialsFile));
    }

    if(nCred.count(JSON_RS_MYSQL_DB_CRED_FILE_ROOT) != 1)
        throw RTTException(objectInfo,
                           getParsingErrorMessage("missing root tag in credentials file",
                                                  rsMysqlCredentialsFile, JSON_RS_MYSQL_DB_CRED_FILE_ROOT));
    nCred = nCred.at(JSON_RS_MYSQL_DB_CRED_FILE_ROOT);

    return parseStringValue(nCred, JSON_RS_MYSQL_DB_CRED_FILE_NAME, rsMysqlCredentialsFile);
}

std::string ToolkitSettings::getRsMysqlPwd() const {
    json nCred;
    try {
        nCred = json::parse(Utils::readFileToString(rsMysqlCredentialsFile));
    } catch (std::exception & ex) {
        throw RTTException(objectInfo,
                           getParsingErrorMessage(ex.what(), rsMysqlCredentialsFile));
    }

    if(nCred.count(JSON_RS_MYSQL_DB_CRED_FILE_ROOT) != 1)
        throw RTTException(objectInfo,
                           getParsingErrorMessage("missing root tag in credentials file",
                                                  rsMysqlCredentialsFile, JSON_RS_MYSQL_DB_CRED_FILE_ROOT));
    nCred = nCred.at(JSON_RS_MYSQL_DB_CRED_FILE_ROOT);

    return parseStringValue(nCred, JSON_RS_MYSQL_DB_CRED_FILE_PWD, rsMysqlCredentialsFile);
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

std::string ToolkitSettings::parseDirectoryPath(const json & parenttag,
                                                const std::string & childTagPath,
                                                const std::string & cfgFile,
                                                bool mandatory) {
    auto rval = parseStringValue(parenttag , childTagPath , cfgFile , mandatory);
    if(!rval.empty() && rval.back() != '/')
        rval.append("/");

    return rval;
}

std::string ToolkitSettings::parseStringValue(const json & parenttag,
                                              const std::string & childTagPath,
                                              const std::string & cfgFile,
                                              bool mandatory) {
    try {
        auto childTagName = Utils::getLastItemInPath(childTagPath);
        if(parenttag.count(childTagName) != 1) {
            if(mandatory)
                throw RTTException(objectInfo,
                                   getParsingErrorMessage("missing tag", cfgFile, childTagPath));


            return "";
        } else {
            return parenttag.at(childTagName);
        }
    } catch (std::domain_error ex) {
        throw RTTException(objectInfo,
                           getParsingErrorMessage(ex.what(), cfgFile, childTagPath));
    }
}

int ToolkitSettings::parseIntegerValue(const json & parenttag,
                                       const std::string & childTagPath,
                                       const std::string & cfgFile,
                                       bool mandatory) {
    try {
        auto childTagName = Utils::getLastItemInPath(childTagPath);
        if(parenttag.count(childTagName) != 1) {
            if(mandatory)
                throw RTTException(objectInfo,
                                   getParsingErrorMessage("missing tag", cfgFile, childTagPath));

            return 0;
        } else {
            return parenttag.at(childTagName);
        }
    } catch (std::domain_error ex) {
        throw RTTException(objectInfo,
                           getParsingErrorMessage(ex.what(), cfgFile, childTagPath));
    }
}

std::string ToolkitSettings::getParsingErrorMessage(const std::string & mess,
                                                    const std::string & cfgFile,
                                                    const std::string & tagPath) {
    std::stringstream rval;
    rval << mess << "; file: " << cfgFile;
    if(!tagPath.empty())
        rval << "; invalid tag: " << tagPath;

    return rval.str();
}

} // namespace rtt


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
const std::string ToolkitSettings::JSON_MISC                         = ToolkitSettings::JSON_ROOT + "/miscellaneous";
const std::string ToolkitSettings::JSON_MISC_NIST                    = ToolkitSettings::JSON_MISC + "/nist-sts";
const std::string ToolkitSettings::JSON_MISC_NIST_MAIN_RES_DIR       = ToolkitSettings::JSON_MISC_NIST + "/main-result-dir";
const std::string ToolkitSettings::JSON_EXEC                         = ToolkitSettings::JSON_ROOT + "/execution";
const std::string ToolkitSettings::JSON_EXEC_MAX_PAR_TESTS           = ToolkitSettings::JSON_EXEC + "/max-parallel-tests";
const std::string ToolkitSettings::JSON_EXEC_TEST_TIMEOUT            = ToolkitSettings::JSON_EXEC + "/test-timeout-seconds";



ToolkitSettings ToolkitSettings::getInstance(const std::string & cfgFileName) {
    ToolkitSettings ts;
    ts.cfgFileName = cfgFileName;

    json nRoot;
    try {
        nRoot = json::parse(Utils::readFileToString(ts.cfgFileName));
    } catch (std::exception & ex) {
        throw RTTException(objectInfo, ts.getParsingErrorMessage(ex.what()));
    }

    if(nRoot.count(JSON_ROOT) != 1)
        throw RTTException(objectInfo, ts.getParsingErrorMessage("missing root tag", JSON_ROOT));
    nRoot = nRoot.at(JSON_ROOT);

    /* Variables are set below. If new battery or variables are added set them here.
     * Ideally follow organization that is already here. */

    /*** Logger directories ***/
    if(nRoot.count(Utils::getLastItemInPath(JSON_LOG)) != 1)
        throw RTTException(objectInfo ,
                           ts.getParsingErrorMessage("missing tag with logger settings", JSON_LOG));
    {
        json nLogger            = nRoot.at(Utils::getLastItemInPath(JSON_LOG));
        auto dirPfx             = ts.parseDirectoryPath(nLogger , JSON_LOG_DIR_PFX ,  false);
        ts.loggerRunLogDir      = dirPfx + ts.parseDirectoryPath(nLogger , JSON_LOG_RUN_LOG_DIR);
        ts.loggerDieharderDir   = dirPfx + ts.parseDirectoryPath(nLogger , JSON_LOG_DH_DIR);
        ts.loggerNiststsDir     = dirPfx + ts.parseDirectoryPath(nLogger , JSON_LOG_NIST_DIR);
        ts.loggerSCrushDir      = dirPfx + ts.parseDirectoryPath(nLogger , JSON_LOG_TU01SC_DIR);
        ts.loggerCrushDir       = dirPfx + ts.parseDirectoryPath(nLogger , JSON_LOG_TU01C_DIR);
        ts.loggerBCrushDir      = dirPfx + ts.parseDirectoryPath(nLogger , JSON_LOG_TU01BC_DIR);
        ts.loggerRabbitDir      = dirPfx + ts.parseDirectoryPath(nLogger , JSON_LOG_TU01RAB_DIR);
        ts.loggerAlphabitDir    = dirPfx + ts.parseDirectoryPath(nLogger , JSON_LOG_TU01AB_DIR);
        ts.loggerBlAlphabitDir  = dirPfx + ts.parseDirectoryPath(nLogger , JSON_LOG_TU01BAB_DIR);
    }

    /*** Result storage settings - not mandatory ***/
    if(nRoot.count(Utils::getLastItemInPath(JSON_RS)) == 1) {
        json nResultStorage = nRoot.at(Utils::getLastItemInPath(JSON_RS));

        /** File storage - not mandatory **/
        if(nResultStorage.count(Utils::getLastItemInPath(JSON_RS_FILE)) == 1) {
            json nFile              = nResultStorage.at(Utils::getLastItemInPath(JSON_RS_FILE));
            auto dirPfx             = ts.parseDirectoryPath(nFile , JSON_RS_FILE_DIR_PFX , false);
            ts.rsFileOutFile        = ts.parseStringValue(nFile , JSON_RS_FILE_MAIN_FILE , false);
            ts.rsFileDieharderDir   = dirPfx + ts.parseDirectoryPath(nFile , JSON_RS_FILE_DH_DIR , false);
            ts.rsFileNiststsDir     = dirPfx + ts.parseDirectoryPath(nFile , JSON_RS_FILE_NIST_DIR , false);
            ts.rsFileSCrushDir      = dirPfx + ts.parseDirectoryPath(nFile , JSON_RS_FILE_TU01SC_DIR , false);
            ts.rsFileCrushDir       = dirPfx + ts.parseDirectoryPath(nFile , JSON_RS_FILE_TU01C_DIR , false);
            ts.rsFileBCrushDir      = dirPfx + ts.parseDirectoryPath(nFile , JSON_RS_FILE_TU01BC_DIR , false);
            ts.rsFileRabbitDir      = dirPfx + ts.parseDirectoryPath(nFile , JSON_RS_FILE_TU01RAB_DIR , false);
            ts.rsFileAlphabitDir    = dirPfx + ts.parseDirectoryPath(nFile , JSON_RS_FILE_TU01AB_DIR , false);
            ts.rsFileBlAlphabitDir  = dirPfx + ts.parseDirectoryPath(nFile , JSON_RS_FILE_TU01BAB_DIR , false);
        }

        /*** MySQL Database storage - not mandatory ***/
        if(nResultStorage.count(Utils::getLastItemInPath(JSON_RS_MYSQL_DB)) == 1) {
            json nMysql                 = nResultStorage.at(Utils::getLastItemInPath(JSON_RS_MYSQL_DB));
            ts.rsMysqlAddress           = ts.parseStringValue(nMysql, JSON_RS_MYSQL_DB_ADDRESS , false);
            ts.rsMysqlPort              = ts.parseStringValue(nMysql, JSON_RS_MYSQL_DB_PORT , false);
            ts.rsMysqlDbName            = ts.parseStringValue(nMysql, JSON_RS_MYSQL_DB_NAME , false);
            ts.rsMysqlCredentialsFile   = ts.parseStringValue(nMysql, JSON_RS_MYSQL_DB_CRED_FILE , false);
        }
    }

    /*** Binaries locations ***/
    if(nRoot.count(Utils::getLastItemInPath(JSON_BINARIES)) != 1)
        throw RTTException(objectInfo ,
                           ts.getParsingErrorMessage("missing tag with binaries locations", JSON_BINARIES));
    {
        json nBinaries      = nRoot.at(Utils::getLastItemInPath(JSON_BINARIES));
        ts.binaryDieharder  = ts.parseStringValue(nBinaries , JSON_BINARIES_DH);
        ts.binaryNiststs    = ts.parseStringValue(nBinaries , JSON_BINARIES_NIST);
        ts.binaryTestU01    = ts.parseStringValue(nBinaries , JSON_BINARIES_TU01);
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
                           ts.getParsingErrorMessage("missing tag with miscellaneous settings", JSON_MISC));
    {
        json nMisc = nRoot.at(Utils::getLastItemInPath(JSON_MISC));
        /** NIST STS **/
        if(nMisc.count(Utils::getLastItemInPath(JSON_MISC_NIST)) != 1)
            throw RTTException(objectInfo ,
                               ts.getParsingErrorMessage("missing tag with nist sts misc settings", JSON_MISC_NIST));
        {
            json nMiscNist              = nMisc.at(Utils::getLastItemInPath(JSON_MISC_NIST));
            ts.miscNiststsMainResDir    = ts.parseDirectoryPath(nMiscNist , JSON_MISC_NIST_MAIN_RES_DIR);
        }
    }


    /*** Battery execution related variables ***/
    if(nRoot.count(Utils::getLastItemInPath(JSON_EXEC)) != 1)
        throw RTTException(objectInfo ,
                           ts.getParsingErrorMessage("missing tag with battery execution settings", JSON_EXEC));
    {
        bool hasThreadsFromEnv = false;
        json nExec = nRoot.at(Utils::getLastItemInPath(JSON_EXEC));

        ts.execTestTimeout = ts.parseIntegerValue(nExec, JSON_EXEC_TEST_TIMEOUT);

        if(const char* envThreads = std::getenv("RTT_PARALLEL")) {
            ts.execMaximumThreads = atoi(envThreads);
            hasThreadsFromEnv = ts.execMaximumThreads > 0 && ts.execMaximumThreads < 32000;
        }
        if (!hasThreadsFromEnv) {
            ts.execMaximumThreads = ts.parseIntegerValue(nExec, JSON_EXEC_MAX_PAR_TESTS);
        }
    }

    return ts;
}

std::string ToolkitSettings::getLoggerRunLogDir() const {
    return loggerRunLogDir;
}

std::string ToolkitSettings::getRsFileOutFile() const {
    return returnIfNonEmpty(rsFileOutFile, JSON_RS_FILE_MAIN_FILE);
}

std::string ToolkitSettings::getLoggerBatteryDir(const BatteryArg &battery) const {
    return getBatteryVariable(VariableType::loggerDir , battery);
}

std::string ToolkitSettings::getRsFileBatteryDir(const BatteryArg &battery) const {
    return getBatteryVariable(VariableType::rsFileDir , battery);
}

std::string ToolkitSettings::getBinaryBattery(const BatteryArg &battery) const {
    return getBatteryVariable(VariableType::binary , battery);
}

std::string ToolkitSettings::getMiscNiststsMainResDir() const {
    return miscNiststsMainResDir;
}

int ToolkitSettings::getExecMaximumThreads() const {
    return execMaximumThreads;
}

std::string ToolkitSettings::getRsMysqlAddress() const {
    return returnIfNonEmpty(rsMysqlAddress, JSON_RS_MYSQL_DB_ADDRESS);
}

std::string ToolkitSettings::getRsMysqlPort() const {
    return returnIfNonEmpty(rsMysqlPort, JSON_RS_MYSQL_DB_PORT);
}

std::string ToolkitSettings::getRsMysqlDbName() const {
    return returnIfNonEmpty(rsMysqlDbName, JSON_RS_MYSQL_DB_NAME);
}

int ToolkitSettings::getExecTestTimeout() const {
    return execTestTimeout;
}

std::string ToolkitSettings::getRsMysqlUserName() const {
    return getTagFromCredentials(JSON_RS_MYSQL_DB_CRED_FILE_NAME);
}

std::string ToolkitSettings::getRsMysqlPwd() const {
    return getTagFromCredentials(JSON_RS_MYSQL_DB_CRED_FILE_PWD);
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
                                                const BatteryArg & battery) const {
    /* This is main getter so that all of it is in one place (for future modifications).
     * If new battery is added - create new case for that constant, add it below.
     * If new VariableType is added - add its case into each battery. Also add method
     * for accessing it (see methods getLoggerBatteryDir, getBinaryBattery, etc...)*/
    switch(battery.getBatteryId()) {
    case Constants::BatteryID::NIST_STS: {
        switch(variableType) {
        case VariableType::binary:    return binaryNiststs;
        case VariableType::loggerDir: return loggerNiststsDir;
        case VariableType::rsFileDir:
                return returnIfNonEmpty(rsFileNiststsDir, JSON_RS_FILE_NIST_DIR);
        default:raiseBugException("invalid variable type");
        }
    }
    case Constants::BatteryID::DIEHARDER: {
        switch(variableType) {
        case VariableType::binary:    return binaryDieharder;
        case VariableType::loggerDir: return loggerDieharderDir;
        case VariableType::rsFileDir:
                return returnIfNonEmpty(rsFileDieharderDir, JSON_RS_FILE_DH_DIR);
        default:raiseBugException("invalid variable type");
        }
    }
    case Constants::BatteryID::TU01_SMALLCRUSH: {
        switch(variableType) {
        case VariableType::binary:    return binaryTestU01;
        case VariableType::loggerDir: return loggerSCrushDir;
        case VariableType::rsFileDir:
                return returnIfNonEmpty(rsFileSCrushDir, JSON_RS_FILE_TU01SC_DIR);
        default:raiseBugException("invalid variable type");
        }
    }
    case Constants::BatteryID::TU01_CRUSH: {
        switch(variableType) {
        case VariableType::binary:    return binaryTestU01;
        case VariableType::loggerDir: return loggerCrushDir;
        case VariableType::rsFileDir:
                return returnIfNonEmpty(rsFileCrushDir, JSON_RS_FILE_TU01C_DIR);
        default:raiseBugException("invalid variable type");
        }
    }
    case Constants::BatteryID::TU01_BIGCRUSH: {
        switch(variableType) {
        case VariableType::binary:    return binaryTestU01;
        case VariableType::loggerDir: return loggerBCrushDir;
        case VariableType::rsFileDir:
                return returnIfNonEmpty(rsFileBCrushDir, JSON_RS_FILE_TU01BC_DIR);
        default:raiseBugException("invalid variable type");
        }
    }
    case Constants::BatteryID::TU01_RABBIT: {
        switch(variableType) {
        case VariableType::binary:    return binaryTestU01;
        case VariableType::loggerDir: return loggerRabbitDir;
        case VariableType::rsFileDir:
                return returnIfNonEmpty(rsFileRabbitDir, JSON_RS_FILE_TU01RAB_DIR);
        default:raiseBugException("invalid variable type");
        }
    }
    case Constants::BatteryID::TU01_ALPHABIT: {
        switch(variableType) {
        case VariableType::binary:    return binaryTestU01;
        case VariableType::loggerDir: return loggerAlphabitDir;
        case VariableType::rsFileDir:
                return returnIfNonEmpty(rsFileAlphabitDir, JSON_RS_FILE_TU01AB_DIR);
        default:raiseBugException("invalid variable type");
        }
    }
    case Constants::BatteryID::TU01_BLOCK_ALPHABIT: {
        switch(variableType) {
        case VariableType::binary:    return binaryTestU01;
        case VariableType::loggerDir: return loggerBlAlphabitDir;
        case VariableType::rsFileDir:
                return returnIfNonEmpty(rsFileBlAlphabitDir, JSON_RS_FILE_TU01BAB_DIR);
        default:raiseBugException("invalid variable type");
        }
    }
    default:raiseBugException("invalid battery");
    }
}

std::string ToolkitSettings::parseDirectoryPath(const json & parenttag,
                                                const std::string & childTagPath,
                                                bool mandatory) const {
    auto rval = parseStringValue(parenttag , childTagPath , mandatory);
    if(!rval.empty() && rval.back() != '/')
        rval.append("/");

    return rval;
}

std::string ToolkitSettings::parseStringValue(const json & parenttag,
                                              const std::string & childTagPath,
                                              bool mandatory) const {
    try {
        auto childTagName = Utils::getLastItemInPath(childTagPath);
        if(parenttag.count(childTagName) != 1) {
            if(mandatory)
                throw RTTException(objectInfo,
                                   getParsingErrorMessage("missing tag", childTagPath));


            return "";
        } else {
            return parenttag.at(childTagName);
        }
    } catch (std::domain_error ex) {
        throw RTTException(objectInfo,
                           getParsingErrorMessage(ex.what(), childTagPath));
    }
}

int ToolkitSettings::parseIntegerValue(const json & parenttag,
                                       const std::string & childTagPath,
                                       bool mandatory) const {
    try {
        auto childTagName = Utils::getLastItemInPath(childTagPath);
        if(parenttag.count(childTagName) != 1) {
            if(mandatory)
                throw RTTException(objectInfo,
                                   getParsingErrorMessage("missing tag", childTagPath));

            return 0;
        } else {
            return parenttag.at(childTagName);
        }
    } catch (std::domain_error ex) {
        throw RTTException(objectInfo,
                           getParsingErrorMessage(ex.what(), childTagPath));
    }
}

std::string ToolkitSettings::getTagFromCredentials(const std::string & tagPath) const {
    if(rsMysqlCredentialsFile.empty())
        throw RTTException(objectInfo, getParsingErrorMessage(
                               "missing or empty tag", JSON_RS_MYSQL_DB_CRED_FILE));
    json nCred;
    try {
        nCred = json::parse(Utils::readFileToString(rsMysqlCredentialsFile));
    } catch (std::exception & ex) {
        throw RTTException(objectInfo,
                           getParsingErrorMessage(ex.what(), {}, rsMysqlCredentialsFile));
    }

    if(nCred.count(JSON_RS_MYSQL_DB_CRED_FILE_ROOT) != 1)
        throw RTTException(objectInfo, getParsingErrorMessage(
                               "missing root tag in credentials file",
                               JSON_RS_MYSQL_DB_CRED_FILE_ROOT,
                               rsMysqlCredentialsFile));

    nCred = nCred.at(JSON_RS_MYSQL_DB_CRED_FILE_ROOT);
    auto rval = parseStringValue(nCred, tagPath, false);
    return returnIfNonEmpty(rval, tagPath, rsMysqlCredentialsFile);
}

std::string ToolkitSettings::returnIfNonEmpty(const std::string & value,
                                              const std::string & originTag,
                                              const std::string & originFile) const {
    if(value.empty())
        throw RTTException(objectInfo, getParsingErrorMessage(
                               "missing or empty tag", originTag, originFile));
    return value;
}

std::string ToolkitSettings::getParsingErrorMessage(const std::string & mess,
                                                    const std::string & tagPath,
                                                    const std::string & fileName) const {
    std::stringstream rval;
    rval << mess << "; file: ";
    if(!fileName.empty()) {
        rval << fileName;
    } else {
        rval << cfgFileName;
    }
    if(!tagPath.empty())
        rval << "; invalid tag: " << tagPath;

    return rval.str();
}

} // namespace rtt


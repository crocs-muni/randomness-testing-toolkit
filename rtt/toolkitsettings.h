#ifndef RTT_TOOLKITSETTINGS_H
#define RTT_TOOLKITSETTINGS_H

#include "rtt/constants.h"
#include "rtt/bugexception.h"
#include "rtt/rttexception.h"

#include "libs/moderncppjson/json.hpp"

namespace rtt {

using json = nlohmann::json;

class ToolkitSettings {
public:
    /* Get object */
    static ToolkitSettings getInstance(const std::string & cfgFileName);

    /* Getters for variables */
    std::string getLoggerRunLogDir() const;

    std::string getLoggerRunLogFileName() const;

    std::string getRsFileOutFile() const;

    std::string getLoggerBatteryDir(Constants::Battery battery) const;

    std::string getRsFileBatteryDir(Constants::Battery battery) const;

    std::string getBinaryBattery(Constants::Battery battery) const;

    std::string getMiscNiststsMainResDir() const;

    int getExecMaximumThreads() const;

    std::string getRsMysqlAddress() const;

    std::string getRsMysqlUserName() const;

    std::string getRsMysqlPwd() const;

    std::string getRsMysqlDbName() const;

private:
    /* JSON tag names constants */
    static const std::string JSON_ROOT;
    static const std::string JSON_LOG;
    static const std::string JSON_LOG_DIR_PFX;
    static const std::string JSON_LOG_RUN_LOG_DIR;
    static const std::string JSON_LOG_DH_DIR;
    static const std::string JSON_LOG_NIST_DIR;
    static const std::string JSON_LOG_TU01SC_DIR;
    static const std::string JSON_LOG_TU01C_DIR;
    static const std::string JSON_LOG_TU01BC_DIR;
    static const std::string JSON_LOG_TU01RAB_DIR;
    static const std::string JSON_LOG_TU01AB_DIR;
    static const std::string JSON_LOG_TU01BAB_DIR;
    static const std::string JSON_RS;
    static const std::string JSON_RS_FILE;
    static const std::string JSON_RS_FILE_DIR_PFX;
    static const std::string JSON_RS_FILE_MAIN_FILE;
    static const std::string JSON_RS_FILE_DH_DIR;
    static const std::string JSON_RS_FILE_NIST_DIR;
    static const std::string JSON_RS_FILE_TU01SC_DIR;
    static const std::string JSON_RS_FILE_TU01C_DIR;
    static const std::string JSON_RS_FILE_TU01BC_DIR;
    static const std::string JSON_RS_FILE_TU01RAB_DIR;
    static const std::string JSON_RS_FILE_TU01AB_DIR;
    static const std::string JSON_RS_FILE_TU01BAB_DIR;
    static const std::string JSON_RS_MYSQL_DB;
    static const std::string JSON_RS_MYSQL_DB_ADDRESS;
    static const std::string JSON_RS_MYSQL_DB_NAME;
    static const std::string JSON_RS_MYSQL_DB_CRED_FILE;
    static const std::string JSON_RS_MYSQL_DB_CRED_FILE_ROOT;
    static const std::string JSON_RS_MYSQL_DB_CRED_FILE_NAME;
    static const std::string JSON_RS_MYSQL_DB_CRED_FILE_PWD;
    static const std::string JSON_BINARIES;
    static const std::string JSON_BINARIES_NIST;
    static const std::string JSON_BINARIES_DH;
    static const std::string JSON_BINARIES_TU01;
    static const std::string JSON_MISC;
    static const std::string JSON_MISC_NIST;
    static const std::string JSON_MISC_NIST_MAIN_RES_DIR;
    static const std::string JSON_EXEC;
    static const std::string JSON_EXEC_MAX_PAR_TESTS;

    /* Variable types for getters. Should a new variable be added,
     * add it here too. */
    enum class VariableType {
        loggerDir,
        rsFileDir,
        binary
    };

    /* Member variables */
    static const std::string objectInfo;

    std::string loggerRunLogDir;
    std::string loggerDieharderDir;
    std::string loggerNiststsDir;
    std::string loggerSCrushDir;
    std::string loggerCrushDir;
    std::string loggerBCrushDir;
    std::string loggerRabbitDir;
    std::string loggerAlphabitDir;
    std::string loggerBlAlphabitDir;

    std::string rsFileOutFile;
    std::string rsFileDieharderDir;
    std::string rsFileNiststsDir;
    std::string rsFileSCrushDir;
    std::string rsFileCrushDir;
    std::string rsFileBCrushDir;
    std::string rsFileRabbitDir;
    std::string rsFileAlphabitDir;
    std::string rsFileBlAlphabitDir;

    std::string rsMysqlAddress;
    std::string rsMysqlDbName;
    std::string rsMysqlCredentialsFile;

    std::string binaryDieharder;
    std::string binaryNiststs;
    std::string binaryTestU01;

    std::string miscNiststsMainResDir;

    int execMaximumThreads = 1;

    /* Private methods */
    ToolkitSettings() {}

    std::string getBatteryVariable(VariableType variableType ,
                                   Constants::Battery battery) const;

    static std::string parseDirectoryPath(const json & parentNode,
                                          const std::string & childTagName,
                                          const std::string & cfgFile,
                                          bool mandatory = true);

    static std::string parseStringValue(const json & parentNode,
                                        const std::string & childTagName,
                                        const std::string & cfgFile,
                                        bool mandatory = true);

    static int parseIntegerValue(const json & parentNode,
                                 const std::string & childTagName,
                                 const std::string & cfgFile,
                                 bool mandatory = true);

    static std::string getParsingErrorMessage(const std::string & mess,
                                              const std::string & cfgFile,
                                              const std::string & tagPath = "");
};

} // namespace rtt

#endif // RTT_TOOLKITSETTINGS_H

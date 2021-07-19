#ifndef RTT_TOOLKITSETTINGS_H
#define RTT_TOOLKITSETTINGS_H

#include "rtt/constants.h"
#include "rtt/bugexception.h"
#include "rtt/rttexception.h"
#include "rtt/clinterface/batteryarg.h"

#include "libs/moderncppjson/json.hpp"

namespace rtt {

using json = nlohmann::json;
using namespace clinterface;

class ToolkitSettings {
public:
    /**
     * @brief getInstance Creates initialized object
     * @param cfgFileName Path to file with toolkit configuration
     * @return instance
     */
    static ToolkitSettings getInstance(const std::string & cfgFileName);

    /**
     * @brief getLoggerRunLogDir
     * @return Path to directory in which the log of the program run will be stored
     */
    std::string getLoggerRunLogDir() const;

    /**
     * @brief getRsFileOutFile
     * @return Path to table with results (FileStorage)
     */
    std::string getRsFileOutFile() const;

    /**
     * @brief getLoggerBatteryDir
     * @param battery
     * @return Path to directory in which the log of the battery executable run will be stored
     */
    std::string getLoggerBatteryDir(const BatteryArg & battery) const;

    /**
     * @brief getRsFileBatteryDir
     * @param battery
     * @return Path to directory in which the report of program run will be stored (FileStorage)
     */
    std::string getRsFileBatteryDir(const BatteryArg & battery) const;

    /**
     * @brief getBinaryBattery
     * @param battery
     * @return Path to executable of a given battery
     */
    std::string getBinaryBattery(const BatteryArg & battery) const;

    /**
     * @brief getMiscNiststsMainResDir
     * @return Path to NIST STS main result directory
     */
    std::string getMiscNiststsMainResDir() const;

    /**
     * @brief getRsMysqlAddress
     * @return IPv4 address of MySQL database (MysqlStorage)
     */
    std::string getRsMysqlAddress() const;

    /**
     * @brief getRsMysqlPort
     * @return Port of MySQL database (MysqlStorage)
     */
    std::string getRsMysqlPort() const;

    /**
     * @brief getRsMysqlUserName
     * @return Username for accessing database (MysqlStorage)
     */
    std::string getRsMysqlUserName() const;

    /**
     * @brief getRsMysqlPwd
     * @return Password for accessing database (MysqlStorage)
     */
    std::string getRsMysqlPwd() const;

    /**
     * @brief getRsMysqlDbName
     * @return Name of the database (MysqlStorage)
     */
    std::string getRsMysqlDbName() const;

    /**
     * @brief getExecTestTimeout
     * @return Battery test execution timeout in seconds
     */
    int getExecTestTimeout() const;

    /**
     * @brief getExecMaximumThreads
     * @return Maximum battery tests running in parallel
     */
    int getExecMaximumThreads() const;

    /**
     * @brief shouldSkipPvalueStorage
     * @return True if pvalue storage should be skipped
     */
    bool shouldSkipPvalueStorage() const;
    bool hasShouldSkipPvalueStorage() const;

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
    static const std::string JSON_RS_MYSQL_DB_PORT;
    static const std::string JSON_RS_MYSQL_DB_NAME;
    static const std::string JSON_RS_MYSQL_DB_CRED_FILE;
    static const std::string JSON_RS_MYSQL_DB_CRED_FILE_ROOT;
    static const std::string JSON_RS_MYSQL_DB_CRED_FILE_NAME;
    static const std::string JSON_RS_MYSQL_DB_CRED_FILE_PWD;
    static const std::string JSON_RS_SKIP_PVALUE_STORAGE;
    static const std::string JSON_BINARIES;
    static const std::string JSON_BINARIES_NIST;
    static const std::string JSON_BINARIES_DH;
    static const std::string JSON_BINARIES_TU01;
    static const std::string JSON_MISC;
    static const std::string JSON_MISC_NIST;
    static const std::string JSON_MISC_NIST_MAIN_RES_DIR;
    static const std::string JSON_EXEC;
    static const std::string JSON_EXEC_MAX_PAR_TESTS;
    static const std::string JSON_EXEC_TEST_TIMEOUT;

    /* Variable types for getters. Should a new variable be added,
     * add it here too. */
    enum class VariableType {
        loggerDir,
        rsFileDir,
        binary
    };

    /* Member variables */
    static const std::string objectInfo;

    std::string cfgFileName;

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
    std::string rsMysqlPort;
    std::string rsMysqlDbName;
    std::string rsMysqlCredentialsFile;

    std::string binaryDieharder;
    std::string binaryNiststs;
    std::string binaryTestU01;

    std::string miscNiststsMainResDir;

    int execMaximumThreads;
    int execTestTimeout;
    int skipPvalueStorage;

    /* Private methods */
    ToolkitSettings() {}

    std::string getBatteryVariable(VariableType variableType ,
                                   const BatteryArg & battery) const;

    std::string parseDirectoryPath(const json & parentNode,
                                   const std::string & childTagName,
                                   bool mandatory = true) const;

    std::string parseStringValue(const json & parentNode,
                                 const std::string & childTagName,
                                 bool mandatory = true) const;

    int parseIntegerValue(const json & parentNode,
                          const std::string & childTagName,
                          bool mandatory = true,
                          int defaultValue = 0) const;

    std::string getTagFromCredentials(const std::string & tagPath) const;

    std::string returnIfNonEmpty(const std::string & value,
                                 const std::string & originTag,
                                 const std::string & originFile = "") const;

    std::string getParsingErrorMessage(const std::string & mess,
                                       const std::string & tagPath = "",
                                       const std::string & fileName = "") const;
};

} // namespace rtt

#endif // RTT_TOOLKITSETTINGS_H

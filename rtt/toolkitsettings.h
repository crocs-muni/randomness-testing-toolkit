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
    std::string rsMysqlUserName;
    std::string rsMysqlPwd;
    std::string rsMysqlDbName;

    std::string binaryDieharder;
    std::string binaryNiststs;
    std::string binaryTestU01;

    std::string miscNiststsMainResDir;

    int execMaximumThreads = 1;

    /* Private methods */
    ToolkitSettings() {}

    std::string getBatteryVariable(VariableType variableType ,
                                   Constants::Battery battery) const;

    static std::string parseDirectoryPath(const json::object_t & parentNode,
                                          const std::string & childTagName,
                                          bool mandatory = true);

    static std::string parseStringValue(const json::object_t & parentNode,
                                        const std::string & childTagName,
                                 bool mandatory = true);

    static int parseIntegerValue(const json::object_t & parentNode,
                                 const std::string & childTagName,
                                 bool mandatory = true);
};

} // namespace rtt

#endif // RTT_TOOLKITSETTINGS_H

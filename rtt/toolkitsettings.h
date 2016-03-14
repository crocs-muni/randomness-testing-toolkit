#ifndef RTT_TOOLKITSETTINGS_H
#define RTT_TOOLKITSETTINGS_H

#include "rtt/constants.h"
#include "bugexception.h"
#include "rtt/rttexception.h"
#include "libs/tinyXML/xmlproc.h"

namespace rtt {

class ToolkitSettings {
public:
    static ToolkitSettings getInstance(
            const std::string & configFileName = Constants::FILE_TOOLKIT_SETTINGS);

    /* Getters for variables */

    std::string getLoggerRunLogDir() const;

    std::string getRsFileOutFile() const;

    std::string getLoggerBatteryDir(Constants::Battery battery) const;

    std::string getRsFileBatteryDir(Constants::Battery battery) const;

    std::string getBinaryBattery(Constants::Battery battery) const;

private:
    /* Variable types for getters. Should new variable be added, add it here too. */
    enum class VariableType {
        loggerDir,
        rsFileDir,
        binary
    };

    /* XPaths inside config file */
    /* Logger paths */
    static const std::string XPATH_LOGGER_DIR_PREFIX;
    static const std::string XPATH_LOGGER_RUN_LOG_DIR;
    static const std::string XPATH_LOGGER_DIEHARDER_DIR;
    static const std::string XPATH_LOGGER_NISTSTS_DIR;
    static const std::string XPATH_LOGGER_TU01_SCRUSH_DIR;
    static const std::string XPATH_LOGGER_TU01_CRUSH_DIR;
    static const std::string XPATH_LOGGER_TU01_BCRUSH_DIR;
    static const std::string XPATH_LOGGER_TU01_RABBIT_DIR;
    static const std::string XPATH_LOGGER_TU01_ALPHABIT_DIR;
    /* Result storage paths */
    /* File result storage */
    static const std::string XPATH_RS_FILE_OUTPUT_FILE;
    static const std::string XPATH_RS_FILE_DIR_PREFIX;
    static const std::string XPATH_RS_FILE_DIEHARDER_DIR;
    static const std::string XPATH_RS_FILE_NISTSTS_DIR;
    static const std::string XPATH_RS_FILE_TU01_SCRUSH_DIR;
    static const std::string XPATH_RS_FILE_TU01_CRUSH_DIR;
    static const std::string XPATH_RS_FILE_TU01_BCRUSH_DIR;
    static const std::string XPATH_RS_FILE_TU01_RABBIT_DIR;
    static const std::string XPATH_RS_FILE_TU01_ALPHABIT_DIR;
    /* Database result storage */
    // Nothing yet
    /* Executable binaries paths */
    static const std::string XPATH_BINARIES_DIEHARDER;
    static const std::string XPATH_BINARIES_NISTSTS;
    static const std::string XPATH_BINARIES_TESTU01;

    std::string objectInfo = "Toolkit Settings";

    std::string loggerRunLogDir;
    std::string loggerDieharderDir;
    std::string loggerNiststsDir;
    std::string loggerSCrushDir;
    std::string loggerCrushDir;
    std::string loggerBCrushDir;
    std::string loggerRabbitDir;
    std::string loggerAlphabitDir;

    std::string rsFileOutFile;
    std::string rsFileDieharderDir;
    std::string rsFileNiststsDir;
    std::string rsFileSCrushDir;
    std::string rsFileCrushDir;
    std::string rsFileBCrushDir;
    std::string rsFileRabbitDir;
    std::string rsFileAlphabitDir;

    std::string binaryDieharder;
    std::string binaryNiststs;
    std::string binaryTestU01;

    ToolkitSettings() {}

    std::string getBatteryVariable(VariableType variableType ,
                                   Constants::Battery battery) const;

    std::string getDirValue(TiXmlNode * xmlConfig ,
                            const std::string & xpath ,
                            bool mandatory = true);

    std::string getStringValue(TiXmlNode * xmlConfig ,
                               const std::string & xpath ,
                               bool mandatory = true);

    /**
     * @brief getIntegerValue Takes value in xmlConfig on xpath path and
     * converts it into integer. If mandatory is set to false and tag is
     * empty or nonexistent returns 0. In any case, if the value cannot
     * be converted throw exception.
     * @param xmlConfig Config root
     * @param xpath Path to tag
     * @param mandatory If tag does not exist or is empty throws exception if
     * this is set to true.
     * @return integer value
     */
    int getIntegerValue(TiXmlNode * xmlConfig ,
                        const std::string & xpath ,
                        bool mandatory = true);
};

} // namespace rtt

#endif // RTT_TOOLKITSETTINGS_H

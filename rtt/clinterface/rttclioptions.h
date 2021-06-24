#ifndef RTT_CLINTERFACE_RTTCLIOPTIONS_H
#define RTT_CLINTERFACE_RTTCLIOPTIONS_H

#include <vector>
#include <string>
#include <functional>

#include "rtt/version.h"
#include "libs/variant/include/mpark/variant.hpp"
#include "rtt/strings.h"
#include "rtt/rttexception.h"
#include "rtt/clinterface/clargument.h"
#include "rtt/clinterface/batteryarg.h"
#include "rtt/clinterface/resultstoragearg.h"

namespace rtt {
namespace clinterface {

typedef mpark::variant<
            ClArgument<BatteryArg>,
            ClArgument<ResultStorageArg>,
            ClArgument<int>,
            ClArgument<std::string>,
            ClArgument<std::uint64_t>>
        tArgumentTypes;

/**
 * @brief The RTTCliOptions class Handles command line interface and
 * options for RTT. The options are defined and parsed here.
 */
class RTTCliOptions {
public:
    /**
     * @brief getInstance Creates the object or throws and exception if the
     * options are invalid.
     * @param argc
     * @param argv
     * @return Initialized object with parsed options.
     */
    static RTTCliOptions getInstance(int argc, char * argv[]);

    /**
     * @brief getUsage
     * @return Usage of the RTT application
     */
    static std::string getUsage();

    /**
     * @brief getInputCfgPath
     * @return Path to config with battery configuration.
     */
    std::string getInputCfgPath() const;

    /**
     * @brief getInputDataPath
     * @return Path to file with binary data to analyse.
     */
    std::string getInputDataPath() const;

    /**
     * @brief getTestConsts
     * @return IDs of tests that was set through the command line.
     */
    std::vector<int> getTestConsts() const;

    /**
     * @brief getBatteryId
     * @return ID of the chosen battery.
     */
    Constants::BatteryID getBatteryId() const;

    /**
     * @brief getBatteryArg
     * @return Whole object of the chosen battery.
     */
    BatteryArg getBatteryArg() const;

    /**
     * @brief getResultStorageId
     * @return ID of the chosen storage.
     */
    Constants::ResultStorageID getResultStorageId() const;

    /**
     * @brief getResultStorageArg
     * @return Whole object of the chosen storage.
     */
    ResultStorageArg getResultStorageArg() const;

    /**
     * @brief getMysqlDbEid
     * @return Experiment ID for the MySQL database.
     */
    std::uint64_t getMysqlDbEid() const;

    /**
     * @brief getJid
     * @return Job ID
     */
    bool hasJid() const;
    std::uint64_t getJid() const;

    /**
     * @brief getResultsPathPrefix
     * @return Path prefix to the experiment results directory
     */
    std::string getResultsPathPrefix() const;
    bool hasResultsPathPrefix() const;

    /**
     * @brief getSettingsFilePath
     * @return RTT settings json file path
     */
    std::string getSettingsFilePath() const;
    bool hasSettingsFilePath() const;

    /**
     * @brief getMysqlDbHost
     * @return MySQL host name, overrides config file
     */
    std::string getMysqlDbHost() const;
    bool hasMysqlDbHost() const;

    /**
     * @brief getMysqlDbPort
     * @return MySQL port, overrides config file
     */
    std::uint64_t getMysqlDbPort() const;
    bool hasMysqlDbPort() const;

    /**
     * @brief getSkipPvalues
     * @return skip p-value storage procedure
     */
    bool getSkipPvalues() const;
    bool hasSkipPvalues() const;

private:
    static const std::string BATTERY_ARG_NAME;
    static const std::string SETTINGS_FILE_ARG_NAME;
    static const std::string DATA_FILE_ARG_NAME;
    static const std::string CONF_FILE_ARG_NAME;
    static const std::string TEST_ID_ARG_NAME;
    static const std::string JID_ARG_NAME;
    static const std::string RESULT_STORAGE_ARG_NAME;
    static const std::string RESULT_PATH_PREFIX_ARG_NAME;
    static const std::string MYSQL_DB_EID_ARG_NAME;
    static const std::string MYSQL_DB_HOST_ARG_NAME;
    static const std::string MYSQL_DB_PORT_ARG_NAME;
    static const std::string SKIP_PVALUES;
    std::vector<tArgumentTypes> arguments = {
        ClArgument<BatteryArg>(BATTERY_ARG_NAME),                    /* Battery */
        ClArgument<std::string>(DATA_FILE_ARG_NAME),                 /* Input data file */
        ClArgument<std::string>(CONF_FILE_ARG_NAME),                 /* Input config file */
        ClArgument<int>(TEST_ID_ARG_NAME, true),                     /* (opt) Test to run in battery */
        ClArgument<std::uint64_t>(JID_ARG_NAME, true),               /* (opt) Job ID */
        ClArgument<ResultStorageArg>(RESULT_STORAGE_ARG_NAME, true), /* (opt) Result storage */
        ClArgument<std::string>(RESULT_PATH_PREFIX_ARG_NAME, true), /* (opt) Result path prefix */
        ClArgument<std::string>(SETTINGS_FILE_ARG_NAME, true),       /* (opt) JSON settings file  */
        ClArgument<std::uint64_t>(MYSQL_DB_EID_ARG_NAME, true),      /* (opt) Experiment ID  */
        ClArgument<std::string>(MYSQL_DB_HOST_ARG_NAME, true),       /* (opt) MySQL Host name  */
        ClArgument<std::uint64_t>(MYSQL_DB_PORT_ARG_NAME, true),      /* (opt) MySQL port  */
        ClArgument<int>(SKIP_PVALUES, true)                         /* skip pvalue storage  */
    };

    std::string objectInfo = "CL Arguments Parser";

    RTTCliOptions() {}

    /**
     * @brief isArgumentSet
     * @param argName
     * @return true if the argument argName was set, false otherwise.
     */
    bool isArgumentSet(const std::string & argName) const;

    /**
     * @brief setArgumentValue Will set value to the argument argName
     * @param argName
     * @param value
     */
    void setArgumentValue(const std::string & argName, const  std::string & value);

    /**
     * @brief getArgumentValue
     * @param argName
     * @return Value of the requested argument.
     */
    template<typename T>
    T getArgumentValue(const std::string & argName) const {
        auto cmpArgumentName = [&](const auto & arg) {
            return argName == arg.getArgumentName();
        };
        for(const auto & arg : arguments) {
            if(mpark::visit(cmpArgumentName, arg)) {
                try {
                    return mpark::get<ClArgument<T>>(arg).getArgumentValue();
                } catch (mpark::bad_variant_access & e) {
                    raiseBugException(e.what());
                }
            }
        }
        raiseBugException("no argument with such name: " + argName);
    }
};

} // namespace clinterface
} // namespace rtt

#endif // RTT_CLINTERFACE_RTTCLIOPTIONS_H

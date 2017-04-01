#ifndef RTT_LOGGER_H
#define RTT_LOGGER_H

#include <string>

#ifndef ELPP_NO_DEFAULT_LOG_FILE
    #define ELPP_NO_DEFAULT_LOG_FILE
#endif
#ifndef ELPP_THREAD_SAFE
    #define ELPP_THREAD_SAFE
#endif
#ifndef ELPP_FORCE_USE_STD_THREAD
    #define ELPP_FORCE_USE_STD_THREAD
#endif

#include "libs/easylogging/easylogging++.h"

namespace rtt {

enum class LogLevel {
    INFO , WARN , ERROR
};

/**
 * @brief The Logger class This is just a simple wrapper
 * for Easylogging++. Will hold pointer to logger and make header on start.
 */
class Logger {
public:
    /**
     * @brief Logger Will create Logger instance and write log header.
     * @param logId Program wide unique id.
     * @param logFile Path to log file
     * @param toCout If true, log will be written also on standard output
     */
    Logger(const std::string & logId ,
           const std::string & logFile , bool toCout);

    /**
     * @brief ~Logger desctructor, will finalize log and write number of warnings and errors during the run.
     */
    ~Logger();

    /**
     * @brief log Will write logger message of desired level.
     * @param level Log level, can be INFO, WARN or ERROR
     * @param msg message
     */
    void log(LogLevel level , const std::string & msg);

    /**
     * @brief info Will write informational message to log.
     * @param msg
     */
    void info(const std::string & msg);

    /**
     * @brief warn Will write warning message to log and store msg in warningMessages
     * @param msg
     */
    void warn(const std::string & msg);

    /**
     * @brief error Will write error message to log and store msg in errorMessages
     * @param msg
     */
    void error(const std::string & msg);

    /**
     * @brief getWarningMessages
     * @return All warning messages that were logged using this object
     */
    std::vector<std::string> getWarningMessages();

    /**
     * @brief getErrorMessages
     * @return All error messages that were logged using this object
     */
    std::vector<std::string> getErrorMessages();

private:
    el::Logger * rawLogger = NULL;
    el::Configurations rawLoggerConf;

    /* Mutex for operations with warning messages */
    std::mutex warningMessages_mux;
    std::vector<std::string> warningMessages;

    /* Mutex for operations with error messages */
    std::mutex errorMessages_mux;
    std::vector<std::string> errorMessages;
};

} // namespace rtt

#endif // RTT_LOGGER_H

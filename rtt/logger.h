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

/* This is just a simple wrapper for Easylogging++.
 * Will hold pointer to logger and make header on start. */
class Logger {
public:
    /* Will create logger instance, write header to log. */
    Logger(const std::string & logId ,
           const std::string & logFile , bool toCout);

    /* Destructor, will write counts of errors and warnings */
    ~Logger();

    void log(LogLevel level , const std::string & msg);

    void info(const std::string & msg);

    void warn(const std::string & msg);

    void error(const std::string & msg);

    std::vector<std::string> getWarningMessages();

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

#include "logger.h"

#include "rtt/bugexception.h"
#include "rtt/utils.h"
#include "rtt/version.h"

namespace rtt {

Logger::Logger(const std::string &logId, const std::string &logFile, bool toCout) {
    /* Empty to make header, will be set later */
    rawLoggerConf.set(el::Level::Global, el::ConfigurationType::Format, "%msg");
    rawLoggerConf.set(el::Level::Global, el::ConfigurationType::Filename,
                      logFile);
    rawLoggerConf.set(el::Level::Global, el::ConfigurationType::Enabled,
                      "true");
    rawLoggerConf.set(el::Level::Global, el::ConfigurationType::ToFile,
                      "true");
    rawLoggerConf.set(el::Level::Global, el::ConfigurationType::MillisecondsWidth,
                      "1");
    rawLoggerConf.set(el::Level::Global, el::ConfigurationType::PerformanceTracking,
                      "false");
    rawLoggerConf.set(el::Level::Global, el::ConfigurationType::MaxLogFileSize,
                      "10485760"); /* 10MB */
    rawLoggerConf.set(el::Level::Global, el::ConfigurationType::LogFlushThreshold,
                      "100");
    if(toCout)
        rawLoggerConf.set(el::Level::Global, el::ConfigurationType::ToStandardOutput,
                          "true");
    else
        rawLoggerConf.set(el::Level::Global, el::ConfigurationType::ToStandardOutput,
                          "false");

    rawLogger = el::Loggers::getLogger(logId);

    el::Loggers::reconfigureLogger(rawLogger , rawLoggerConf);

    /* Writing log header */
    rawLogger->info("\nRandomness Testing Toolkit logger start.");
    rawLogger->info("Application build  "+ (std::string)GIT_COMMIT_SHORT);
    rawLogger->info("Logger name        " + logId);
    rawLogger->info("Logging start      " +
                 Utils::formatRawTime(Utils::getRawTime() , "%d-%m-%Y %H:%M:%S"));
    rawLogger->info("\n");

    /* Set format for normal logging */
    rawLoggerConf.set(el::Level::Global, el::ConfigurationType::Format,
                  "[%datetime{%H:%m:%s}] Thread %thread: %level - %msg");

    el::Loggers::reconfigureLogger(rawLogger , rawLoggerConf);
}

Logger::~Logger() {
    /* Setting clear format for ending info. */
    rawLoggerConf.set(el::Level::Global, el::ConfigurationType::Format, "%msg");
    el::Loggers::reconfigureLogger(rawLogger , rawLoggerConf);

    /* Writing ending info */
    rawLogger->info("\n\nLogging end        " +
                    Utils::formatRawTime(Utils::getRawTime() , "%d-%m-%Y %H:%M:%S"));
    rawLogger->info("Error count        " + Utils::itostr(errorCount));
    rawLogger->info("Warning count      " + Utils::itostr(warningCount));
    rawLogger->info("");
}

void Logger::log(LogLevel level, const std::string & msg) {
    switch(level) {
    case LogLevel::INFO:
        rawLogger->info(msg);
        break;
    case LogLevel::WARN:
        rawLogger->warn(msg);
        ++warningCount;
        break;
    case LogLevel::ERROR:
        rawLogger->error(msg);
        ++errorCount;
        break;
    default:
        raiseBugException("unknown log level");
    }
}

void Logger::info(const std::string & msg) {
    rawLogger->info(msg);
}

void Logger::warn(const std::string & msg) {
    rawLogger->warn(msg);
    ++warningCount;
}

void Logger::error(const std::string & msg) {
    rawLogger->error(msg);
    ++errorCount;
}

} // namespace rtt

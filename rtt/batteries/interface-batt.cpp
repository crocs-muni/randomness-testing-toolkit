#include "interface-batt.h"

namespace rtt {
namespace batteries {

std::string Interface::createLogFilePath(const time_t & battCreationTime,
                                         const std::string & logDirectory,
                                         const std::string & binFilePath) {
    std::string logFilePath = logDirectory;
    if(!logFilePath.empty() && logFilePath.back() != '/')
        logFilePath.append("/");
    logFilePath.append(Utils::formatRawTime(battCreationTime , "%Y%m%d%H%M%S"));
    logFilePath.append("-" + Utils::getLastItemInPath(binFilePath) + ".log");
    return logFilePath;
}

}
} // namespace rtt

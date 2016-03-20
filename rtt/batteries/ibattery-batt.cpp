#include "ibattery-batt.h"

#include "rtt/batteries/dieharder/battery-dh.h"
#include "rtt/batteries/niststs/battery-sts.h"
#include "rtt/batteries/testu01/battery-tu01.h"

namespace rtt {
namespace batteries {

std::unique_ptr<IBattery> IBattery::getInstance(const Globals & globals) {
    switch(globals.getCliOptions()->getBattery()) {
    case Constants::Battery::DIEHARDER:
        return dieharder::Battery::getInstance(globals);
    case Constants::Battery::NIST_STS:
        return niststs::Battery::getInstance(globals);
    case Constants::Battery::TU01_SMALLCRUSH:
        //return testu01::Battery::getInstance(globals);
    case Constants::Battery::TU01_CRUSH:
        //return testu01::Battery::getInstance(globals);
    case Constants::Battery::TU01_BIGCRUSH:
        //return testu01::Battery::getInstance(globals);
    case Constants::Battery::TU01_RABBIT:
        //return testu01::Battery::getInstance(globals);
    case Constants::Battery::TU01_ALPHABIT:
        return testu01::Battery::getInstance(globals);
    default:raiseBugException("invalid battery");
    }
}

std::string IBattery::createLogFilePath(const time_t & battCreationTime,
                                         const std::string & logDirectory,
                                         const std::string & binFilePath) {
    std::string logFilePath = logDirectory;
    if(!logFilePath.empty() && logFilePath.back() != '/')
        logFilePath.append("/");
    logFilePath.append(Utils::formatRawTime(battCreationTime , "%Y%m%d%H%M%S"));
    logFilePath.append("-" + Utils::getLastItemInPath(binFilePath) + ".log");
    return logFilePath;
}

std::vector<int> IBattery::parseIntValues(const std::string & str) {
    std::vector<std::string> values = Utils::split(str , ' ');
    std::vector<std::string> range;
    std::vector<int> rval;
    int botRange = 0;
    int topRange = 0;

    for(const std::string & value : values) {
        if(value.find('-') == std::string::npos) {
            /* Only integer is in value */
            rval.push_back(Utils::strtoi(value));
        } else {
            /* Range of integers */
            range = Utils::split(value , '-');
            if(range.size() != 2) /* more than one dash in string, why would you do that??? */
                throw std::runtime_error("invalid range denoted in string " + value);
            botRange = Utils::strtoi(range.front());
            topRange = Utils::strtoi(range.back());
            for( ; botRange <= topRange ; ++botRange)
                rval.push_back(botRange);
        }
    }
    Utils::sort(rval);
    return rval;
}

} // namespace batteries
} // namespace rtt

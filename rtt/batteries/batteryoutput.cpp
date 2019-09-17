#include "batteryoutput.h"

namespace rtt {
namespace batteries {

static const std::regex RE_ERR ("\\s*(.*?error.*?)\\n", std::regex::icase);
static const std::regex RE_WARN ("\\s*(.*?warning.*?)\\n", std::regex::icase);

void BatteryOutput::appendStdOut(const std::string & stdOut) {
    detectionDone = false;

    this->stdOut.append(stdOut);
}

void BatteryOutput::appendStdErr(const std::string & stdErr) {
    this->stdErr.append(stdErr);
}

std::string BatteryOutput::getStdOut() const {
    return stdOut;
}

std::string BatteryOutput::getStdErr() const {
    return stdErr;
}

std::vector<std::string> BatteryOutput::getErrors() const {
    return errors;
}

std::vector<std::string> BatteryOutput::getWarnings() const {
    return warnings;
}

void BatteryOutput::doDetection() {
    detectErrsWarnsInStdOut();
}

void BatteryOutput::detectErrsWarnsInStdOut() {
    if(detectionDone)
        return;

    /* Detect warnings and errors here.
     * Detection happens only in stdOut variable. */


    std::smatch match;
    auto end =       std::sregex_iterator();
    auto errBegin =  std::sregex_iterator(stdOut.begin() , stdOut.end(), RE_ERR);
    auto warnBegin = std::sregex_iterator(stdOut.begin() , stdOut.end(), RE_WARN);

    errors.clear();
    warnings.clear();

    for( ; errBegin != end ; ++errBegin) {
        match = *errBegin;
        errors.push_back(match[1].str());
    }

    for( ; warnBegin != end ; ++ warnBegin) {
        match = *warnBegin;
        warnings.push_back(match[1].str());
    }

    detectionDone = true;
}

} // namespace batteries
} // namespace rtt


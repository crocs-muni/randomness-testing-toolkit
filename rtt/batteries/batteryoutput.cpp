#include "batteryoutput.h"

namespace rtt {
namespace batteries {

static const boost::regex RE_ERR  ("\\n\\s*([^\\n]*error[^\\n]*)\\n", boost::regex::icase);
static const boost::regex RE_WARN ("\\n\\s*([^\\n]*warning[^\\n]*)\\n", boost::regex::icase);

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


    boost::smatch match;
    auto end =       boost::sregex_iterator();
    auto errBegin =  boost::sregex_iterator(stdOut.begin() , stdOut.end(), RE_ERR);
    auto warnBegin = boost::sregex_iterator(stdOut.begin() , stdOut.end(), RE_WARN);

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


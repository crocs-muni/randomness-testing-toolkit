#ifndef RTT_BATTERIES_BATTERYOUTPUT_H
#define RTT_BATTERIES_BATTERYOUTPUT_H

#include <string>
#include <vector>
#include <regex>

namespace rtt {
namespace batteries {

/* Class for storing output from executed battery.
 * After calling get functions on errors and warnings, string stdOut is checked for
 * lines containing "error" or "warning" (case insensitive) and if any lines are found,
 * they are also stored in variables errors and warnings respectively. */
class BatteryOutput {
public:
    BatteryOutput() {}

    void appendStdOut(const std::string & stdOut);

    void appendStdErr(const std::string & stdErr);

    std::string getStdErr() const;

    std::string getStdOut() const;

    std::vector<std::string> getErrors();

    std::vector<std::string> getWarnings();


private:
    bool errsWarnsDetected = false;
    std::string stdOut;
    std::string stdErr;
    std::vector<std::string> errors;
    std::vector<std::string> warnings;

    void detectErrsWarnsInStdOut();
};

} // namespace batteries
} // namespace rtt

#endif // RTT_BATTERIES_BATTERYOUTPUT_H

#ifndef RTT_BATTERIES_BATTERYOUTPUT_H
#define RTT_BATTERIES_BATTERYOUTPUT_H

#include <string>
#include <vector>
#include <regex>

namespace rtt {
namespace batteries {

/**
 * @brief The BatteryOutput class Class for storing output from executed battery.
 * After calling get functions on errors and warnings, string stdOut is checked for
 * lines containing "error" or "warning" (case insensitive) and if any lines are found,
 * they are also stored in variables errors and warnings respectively.
 */
class BatteryOutput {
public:
    BatteryOutput() {}

    /**
     * @brief appendStdOut Add string to standard output
     * @param stdOut
     */
    void appendStdOut(const std::string & stdOut);

    /**
     * @brief appendStdErr Add string to error output
     * @param stdErr
     */
    void appendStdErr(const std::string & stdErr);

    /**
     * @brief getStdErr
     * @return Raw error output
     */
    std::string getStdErr() const;

    /**
     * @brief getStdOut
     * @return Raw standard output
     */
    std::string getStdOut() const;

    /**
     * @brief getErrors
     * @return Extracted error messages
     */
    std::vector<std::string> getErrors() const;

    /**
     * @brief getWarnings
     * @return Extracted warning messages
     */
    std::vector<std::string> getWarnings() const;

    /**
     * @brief doDetection This will force detection. Detection is time heavy
     * operation and should be done inside test threads
     * instead of running it via getter later.
     */
    void doDetection();

private:
    bool detectionDone = false;
    std::string stdOut;
    std::string stdErr;
    std::vector<std::string> errors;
    std::vector<std::string> warnings;

    void detectErrsWarnsInStdOut();
};

} // namespace batteries
} // namespace rtt

#endif // RTT_BATTERIES_BATTERYOUTPUT_H

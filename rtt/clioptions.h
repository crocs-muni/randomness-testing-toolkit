#ifndef RTT_CLIOPTIONS_H
#define RTT_CLIOPTIONS_H

#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <stdexcept>

#include "rtt/constants.h"
#include "rtt/rttexception.h"
#include "rtt/utils.h"

namespace rtt {

/**
 * @brief The CliOptions class Intented for parsing and holding cli arguments of the binary.
 */
class CliOptions {
public:
    /**
     * @brief getInstance Will create initialized CliOptions instance.
     * @param argc Count of arguments received on the command line.
     * @param argv Values of arguments received on the command line
     * @return Initialized object.
     */
    static CliOptions getInstance(int argc , char * argv[]);

    /**
     * @brief getUsage
     * @return String with program help message.
     */
    static std::string getUsage();

    /**
     * @brief getBatteryId
     * @return ID of the battery that will be used during the program run.
     */
    Constants::Battery getBatteryId() const;

    /**
     * @brief getTestConsts
     * @return IDs of tests that will be executed during the program run.
     */
    std::vector<int> getTestConsts() const;

    /**
     * @brief getInputCfgPath
     * @return Path (relative or absolute) to input configuration file.
     */
    std::string getInputCfgPath() const;

    /**
     * @brief getInputDataPath
     * @return Path (relative or absolute) to input data that will be analyzed by the battery.
     */
    std::string getInputDataPath() const;

    /**
     * @brief getMysqlEid Used by MySQL storage. ID of the experiment that was previously
     * created in the table and to which will be added results of this run.
     * @return ID of the experiment.
     */
    std::uint64_t getMysqlEid() const;

private:
    Constants::Battery battery;
    std::vector<int> testConsts;
    std::string objectInfo = "CLI options";
    std::string inputCfgPath;
    std::string inputDataPath;
    std::uint64_t mysqlEid = 0;

    /* Constructor is private => no unitialized instances around */
    CliOptions() {}
};

} // namespace rtt

#endif // RTT_CLIOPTIONS_H


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

class CliOptions {
public:
    static CliOptions getInstance(int argc , char * argv[]);
    static std::string getUsage();

    Constants::Battery getBattery() const;
    std::vector<int> getTestConsts() const;
    std::string getInputCfgPath() const;
    std::string getBinFilePath() const;
    std::string getOutFilePath() const;

private:
    Constants::Battery battery;
    std::vector<int> testConsts;
    std::string objectInfo = "CLI options";
    std::string inputCfgPath;
    std::string binFilePath;
    std::string outFilePath;

    /* Constructor is private => no unitialized instances around */
    CliOptions() {}
};

} // namespace rtt

#endif // RTT_CLIOPTIONS_H


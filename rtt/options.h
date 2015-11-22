#ifndef RTT_OPTIONS_H
#define RTT_OPTIONS_H

#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <stdexcept>

#include "rtt/constants.h"
#include "rtt/utils.h"

namespace rtt {

class CliOptions {
private:
    int battery;
    std::vector<int> testConsts;
    std::string inputCfgPath;
    std::string binFilePath;
    std::string outFilePath;
public:
    CliOptions() : battery(0) {}
    void init(int argc , char * argv[]);
    int getBattery() const;
    std::vector<int> getTestConsts() const;
    std::string getInputCfgPath() const;
    std::string getBinFilePath() const;
    std::string getOutFilePath() const;
    std::string getUsage() const;
};

} // namespace rtt

#endif // RTT_OPTIONS_H


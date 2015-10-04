#ifndef TOOLKITOPTIONS_H
#define TOOLKITOPTIONS_H

#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <stdexcept>

#include "ToolkitConstants.h"
#include "Utils.h"

class ToolkitOptions {
private:
    int battery;
    std::vector<int> testConsts;
    std::string inputCfgPath;
    std::string binFilePath;
    std::string outFilePath;
public:
    ToolkitOptions() : battery(0) {}
    void init(int argc , char * argv[]);
    int getBattery() const;
    std::vector<int> getTestConsts() const;
    std::string getInputCfgPath() const;
    std::string getBinFilePath() const;
    std::string getOutFilePath() const;
    std::string getUsage() const;
private:
    int strtoi(char * str) const;
};

#endif // TOOLKITOPTIONS_H


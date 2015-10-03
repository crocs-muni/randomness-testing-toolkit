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
public:
    ToolkitOptions() : battery(0) {}
    void init(int argc , char * argv[]);
    int getBattery();
    std::vector<int> getTestConsts();
    std::string getInputCfgPath();
    std::string getUsage();
private:
    int strtoi(char * str);
};

#endif // TOOLKITOPTIONS_H


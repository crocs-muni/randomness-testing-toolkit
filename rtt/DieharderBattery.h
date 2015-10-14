#ifndef DIEHARDERBATTERY_H
#define DIEHARDERBATTERY_H

#include <unistd.h>
#include <spawn.h>
#include <sys/wait.h>

extern char **environ;

#include "StatBatteryInterface.h"
#include "XMLproc.h"

class DieharderBattery : public StatBatteryInterface {
private:
    std::vector<int> tests;
    std::string binFilePath;
    std::string dieharderBinPath;
    std::string outFilePath;
    std::string additionalArguments;
public:
    DieharderBattery() {}
    void initBattery(const ToolkitOptions & options);
    void runTests();
private:
    char ** buildArgs(int testNum , int * argc);
    void destroyArgs(char ** argv , int argc);
};

#endif //DIEHARDERBATTERY_H

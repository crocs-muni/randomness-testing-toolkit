#ifndef NISTSTSBATTERY_H
#define NISTSTSBATTERY_H

#include <poll.h>
#include <unistd.h>
#include <spawn.h>
#include <sys/wait.h>

extern char **environ;

#include "StatBatteryInterface.h"
#include "XMLproc.h"

class NistStsBattery : public StatBatteryInterface {
private:
    std::string testsVector;
    std::string binFilePath;
    std::string nistStsBinPath;
    std::string outFilePath;
    std::vector<std::pair<int , int>> adjustedParameters;
    std::string nistOutput;
    int streamSize;
    int streamCount;
public:
    NistStsBattery() {}
    void initBattery(const ToolkitOptions & options);
    void runTests();
    void processStoredResults();
private:
    std::string createTestsVector(const std::vector<int> & tests);
    void loadAdjustedParameters(TiXmlNode * root);
    void adjParValidator(int testNum);
    void validateTestConsts(const std::vector<int> & tests);
    posix_spawn_file_actions_t createFileActions(
            int * stdin_pipe , int * stdout_pipe , int * stderr_pipe);
    void readPipes(int * stdout_pipe , int * stderr_pipe);
    char ** buildArgs(int * argc);
    void destroyArgs(int argc , char ** argv);
    std::string createInputSequence();
};

#endif //NISTSTSBATTERY_H

#ifndef RTT_BATTERIES_IVARIANT_H
#define RTT_BATTERIES_IVARIANT_H

#include "rtt/globalcontainer.h"
#include "rtt/batteries/testconstants.h"
#include "rtt/batteries/batteryoutput.h"

namespace rtt {
namespace batteries {

class IVariant {
public:
    static std::unique_ptr<IVariant> getInstance(int testId, uint variantIdx,
                                                 const GlobalContainer & cont);

    virtual ~IVariant() {}

    void execute();

    std::string getCliArguments() const;

    std::string getStdInput() const;

    std::vector<std::string> getUserSettings() const;

    BatteryOutput getBatteryOutput() const;

protected:
    /* Set in constructor */
    Logger * logger;
    std::string objectInfo;
    int testId;
    uint variantIdx;
    Constants::Battery battId;
    std::string binaryDataPath;
    std::string logFilePath;
    std::string executablePath;
    std::vector<std::string> userSettings;
    std::string cliArguments;
    std::string stdInput;

    /* Set after execution */
    BatteryOutput batteryOutput;
    bool executed = false;

    IVariant(int testId, uint variantIdx, const GlobalContainer & cont);

    virtual void buildStrings() = 0;
};

} // namespace batteries
} // namespace rtt

#endif // RTT_BATTERIES_IVARIANT_H

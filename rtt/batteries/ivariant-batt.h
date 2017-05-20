#ifndef RTT_BATTERIES_IVARIANT_H
#define RTT_BATTERIES_IVARIANT_H

#include "rtt/globalcontainer.h"
#include "rtt/clinterface/batteryarg.h"
#include "rtt/batteries/testconstants.h"
#include "rtt/batteries/batteryoutput.h"

namespace rtt {
namespace batteries {

/**
 * @brief The IVariant class Holds info about single variant of given test. Can and will be executed.
 */
class IVariant {
public:
    /**
     * @brief getInstance Initializes an object
     * @param testId Id of the test
     * @param testObjInf Info about parent object, used for logging
     * @param variantIdx Index of the new variant
     * @param cont Global settings
     * @return Obejct
     */
    static std::unique_ptr<IVariant> getInstance(int testId, std::string testObjInf,
                                                 uint variantIdx, const GlobalContainer & cont);

    /**
     * @brief ~IVariant Desctructor.
     */
    virtual ~IVariant() {}

    /**
     * @brief execute Executes the variant, should be called only
     * from threadManager function, otherwise non-defined behaviour
     */
    virtual void execute();

    /**
     * @brief getCliArguments
     * @return CLI arguments of the variant that will be sent to the binary
     */
    std::string getCliArguments() const;

    /**
     * @brief getStdInput
     * @return Standard input that will be sent to the binary
     */
    std::string getStdInput() const;

    /**
     * @brief getBatteryOutput
     * @return Output of the execution
     */
    BatteryOutput getBatteryOutput() const;

    /**
     * @brief getTestId
     * @return Test ID
     */
    int getTestId() const;

    /**
     * @brief getObjectInfo
     * @return Info about the object, will be used in logging
     */
    std::string getObjectInfo() const;

    /**
     * @brief getUserSettings
     * @return Settings set by user in battery configuration
     */
    std::vector<std::pair<std::string, std::string> > getUserSettings() const;

protected:
    /* Set in constructor */
    Logger * logger;
    std::string objectInfo;
    int testId;
    uint variantIdx;
    clinterface::BatteryArg battery;
    std::string binaryDataPath;
    std::string logFilePath;
    std::string executablePath;
    std::string cliArguments;
    std::string stdInput;
    std::vector<std::pair<std::string, std::string>> userSettings;

    /* Set after execution */
    BatteryOutput batteryOutput;
    bool executed = false;

    IVariant(int testId, std::string testObjInf,
             uint variantIdx, const GlobalContainer & cont);

    virtual void buildStrings() = 0;

    void analyzeAndStoreBattOut();
};

} // namespace batteries
} // namespace rtt

#endif // RTT_BATTERIES_IVARIANT_H

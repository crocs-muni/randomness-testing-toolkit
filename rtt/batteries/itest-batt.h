#ifndef RTT_BATTERIES_ITEST_H
#define RTT_BATTERIES_ITEST_H

#include "rtt/batteries/ivariant-batt.h"
#include "rtt/clinterface/rttclioptions.h"

namespace rtt {
namespace batteries {

typedef std::vector<double> tTestPvals;

/**
 * @brief The ITest class Holds single test from given battery.
 * Can have one or multiple variants and those will be executed.
 */
class ITest {
public:
    /**
     * @brief getInstance Creates initialized object
     * @param battObjInf Information about parent object used for logging
     * @param testId ID of the test
     * @param cont Global settings
     * @return
     */
    static std::unique_ptr<ITest> getInstance(std::string battObjInf, int testId,
                                              const GlobalContainer & cont);

    /**
     * @brief ~ITest Desctructor
     */
    virtual ~ITest() {}

    /**
     * @brief wasExecuted
     * @return true if the test was executed, false otherwise
     */
    bool wasExecuted() const;

    /**
     * @brief getTestId
     * @return ID of the test
     */
    int getTestId() const;

    /**
     * @brief getLogicName
     * @return Human readable name of the test
     */
    std::string getLogicName() const;

    /**
     * @brief getVariants
     * @return All variants of the test
     */
    std::vector<IVariant *> getVariants() const;

    /**
     * @brief getBattId
     * @return ID of the parent battery
     */
    BatteryArg getBatteryArg() const;

    /**
     * @brief getLogger
     * @return pointer to logger
     */
    Logger * getLogger() const;

protected:
    ITest(std::string battObjInf, int testId , const GlobalContainer & cont);

    /* These fields will be set in the constructor */
    /* Pointers to global configurations */
    clinterface::RTTCliOptions * rttCliOptions;
    ToolkitSettings * toolkitSettings;
    Configuration * batteryConfiguration;
    Logger * logger;
    /* Variations of the test */
    std::vector<std::unique_ptr<IVariant>> variants;
    /* Test specific fields - will be set in constructor (base class) and
     * getInstance(derived classes) */
    int testId;
    clinterface::BatteryArg battery;
    std::string logicName;
    std::string objectInfo;
};

} // namespace batteries
} // namespace rtt

#endif // RTT_BATTERIES_ITEST_H

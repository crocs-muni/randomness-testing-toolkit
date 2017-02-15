#ifndef RTT_BATTERIES_ITEST_H
#define RTT_BATTERIES_ITEST_H

#include "rtt/batteries/ivariant-batt.h"

namespace rtt {
namespace batteries {

typedef std::vector<double> tTestPvals;

class ITest {
public:
    static std::unique_ptr<ITest> getInstance(int testId,
                                              const GlobalContainer & cont);

    virtual ~ITest() {}

    /* Getters for results and some variables */
    bool wasExecuted() const;

    int getTestId() const;

    std::string getLogicName() const;

    std::vector<IVariant *> getVariants() const;

    Constants::Battery getBattId() const;

    Logger * getLogger() const;

protected:
    ITest(int testId , const GlobalContainer & cont);

    /* These fields will be set in the constructor */
    /* Pointers to global configurations */
    CliOptions * cliOptions;
    ToolkitSettings * toolkitSettings;
    Configuration * batteryConfiguration;
    Logger * logger;
    /* Variations of the test */
    std::vector<std::unique_ptr<IVariant>> variants;
    /* Test specific fields - will be set in constructor (base class) and
     * getInstance(derived classes) */
    int testId;
    Constants::Battery battId;
    std::string logicName;
    std::string objectInfo;
};

} // namespace batteries
} // namespace rtt

#endif // RTT_BATTERIES_ITEST_H

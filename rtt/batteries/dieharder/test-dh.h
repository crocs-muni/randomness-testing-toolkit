#ifndef RTT_BATTERIES_DIEHARDER_TEST_H
#define RTT_BATTERIES_DIEHARDER_TEST_H

#include <string.h>
#include <vector>

#include "rtt/batteries/itest-batt.h"
#include "rtt/batteries/testrunner-batt.h"
#include "rtt/batteries/dieharder/setting-dh.h"
#include "rtt/batteries/testconstants.h"

namespace rtt {
namespace batteries {
namespace dieharder {

typedef std::pair<int , std::string> tTestInfo;

class Test : public ITest {
public:
    /* Test info constants */
    static const int OPTION_HEADER_FLAG;
    static const int OPTION_FILE_GENERATOR;

    /*
    ======================
    *** Public methods ***
    ======================
    */
    static std::unique_ptr<Test> getInstance(int testIndex ,
                                             const GlobalContainer & container);

    void execute();

    std::vector<std::string> getParameters() const;

    std::vector<std::string> getStatistics() const;

private:
    /*
    =================
    *** Variables ***
    =================
    */
    /* These fields will be set after initialization in */
    /* getInstance() */
    std::vector<Setting> settings;
    int pSampleCount;
    int subTestsCount;

    /*
    ===============
    *** Methods ***
    ===============
    */
    /* I don't want to allow existence of Test objects */
    /* without initialization that is in getInstance */
    Test(int testIndex , const GlobalContainer & container)
        : ITest(testIndex , container) {}

    std::string createArgs() const;

    void extractPvalues();
};

} // namespace dieharder
} // namespace batteries
} // namespace rtt

#endif // RTT_BATTERIES_DIEHARDER_TEST_H

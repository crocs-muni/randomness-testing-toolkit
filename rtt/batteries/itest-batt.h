#ifndef RTT_BATTERIES_ITEST_H
#define RTT_BATTERIES_ITEST_H

#include "libs/tinyXML/xmlproc.h"
#include "rtt/utils.h"

namespace rtt {
namespace batteries {

typedef std::vector<double> tTestPvals;

class ITest {
public:

    virtual ~ITest() {}

    virtual void execute() = 0;

    virtual bool wasExecuted() const = 0;

    virtual void appendTestLog(std::string & batteryLog) const = 0;

    virtual std::string getLogicName() const = 0;

    virtual std::vector<std::string> getParameters() const = 0;

    virtual std::vector<std::string> getStatistics() const = 0;

    virtual std::vector<tTestPvals> getResults() const = 0;

    virtual int getTestIndex() const = 0;

    /* Following methods are used more or less by all tests */
    /* So for the sake of code non-duplicity, I declare them here */

    static std::string getTestOrDefOpt(TiXmlNode * cfgRoot,
                                       TiXmlNode * testNode,
                                       const std::string & defaultPath,
                                       const std::string & testPath);
};

} // namespace batteries
} // namespace rtt

#endif // RTT_BATTERIES_ITEST_H

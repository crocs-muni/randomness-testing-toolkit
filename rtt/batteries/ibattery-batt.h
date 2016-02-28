#ifndef RTT_IBATTERY_H
#define RTT_IBATTERY_H

#include "libs/tinyXML/xmlproc.h"
#include "rtt/options.h"

namespace rtt {
namespace batteries {

class IBattery {
public:

    virtual ~IBattery() {}

    virtual void runTests() = 0;

    virtual void processStoredResults() = 0;

    /* Following methods are used more or less by all batteries */
    /* So for the sake of code non-duplicity, I declare them here */

    static std::string createLogFilePath(const time_t & battCreationTime ,
                                         const std::string & logDirectory ,
                                         const std::string & binFilePath);

    static std::vector<int> parseIntValues(const std::string & str);
};

} // namespace batteries
} // namespace rtt

#endif // RTT_IBATTERY_H

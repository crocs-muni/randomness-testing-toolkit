#ifndef RTT_BATTERIES_INTERFACE_H
#define RTT_BATTERIES_INTERFACE_H

#include "libs/tinyXML/xmlproc.h"
#include "rtt/options.h"

namespace rtt {
namespace batteries {

class Interface {
public:

    virtual ~Interface() {}

    virtual void runTests() = 0;

    virtual void processStoredResults() = 0;

    /* Following methods are used more or less by all batteries */
    /* So for the sake of code non-duplicity, I declare them here */

    static std::string createLogFilePath(const time_t & battCreationTime ,
                                         const std::string & logDirectory ,
                                         const std::string & binFilePath);
};

} // namespace batteries
} // namespace rtt

#endif // RTT_BATTERIES_INTERFACE_H

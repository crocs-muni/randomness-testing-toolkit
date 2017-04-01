#ifndef RTT_BUGEXCEPTION
#define RTT_BUGEXCEPTION

#include <exception>
#include <stdexcept>

#include "rtt/utils.h"

/* I don't like macros either... */
#define raiseBugException(message) \
    throw BugException(std::string(__FILE__) , rtt::Utils::itostr(__LINE__) , message)

namespace rtt {

/**
 * @brief The BugException class Thrown on assertions that should never
 * happen during normal run. Probably indicates bug caused by developer.
 * Should be called via macro raiseBugException that will add filename and line
 * into the message.
 */
class BugException : public std::logic_error {
public:
    BugException(const std::string & file ,
                 const std::string & line ,
                 const std::string & message)
        : std::logic_error(file + ":" + line + " - " + message)
    {}
};

} // namespace rtt

#endif // RTT_BUGEXCEPTION


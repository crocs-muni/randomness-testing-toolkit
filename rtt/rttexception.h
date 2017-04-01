#ifndef RTT_RTTEXCEPTION_H
#define RTT_RTTEXCEPTION_H

#include <exception>
#include <stdexcept>
#include <sstream>

#include "rtt/bugexception.h"

namespace rtt {

/**
 * @brief The RTTException class Used for indicating error during runtime
 */
class RTTException : public std::runtime_error {
public:
    RTTException(const std::string & objIdentifier ,
                 const std::string & message) :
        std::runtime_error(objIdentifier + ": " + message) {
        if(objIdentifier.empty())
            raiseBugException("empty objIdentifier");
    }
};

} // namespace rtt

#endif // RTT_RTTEXCEPTION_H

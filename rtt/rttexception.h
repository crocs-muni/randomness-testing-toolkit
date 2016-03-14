#ifndef RTT_RTTEXCEPTION_H
#define RTT_RTTEXCEPTION_H

#include <exception>
#include <stdexcept>
#include <sstream>
#include <assert.h>

namespace rtt {

class RTTException : public std::runtime_error {
public:
    RTTException(const std::string & objIdentifier ,
                 const std::string & message) :
        std::runtime_error(objIdentifier + ": " + message) {
        assert(!objIdentifier.empty());
    }
};

} // namespace rtt

#endif // RTT_RTTEXCEPTION_H

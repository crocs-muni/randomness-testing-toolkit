#ifndef RTT_RTTEXCEPTION_H
#define RTT_RTTEXCEPTION_H

#include <iostream>
#include <exception>
#include <stdexcept>
#include <sstream>
#include <assert.h>

namespace rtt {

class RTTException : public std::runtime_error {
public:
    RTTException(const std::string & objIdentifier ,
                 const std::string & message) :
        std::runtime_error(message) , id(objIdentifier) {
        assert(!id.empty());
    }

    virtual const char * what() const throw() {
        std::stringstream tmp;
        tmp << id << ": " << std::runtime_error::what();
        return tmp.str().c_str();
    }

private:
    std::string id;
};

} // namespace rtt

#endif // RTT_RTTEXCEPTION_H

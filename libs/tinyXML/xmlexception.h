#ifndef XMLEXCEPTION_H
#define XMLEXCEPTION_H

#include <iostream>
#include <exception>
#include <stdexcept>
#include <sstream>

class XMLException : public std::runtime_error {
public:
    XMLException(std::string message)
        : runtime_error(message) {}

    virtual const char * what() const throw() {
        std::stringstream tmp;
        tmp << "XML processor: " << std::runtime_error::what();
        return tmp.str().c_str();
    }

private:
    std::string msg;
};

#endif // XMLEXCEPTION_H


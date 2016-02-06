#ifndef RTT_BATTERIES_DIEHARDER_SETTING_H
#define RTT_BATTERIES_DIEHARDER_SETTING_H

#include <string>
#include <vector>
#include <stdexcept>

#include "rtt/utils.h"

namespace rtt {
namespace batteries {
namespace dieharder {

class Setting {
public:
    static Setting getInstance(const std::string & arg ,
                               const std::string & value);

    void getConsoleInput(std::ostream & out) const;

    std::string getLogicName() const;

    std::string getArgument() const;

    std::string getArgumentValue() const;

private:
    /*
    =================
    *** Variables ***
    =================
    */
    /* These fields will be set after initialization in */
    /* getInstance */
    std::string argument;
    std::string argumentValue;

    /* Following fields will be initialized in getInstance */
    /* to default values according to agrument */
    std::string logicName;

    /*
    ===============
    *** Methods ***
    ===============
    */
    /* I don't want to allow existence of Test objects */
    /* without initialization that is in getInstance */
    Setting() {}
};

} // namespace dieharder
} // namespace batteries
} // namespace rtt

#endif // RTT_BATTERIES_DIEHARDER_SETTING_H

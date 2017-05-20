#ifndef RTT_CLINTERFACE_CLARGUMENT_H
#define RTT_CLINTERFACE_CLARGUMENT_H

#include <string>

#include "rtt/rttexception.h"
#include "rtt/utils.h"

namespace rtt {
namespace clinterface {

/**
 * @brief The ClArgument class Object for command line argument of type ArgumentType.
 * Stores the argument and its values. Must be set before value extraction. Can be optional.
 */
template <typename ArgumentType>
class ClArgument {
public:
    /**
     * @brief ClArgument Creates unset argument object
     * @param argName Name of the argument
     * @param opt Optionality
     */
    ClArgument(std::string argName, bool opt = false);

    /**
     * @brief ClArgument Creates set argument object
     * @param argName Name of the argument
     * @param argValue Value of the argument
     * @param opt Optionality
     */
    ClArgument(std::string argName, const std::string & argValue, bool opt = false);

    /**
     * @brief getArgumentValue Will return the value if was set. RTTException otherwise.
     * @return Value of the argument.
     */
    ArgumentType getArgumentValue() const;

    /**
     * @brief setArgumentValue Sets the value of the argument. If the value is already set,
     * exception is thrown.
     * @param argValue
     */
    void setArgumentValue(const std::string & argValue);

    /**
     * @brief getArgumentName
     * @return Name of the argument.
     */
    std::string getArgumentName() const {
        return argumentName;
    }

    /**
     * @brief isValid
     * @return Will return false if the argument is neither optional nor set. True otherwise.
     */
    bool isValid() const {
        return (optional || set);
    }

    /**
     * @brief isOptional
     * @return True if optional, false otherwise.
     */
    bool isOptional() const {
        return optional;
    }

    /**
     * @brief isSet
     * @return True if set, false otherwise.
     */
    bool isSet() const {
        return set;
    }

private:
    ClArgument() {}

    std::string objectInfo;
    std::string argumentName;
    ArgumentType argumentValue;
    bool optional = false;
    bool set = false;
};

template<typename ArgumentType>
ClArgument<ArgumentType>::ClArgument(std::string argName, bool opt)
    : argumentName(argName), optional(opt)
{
    objectInfo = "command line argument \"" + argumentName + "\"";
}

template<typename ArgumentType>
ClArgument<ArgumentType>::ClArgument(std::string argName, const std::string & argValue, bool opt)
    : ClArgument<ArgumentType>(argName, opt)
{
    setArgumentValue(argValue);
}

template<typename ArgumentType>
ArgumentType ClArgument<ArgumentType>::getArgumentValue() const {
    if(set) {
        return argumentValue;
    } else {
        throw RTTException(objectInfo, "value is not set");
    }
}

template<typename ArgumentType>
void ClArgument<ArgumentType>::setArgumentValue(const std::string & argValue) {
    if(!set) {
        try {
            argumentValue = Utils::lexical_cast<ArgumentType>(argValue);
            set = true;
        } catch (std::runtime_error & e) {
            throw RTTException(objectInfo, e.what());
        }
    } else {
        throw RTTException(objectInfo, "value can't be set multiple times");
    }
}


} // namespace clinterface
} // namespace rtt

#endif // RTT_CLINTERFACE_CLARGUMENT_H

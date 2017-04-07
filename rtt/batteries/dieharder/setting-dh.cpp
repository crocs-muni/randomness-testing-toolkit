#include "setting-dh.h"

namespace rtt {
namespace batteries {
namespace dieharder {

Setting Setting::getInstance(const std::string & arg,
                             const std::string & value) {
    if(arg.empty() || value.empty())
        throw std::runtime_error("neither argument nor its value"
                                 " can be empty in Dieharder");

    Setting setting;
    if(arg == "-a") {
        throw std::runtime_error("option " + arg + " can't be set by user");
        setting.logicName = "All tests, default options";
    } else if (arg == "-d") {
        throw std::runtime_error("option " + arg + " can't be set by user");
        setting.logicName = "Select specific test";
    } else if (arg == "-f") {
        throw std::runtime_error("option " + arg + " can't be set by user");
        setting.logicName = "Filename";
    } else if (arg == "-B") {
        throw std::runtime_error("option " + arg + " can't be set by user");
        setting.logicName = "Binary output";
    } else if (arg == "-D") {
        throw std::runtime_error("option " + arg + " can't be set by user");
        setting.logicName = "Output flag";
    } else if (arg == "-F") {
        throw std::runtime_error("option " + arg + " can't be set by user");
        setting.logicName = "Lists all output flags";
    } else if (arg == "-c") {
        throw std::runtime_error("option " + arg + " can't be set by user");
        setting.logicName = "Table separator";
    } else if (arg == "-g") {
        throw std::runtime_error("option " + arg + " can't be set by user");
        setting.logicName = "Generator number";
    } else if (arg == "-h") {
        throw std::runtime_error("option " + arg + " can't be set by user");
        setting.logicName = "Help";
    } else if (arg == "-k") {
        throw std::runtime_error("option " + arg + " can't be set by user");
        setting.logicName = "KS flag";
        if(value != "0" && value != "1" && value != "2" && value != "3")
            throw std::runtime_error("invalid value in " + arg + " option: " + value);
    } else if (arg == "-l") {
        throw std::runtime_error("option " + arg + " can't be set by user");
        setting.logicName = "Lists tests";
    } else if (arg == "-L") {
        setting.logicName = "Overlap option";
        if(value != "0" && value != "1")
            throw std::runtime_error("invalid value in " + arg + " option: " + value);
    } else if (arg == "-m") {
        setting.logicName = "Multiply Psamples";
    } else if (arg == "-n") {
        setting.logicName = "N-tuple setting";
    } else if (arg == "-o") {
        throw std::runtime_error("option " + arg + " can't be set by user");
        setting.logicName = "Output generator bytes to file";
    } else if (arg == "-p") {
        throw std::runtime_error("option " + arg + " must be set in config file");
        setting.logicName = "P-samples count";
    } else if (arg == "-P") {
        setting.logicName = "Xoff";
    } else if (arg == "-S") {
        throw std::runtime_error("option " + arg + " can't be set by user");
        setting.logicName = "Seed";
    } else if (arg == "-s") {
        throw std::runtime_error("option " + arg + " can't be set by user");
        setting.logicName = "Reseeding strategy";
    } else if (arg == "-t") {
        setting.logicName = "Random entities in test";
    } else if (arg == "-W") {
        setting.logicName = "Weak threshold";
        float tmp = Utils::strtof(value);
        if(tmp < 0 || tmp > 1)
            throw std::runtime_error("invalid value in " + arg + " option: " + value);
    } else if (arg == "-X") {
        setting.logicName = "Fail threshold";
        float tmp = Utils::strtof(value);
        if(tmp < 0 || tmp > 1)
            throw std::runtime_error("invalid value in " + arg + " option: " + value);
    } else if (arg == "-Y") {
        setting.logicName = "X-trategy - Test To Fail mode";
        if(value != "0" && value != "1" && value != "2")
            throw std::runtime_error("invalid value in " + arg + " option: " + value);
    } else if (arg == "-v") {
        throw std::runtime_error("option " + arg + " can't be set by user");
        setting.logicName = "Verbose output";
    } else if (arg == "-x") {
        setting.logicName = "Test specific option X";
    } else if (arg == "-y") {
        setting.logicName = "Test specific option Y";
    } else if (arg == "-z") {
        setting.logicName = "Test specific option Z";
    } else {
        throw std::runtime_error("unknown option used: " + arg);
    }
    /* Checking if option can be converted into float */
    /* Int can be also in float format*/
    Utils::strtof(value);

    setting.argument = arg;
    setting.argumentValue = value;

    return setting;
}

void Setting::getConsoleInput(std::ostream & out) const {
    out << argument << " " << argumentValue;
}
std::string Setting::getLogicName() const {
    return logicName;
}
std::string Setting::getArgument() const {
    return argument;
}
std::string Setting::getArgumentValue() const {
    return argumentValue;
}




} // namespace dieharder
} // namespace batteries
} // namespace rtt


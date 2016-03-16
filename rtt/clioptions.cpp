#include "rtt/clioptions.h"

namespace rtt {

CliOptions CliOptions::getInstance(int argc , char * argv[]) {
    CliOptions options;
    bool batterySet = false;
    int test = -1;
    int testsBot = -1;
    int testsTop = -1;

    for(int i = 1; i < argc; i += 2) {
        if(i == (argc - 1))
            throw RTTException(options.objectInfo ,
                               "invalid usage of command-line arguments");

        // Battery option
        if(strcmp(argv[i] , "-b") == 0) {
            if(batterySet || argv[i + 1][0] == '-')
                throw RTTException(options.objectInfo ,
                                   "can't set \"-b\" option multiple times or without any value");

            if(strcmp(argv[i + 1] , "dieharder") == 0)
                options.battery = Constants::Battery::DIEHARDER;
            else if(strcmp(argv[i + 1] , "nist_sts") == 0)
                options.battery = Constants::Battery::NIST_STS;
            else if(strcmp(argv[i + 1] , "tu01_smallcrush") == 0)
                options.battery = Constants::Battery::TU01_SMALLCRUSH;
            else if(strcmp(argv[i + 1] , "tu01_crush") == 0)
                options.battery = Constants::Battery::TU01_CRUSH;
            else if(strcmp(argv[i + 1] , "tu01_bigcrush") == 0)
                options.battery = Constants::Battery::TU01_BIGCRUSH;
            else if(strcmp(argv[i + 1] , "tu01_rabbit") == 0)
                options.battery = Constants::Battery::TU01_RABBIT;
            else if(strcmp(argv[i + 1] , "tu01_alphabit") == 0)
                options.battery = Constants::Battery::TU01_ALPHABIT;
            else
                throw RTTException(options.objectInfo ,
                                   "unknown battery set: " + (std::string)argv[i + 1]);
            batterySet = true;

        }
        // Input binary file option
        else if(strcmp(argv[i] , "-f") == 0) {
            if(!options.binFilePath.empty() || argv[i + 1][0] == '-')
                throw RTTException(options.objectInfo ,
                                   "can't set \"-b\" option multiple times or without any value");
            options.binFilePath = argv[i + 1];
        }
        // Custom output file option
        else if(strcmp(argv[i] , "-o") == 0) {
            if(!options.binFilePath.empty() || argv[i + 1][0] == '-')
                throw RTTException(options.objectInfo ,
                                   "can't set \"-o\" option multiple times or without any value");
            options.outFilePath = argv[i + 1];
        }
        // Custom input config option
        else if(strcmp(argv[i] , "-c") == 0) {
            if(!options.inputCfgPath.empty() || argv[i + 1][0] == '-')
                throw RTTException(options.objectInfo ,
                                   "can't set \"-c\" option multiple times or without any value");
            options.inputCfgPath = argv[i + 1];
        }
        // Test option
        else if(strcmp(argv[i] , "-t") == 0) {
            if(test != -1 || argv[i + 1][0] == '-')
                throw RTTException(options.objectInfo ,
                                   "can't set \"-t\" option multiple times or without any value");
            test = Utils::strtoi(argv[i + 1]);
        }
        // Bottom limit test option
        else if(strcmp(argv[i] , "-tbot") == 0) {
            if(testsBot != -1 || argv[i + 1][0] == '-')
                throw RTTException(options.objectInfo ,
                                   "can't set \"-tbot\" option multiple times or without any value");
            testsBot = Utils::strtoi(argv[i + 1]);
        }
        // Top limit test option
        else if(strcmp(argv[i] , "-ttop") == 0) {
            if(testsTop != -1 || argv[i + 1][0] == '-')
                throw RTTException(options.objectInfo ,
                                   "can't set \"-tbot\" option multiple times or without any value");
            testsTop = Utils::strtoi(argv[i + 1]);
        }
        // None of the above, error
        else {
            throw RTTException(options.objectInfo ,
                               "unknown option used: " + (std::string)argv[i]);
        }
    }
    /* Sanity checks */
    if(!batterySet)
        throw RTTException(options.objectInfo ,
                           "option \"-b\" must be correctly set in arguments");
    if(options.binFilePath.empty())
        throw RTTException(options.objectInfo ,
                           "option \"-f\" must be set in arguments");
    //if(test < 0 && testsBot < 0 && testsTop < 0)
    //    throw RTTException(options.objectInfo , "test option must be set either by \"-t\" or with \"-tbot\" and \"-ttop\"");
    /* If test options were entered set them! */
    if((testsBot != -1 && testsTop == -1) || (testsBot == -1 && testsTop != -1))
        throw RTTException(options.objectInfo , "can't set only one of options \"-tbot\" and \"ttop\"");
    if(test >= 0)
        options.testConsts.push_back(test);
    if(testsBot >= 0 && testsTop >= 0){
        for(int i = testsBot; i <= testsTop; i++)
            options.testConsts.push_back(i);
    }
    Utils::sort(options.testConsts);
    /* Setting config path */
    if(options.inputCfgPath.empty())
        options.inputCfgPath = Constants::FILE_DEFAULT_CFG_PATH;

    return options;
}

Constants::Battery CliOptions::getBattery() const {
    return battery;
}

std::string CliOptions::getInputCfgPath() const {
    return inputCfgPath;
}

std::vector<int> CliOptions::getTestConsts() const {
    return testConsts;
}

std::string CliOptions::getBinFilePath() const {
    return binFilePath;
}

std::string CliOptions::getOutFilePath() const {
    return outFilePath;
}

std::string CliOptions::getUsage() {
    std::stringstream ss;
    ss << "\n[USAGE] Randomness Testing Toolkit accepts following options.\n";
    ss << "    -b  Followed with battery that will be used. Following batteries\n";
    ss << "        are accepted: \"dieharder\", \"nist_sts\", \"tu01_smallcrush\",\n";
    ss << "        \"tu01_crush\", \"tu01_bigcrush\", \"tu01_rabbit\", \"tu01_alphabit\"\n";
    ss << "    -f  Followed with path to input binary file that will be analysed by battery.\n";
    ss << "    -o  Followed with path of output file for battery results. If left empty,\n";
    ss << "        default value from config file will be used.\n";
    ss << "    -c  Followed with path to custom config file that will be used instead of\n";
    ss << "        default one. Argument is optional, default path is " << Constants::FILE_DEFAULT_CFG_PATH << "\n";
    ss << "    -t  Followed with constant of test in battery that will be used in testing.\n";
    ss << " -tbot  Bottom border for tests. All tests between \"-tbot\" and \"-ttop\n";
    ss << "        will be used. Can't be used without setting \"-ttop\"\n";
    ss << " -ttop  Top border for tests. All tests between \"-tbot\" and \"-ttop\"\n";
    ss << "        will be used. Can't be used without setting \"-tbot\"\n\n";
    ss << "    -h  Or no arguments will bring up this message.\n\n";
    return ss.str();
}

} // namespace rtt

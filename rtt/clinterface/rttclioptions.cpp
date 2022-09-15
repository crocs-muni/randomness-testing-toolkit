#include "rttclioptions.h"

namespace rtt {
namespace clinterface {

const std::string RTTCliOptions::BATTERY_ARG_NAME            = "-b";
const std::string RTTCliOptions::SETTINGS_FILE_ARG_NAME      = "-s";
const std::string RTTCliOptions::DATA_FILE_ARG_NAME          = "-f";
const std::string RTTCliOptions::CONF_FILE_ARG_NAME          = "-c";
const std::string RTTCliOptions::TEST_ID_ARG_NAME            = "-t";
const std::string RTTCliOptions::JID_ARG_NAME                = "--jid";
const std::string RTTCliOptions::RESULT_STORAGE_ARG_NAME     = "-r";
const std::string RTTCliOptions::RESULT_PATH_PREFIX_ARG_NAME = "--rpath";
const std::string RTTCliOptions::MYSQL_DB_EID_ARG_NAME       = "--eid";
const std::string RTTCliOptions::MYSQL_DB_HOST_ARG_NAME      = "--db-host";
const std::string RTTCliOptions::MYSQL_DB_PORT_ARG_NAME      = "--db-port";
const std::string RTTCliOptions::SKIP_PVALUES                = "--skip-pvalues";

RTTCliOptions RTTCliOptions::getInstance(int argc, char * argv[]) {
    RTTCliOptions options;

    /* Parse the options */
    for(int i = 1; i < argc; i += 2) {
        if(i == (argc - 1))
            throw RTTException(options.objectInfo, "invalid argument count");

        options.setArgumentValue(argv[i], argv[i + 1]);
    }

    /* Check whether are all mandatory options set */
    {
        auto argIsInvalid = [](const auto & arg) {
            return !arg.isValid();
        };
        for(const auto & arg : options.arguments) {
            if(mpark::visit(argIsInvalid, arg)) {
                std::string errMess = mpark::visit([](const auto & arg) {
                    return "argument \"" + arg.getArgumentName() + "\" was not set";
                }, arg);
                throw RTTException(options.objectInfo, errMess);
            }
        }
    }

    /* Additional sanity checks for certain options */
    auto inDataPath = options.getArgumentValue<std::string>(DATA_FILE_ARG_NAME);
    if(!Utils::fileExist(inDataPath))
        throw RTTException(options.objectInfo, Strings::ERR_FILE_OPEN_FAIL + inDataPath);

    auto inConfPath = options.getArgumentValue<std::string>(CONF_FILE_ARG_NAME);
    if(!Utils::fileExist(inConfPath))
        throw RTTException(options.objectInfo, Strings::ERR_FILE_OPEN_FAIL + inConfPath);

    /* Set result storage option to default option if not set */
    if(!options.isArgumentSet(RESULT_STORAGE_ARG_NAME)) {
        options.setArgumentValue(RESULT_STORAGE_ARG_NAME, ResultStorageArg::getDefaultShortName());
    }

    /* Check whether eid is set when mysql storage is se */
    if(options.getResultStorageId() == Constants::ResultStorageID::DB_MYSQL &&
            !options.isArgumentSet(MYSQL_DB_EID_ARG_NAME))
        throw RTTException(options.objectInfo, "option \"--eid\" must be set when db_mysql storage is used");

    return options;
}

std::string RTTCliOptions::getUsage() {
    std::stringstream rval;
    rval << "Randomness Testing Toolkit version " << GIT_COMMIT_SHORT << std::endl;
    rval << "(c) 2015-2017 Centre for Research on Cryptography and Security" << std::endl;
    rval << "This project is under the MIT license. See LICENSE for details." << std::endl;
    rval << std::endl;
    rval << "Project github: https://github.com/crocs-muni/randomness-testing-toolkit" << std::endl;
    rval << "Documentation : https://github.com/crocs-muni/randomness-testing-toolkit/wiki" << std::endl;
    rval << std::endl;

    rval << "============================== [USAGE] ==============================" << std::endl;
    rval << "-h or --help     Print this message.                                 " << std::endl;
    rval << "                                                                     " << std::endl;
    rval << "-s <json-path>   (Optional) Overrides RTT JSON config path.          " << std::endl;
    rval << "                                                                     " << std::endl;
    rval << "-b <battery>     Sets the battery that will be executed. Accepted    " << std::endl;
    rval << "                 values of <battery> are: nist_sts, dieharder,       " << std::endl;
    rval << "                 tu01_smallcrush, tu01_crush, tu01_bigcrush,         " << std::endl;
    rval << "                 tu01_rabbit, tu01_alphabit and tu01_blockalphabit.  " << std::endl;
    rval << "                                                                     " << std::endl;
    rval << "-c <cfg-path>    Sets the path to the file with battery config.      " << std::endl;
    rval << "                 For the structure of the file see documentation.    " << std::endl;
    rval << "                                                                     " << std::endl;
    rval << "-f <data-path>   Sets the path to the file with binary data. The data" << std::endl;
    rval << "                 will be analysed with the chosen battery.           " << std::endl;
    rval << "                                                                     " << std::endl;
    rval << "--rpath <path-prefix>  (Optional) Path prefix for experiment results " << std::endl;
    rval << "                 directory.                                          " << std::endl;
    rval << "                                                                     " << std::endl;
    rval << "-t <test-id>     (Optional) Sets the id of the test that will be     " << std::endl;
    rval << "                 executed. If left empty, tests that are defined in  " << std::endl;
    rval << "                 battery configuration file will be executed.        " << std::endl;
    rval << "                                                                     " << std::endl;
    rval << "-r <storage>     (Optional) Sets the type of the result storage that " << std::endl;
    rval << "                 will be used. Accepted values of <storage> are:     " << std::endl;
    rval << "                 file_report and db_mysql. Default is file_report.   " << std::endl;
    rval << "                 For information about the result storages see       " << std::endl;
    rval << "                 documentation.                                      " << std::endl;
    rval << "                                                                     " << std::endl;
    rval << "--eid <eid>      (Optional) Must be set when <storage> is db_mysql.  " << std::endl;
    rval << "                 Sets id of experiment in the database that will be  " << std::endl;
    rval << "                 assigned the results of this battery execution.     " << std::endl;
    rval << "                                                                     " << std::endl;
    rval << "--jid <jid>      (Optional) Job ID being computed                    " << std::endl;
    rval << "                                                                     " << std::endl;
    rval << "--db-host <host> (Optional) Override MySQL host from config file.    " << std::endl;
    rval << "                                                                     " << std::endl;
    rval << "--db-port <port> (Optional) Override MySQL port from config file.    " << std::endl;
    rval << "                                                                     " << std::endl;
    rval << "--skip-pvalues <1> (Optional) Skip pvalue storage.                   " << std::endl;
    rval << "=====================================================================" << std::endl;
    return rval.str();
}

std::string RTTCliOptions::getInputCfgPath() const {
    return getArgumentValue<std::string>(CONF_FILE_ARG_NAME);
}

std::string RTTCliOptions::getInputDataPath() const {
    return getArgumentValue<std::string>(DATA_FILE_ARG_NAME);
}

std::vector<int> RTTCliOptions::getTestConsts() const {
    if(isArgumentSet(TEST_ID_ARG_NAME))
        return { getArgumentValue<int>(TEST_ID_ARG_NAME) };

    return {};
}

Constants::BatteryID RTTCliOptions::getBatteryId() const {
    return getBatteryArg().getBatteryId();
}

BatteryArg RTTCliOptions::getBatteryArg() const {
    return getArgumentValue<BatteryArg>(BATTERY_ARG_NAME);
}

Constants::ResultStorageID RTTCliOptions::getResultStorageId() const {
    return getResultStorageArg().getResultStorageId();
}

ResultStorageArg RTTCliOptions::getResultStorageArg() const {
    return getArgumentValue<ResultStorageArg>(RESULT_STORAGE_ARG_NAME);
}

std::uint64_t RTTCliOptions::getMysqlDbEid() const {
    return getArgumentValue<std::uint64_t>(MYSQL_DB_EID_ARG_NAME);
}

bool RTTCliOptions::hasJid() const {
    return isArgumentSet(JID_ARG_NAME);
}

std::uint64_t RTTCliOptions::getJid() const {
    return getArgumentValue<std::uint64_t>(JID_ARG_NAME);
}

std::string RTTCliOptions::getResultsPathPrefix() const {
    return getArgumentValue<std::string>(RESULT_PATH_PREFIX_ARG_NAME);
}

bool RTTCliOptions::hasResultsPathPrefix() const {
    return isArgumentSet(RESULT_PATH_PREFIX_ARG_NAME);
}

std::string RTTCliOptions::getSettingsFilePath() const {
    return getArgumentValue<std::string>(SETTINGS_FILE_ARG_NAME);
}

bool RTTCliOptions::hasSettingsFilePath() const {
    return isArgumentSet(SETTINGS_FILE_ARG_NAME);
}

std::string RTTCliOptions::getMysqlDbHost() const {
    return getArgumentValue<std::string>(MYSQL_DB_HOST_ARG_NAME);
}

bool RTTCliOptions::hasMysqlDbHost() const {
    return isArgumentSet(MYSQL_DB_HOST_ARG_NAME);
}

std::uint64_t RTTCliOptions::getMysqlDbPort() const {
    return getArgumentValue<std::uint64_t>(MYSQL_DB_PORT_ARG_NAME);
}

bool RTTCliOptions::hasMysqlDbPort() const {
    return isArgumentSet(MYSQL_DB_PORT_ARG_NAME);
}

bool RTTCliOptions::getSkipPvalues() const {
    return getArgumentValue<int>(SKIP_PVALUES) > 0;
}

bool RTTCliOptions::hasSkipPvalues() const {
    return isArgumentSet(SKIP_PVALUES);
}

bool RTTCliOptions::isArgumentSet(const std::string & argName) const {
    auto cmpArgumentName = [&](const auto & arg) {
        return argName == arg.getArgumentName();
    };
    for(const auto & arg : arguments) {
        if(mpark::visit(cmpArgumentName, arg)) {
            return visit([](const auto & arg){
                return arg.isSet();
            }, arg);
        }
    }
    raiseBugException("no argument with such name: " + argName);
}

void RTTCliOptions::setArgumentValue(const std::string & argName, const std::string & value) {
    auto cmpArgumentName = [&](const auto & arg) {
        return argName == arg.getArgumentName();
    };
    auto setValueOfArgument = [&](auto & arg) {
        arg.setArgumentValue(value);
    };
    for(auto & arg : arguments) {
        if(mpark::visit(cmpArgumentName, arg)) {
            mpark::visit(setValueOfArgument, arg);
            return;
        }
    }
    throw RTTException(objectInfo, "unknown argument - " + argName);
}

} // namespace clinterface
} // namespace rtt

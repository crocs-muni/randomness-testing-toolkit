#include "toolkitsettings.h"

namespace rtt {

const std::string ToolkitSettings::objectInfo = "Toolkit Settings";

ToolkitSettings ToolkitSettings::getInstance(const std::string & cfgFileName) {
    json nRoot = json::parse(Utils::readFileToString(cfgFileName));
    if(nRoot.count("toolkit-settings") != 1)
        throw RTTException(objectInfo , "missing root tag");
    nRoot = nRoot.at("toolkit-settings");

    ToolkitSettings ts;

    /* Variables are set below. If new battery or variables are added set them here.
     * Ideally follow organization that is already here. */

    /*** Logger directories ***/
    if(nRoot.count("logger") != 1)
        throw RTTException(objectInfo , "missing node with logger settings");
    {
        json nLogger            = nRoot.at("logger");
        auto dirPfx             = parseDirectoryPath(nLogger , "dir-prefix" , false);
        ts.loggerRunLogDir      = dirPfx + parseDirectoryPath(nLogger , "run-log-dir");
        ts.loggerDieharderDir   = dirPfx + parseDirectoryPath(nLogger , "dieharder-dir");
        ts.loggerNiststsDir     = dirPfx + parseDirectoryPath(nLogger , "nist-sts-dir");
        ts.loggerSCrushDir      = dirPfx + parseDirectoryPath(nLogger , "tu01-smallcrush-dir");
        ts.loggerCrushDir       = dirPfx + parseDirectoryPath(nLogger , "tu01-crush-dir");
        ts.loggerBCrushDir      = dirPfx + parseDirectoryPath(nLogger , "tu01-bigcrush-dir");
        ts.loggerRabbitDir      = dirPfx + parseDirectoryPath(nLogger , "tu01-rabbit-dir");
        ts.loggerAlphabitDir    = dirPfx + parseDirectoryPath(nLogger , "tu01-alphabit-dir");
        ts.loggerBlAlphabitDir  = dirPfx + parseDirectoryPath(nLogger , "tu01-blockalphabit-dir");
    }

    /*** Result storage settings ***/
    if(nRoot.count("result-storage") != 1)
        throw RTTException(objectInfo , "missing node with result storage settings");
    {
        json nResultStorage = nRoot.at("result-storage");

        /** File storage **/
        if(nResultStorage.count("file") != 1)
            throw RTTException(objectInfo , "missing node with file storage settings");
        {
            json nFile              = nResultStorage.at("file");
            auto dirPfx             = parseDirectoryPath(nFile , "dir-prefix" , false);
            ts.rsFileOutFile        = parseStringValue(nFile , "main-file");
            ts.rsFileDieharderDir   = dirPfx + parseDirectoryPath(nFile , "dieharder-dir");
            ts.rsFileNiststsDir     = dirPfx + parseDirectoryPath(nFile , "nist-sts-dir");
            ts.rsFileSCrushDir      = dirPfx + parseDirectoryPath(nFile , "tu01-smallcrush-dir");
            ts.rsFileCrushDir       = dirPfx + parseDirectoryPath(nFile , "tu01-crush-dir");
            ts.rsFileBCrushDir      = dirPfx + parseDirectoryPath(nFile , "tu01-bigcrush-dir");
            ts.rsFileRabbitDir      = dirPfx + parseDirectoryPath(nFile , "tu01-rabbit-dir");
            ts.rsFileAlphabitDir    = dirPfx + parseDirectoryPath(nFile , "tu01-alphabit-dir");
            ts.rsFileBlAlphabitDir  = dirPfx + parseDirectoryPath(nFile , "tu01-blockalphabit-dir");
        }

        /** Database storage **/
        // Nothing yet...
    }


    /*** Binaries locations ***/
    if(nRoot.count("binaries") != 1)
        throw RTTException(objectInfo , "missing node with binaries locations");
    {
        json nBinaries      = nRoot.at("binaries");
        ts.binaryDieharder  = parseStringValue(nBinaries , "dieharder");
        ts.binaryNiststs    = parseStringValue(nBinaries , "nist-sts");
        ts.binaryTestU01    = parseStringValue(nBinaries , "testu01");
    }

    /* Check existence of binaries */
    if(!Utils::fileExist(ts.binaryDieharder))
        throw RTTException(ts.objectInfo, Strings::ERR_FILE_OPEN_FAIL + ts.binaryDieharder);
    if(!Utils::fileExist(ts.binaryNiststs))
        throw RTTException(ts.objectInfo, Strings::ERR_FILE_OPEN_FAIL + ts.binaryNiststs);
    if(!Utils::fileExist(ts.binaryTestU01))
        throw RTTException(ts.objectInfo, Strings::ERR_FILE_OPEN_FAIL + ts.binaryTestU01);

    /*** Miscelaneous variables ***/
    if(nRoot.count("miscelaneous") != 1)
        throw RTTException(objectInfo , "missing node with miscelaneous settings");
    {
        json nMisc = nRoot.at("miscelaneous");
        /** NIST STS **/
        if(nMisc.count("nist-sts") != 1)
            throw RTTException(objectInfo , "missing node with nist sts misc settings");
        {
            json nMiscNist              = nMisc.at("nist-sts");
            ts.miscNiststsMainResDir    = parseDirectoryPath(nMiscNist , "main-result-dir");
        }
    }


    /*** Battery execution related variables ***/
    if(nRoot.count("execution") != 1)
        throw RTTException(objectInfo , "missing node with battery execution settings");
    {
        json nExec = nRoot.at("execution");
        ts.execMaximumThreads = parseIntegerValue(nExec , "max-parallel-tests" , false);
    }

    return ts;
}

std::string ToolkitSettings::getLoggerRunLogDir() const {
    return loggerRunLogDir;
}

std::string ToolkitSettings::getLoggerRunLogFileName() const {
    return loggerRunLogDir + Utils::formatRawTime(Utils::getRawTime() , "%Y%m%d%H%M%S") + ".log";
}

std::string ToolkitSettings::getRsFileOutFile() const {
    return rsFileOutFile;
}

std::string ToolkitSettings::getLoggerBatteryDir(Constants::Battery battery) const {
    return getBatteryVariable(VariableType::loggerDir , battery);
}

std::string ToolkitSettings::getRsFileBatteryDir(Constants::Battery battery) const {
    return getBatteryVariable(VariableType::rsFileDir , battery);
}

std::string ToolkitSettings::getBinaryBattery(Constants::Battery battery) const {
    return getBatteryVariable(VariableType::binary , battery);
}

std::string ToolkitSettings::getMiscNiststsMainResDir() const {
    return miscNiststsMainResDir;
}

int ToolkitSettings::getExecMaximumThreads() const {
    return execMaximumThreads;
}


/*
                     __                       __
                    |  \                     |  \
  ______    ______   \$$ __     __  ______  _| $$_     ______
 /      \  /      \ |  \|  \   /  \|      \|   $$ \   /      \
|  $$$$$$\|  $$$$$$\| $$ \$$\ /  $$ \$$$$$$\\$$$$$$  |  $$$$$$\
| $$  | $$| $$   \$$| $$  \$$\  $$ /      $$ | $$ __ | $$    $$
| $$__/ $$| $$      | $$   \$$ $$ |  $$$$$$$ | $$|  \| $$$$$$$$
| $$    $$| $$      | $$    \$$$   \$$    $$  \$$  $$ \$$     \
| $$$$$$$  \$$       \$$     \$     \$$$$$$$   \$$$$   \$$$$$$$
| $$
| $$
 \$$
*/

std::string ToolkitSettings::getBatteryVariable(VariableType variableType,
                                                Constants::Battery battery) const {
    /* This is main getter so that all of it is in one place (for future modifications).
     * If new battery is added - create new case for that constant, add it below.
     * If new VariableType is added - add its case into each battery. Also add method
     * for accessing it (see methods getLoggerBatteryDir, getBinaryBattery, etc...)*/
    switch(battery) {
    case Constants::Battery::NIST_STS: {
        switch(variableType) {
        case VariableType::binary:    return binaryNiststs;
        case VariableType::loggerDir: return loggerNiststsDir;
        case VariableType::rsFileDir: return rsFileNiststsDir;
        default:raiseBugException("invalid variable type");
        }
    }
    case Constants::Battery::DIEHARDER: {
        switch(variableType) {
        case VariableType::binary:    return binaryDieharder;
        case VariableType::loggerDir: return loggerDieharderDir;
        case VariableType::rsFileDir: return rsFileDieharderDir;
        default:raiseBugException("invalid variable type");
        }
    }
    case Constants::Battery::TU01_SMALLCRUSH: {
        switch(variableType) {
        case VariableType::binary:    return binaryTestU01;
        case VariableType::loggerDir: return loggerSCrushDir;
        case VariableType::rsFileDir: return rsFileSCrushDir;
        default:raiseBugException("invalid variable type");
        }
    }
    case Constants::Battery::TU01_CRUSH: {
        switch(variableType) {
        case VariableType::binary:    return binaryTestU01;
        case VariableType::loggerDir: return loggerCrushDir;
        case VariableType::rsFileDir: return rsFileCrushDir;
        default:raiseBugException("invalid variable type");
        }
    }
    case Constants::Battery::TU01_BIGCRUSH: {
        switch(variableType) {
        case VariableType::binary:    return binaryTestU01;
        case VariableType::loggerDir: return loggerBCrushDir;
        case VariableType::rsFileDir: return rsFileBCrushDir;
        default:raiseBugException("invalid variable type");
        }
    }
    case Constants::Battery::TU01_RABBIT: {
        switch(variableType) {
        case VariableType::binary:    return binaryTestU01;
        case VariableType::loggerDir: return loggerRabbitDir;
        case VariableType::rsFileDir: return rsFileRabbitDir;
        default:raiseBugException("invalid variable type");
        }
    }
    case Constants::Battery::TU01_ALPHABIT: {
        switch(variableType) {
        case VariableType::binary:    return binaryTestU01;
        case VariableType::loggerDir: return loggerAlphabitDir;
        case VariableType::rsFileDir: return rsFileAlphabitDir;
        default:raiseBugException("invalid variable type");
        }
    }
    case Constants::Battery::TU01_BLOCK_ALPHABIT: {
        switch(variableType) {
        case VariableType::binary:    return binaryTestU01;
        case VariableType::loggerDir: return loggerBlAlphabitDir;
        case VariableType::rsFileDir: return rsFileBlAlphabitDir;
        default:raiseBugException("invalid variable type");
        }
    }
    default:raiseBugException("invalid battery");
    }
}

std::string ToolkitSettings::parseDirectoryPath(const json::object_t & parentNode,
                                                const std::string & childTagName,
                                                bool mandatory) {
    auto rval = parseStringValue(parentNode , childTagName , mandatory);
    if(rval.back() != '/')
        rval.append("/");

    return rval;
}

std::string ToolkitSettings::parseStringValue(const json::object_t & parentNode,
                                              const std::string & childTagName,
                                              bool mandatory) {
    try {
        if(parentNode.count(childTagName) != 1) {
            if(mandatory)
                throw RTTException(objectInfo , "missing node: " + childTagName);

            return "";
        } else {
            return parentNode.at(childTagName);
        }
    } catch (std::domain_error ex) {
        throw RTTException(objectInfo , "failed to parse value in tag: "
                           + childTagName + " - " + ex.what());
    }
}

int ToolkitSettings::parseIntegerValue(const json::object_t & parentNode,
                                               const std::string & childTagName,
                                               bool mandatory) {
    try {
        if(parentNode.count(childTagName) != 1) {
            if(mandatory)
                throw RTTException(objectInfo , "missing node: " + childTagName);

            return 0;
        } else {
            return parentNode.at(childTagName);
        }
    } catch (std::domain_error ex) {
        throw RTTException(objectInfo , "failed to parse value in tag: "
                           + childTagName + " - " + ex.what());
    }
}

} // namespace rtt


#include "resultstoragearg.h"

namespace rtt {
namespace clinterface {

ResultStorageArg::ResultStorageArg() {}

ResultStorageArg::ResultStorageArg(const std::string & resultStorage) {
    init(resultStorage);
}

std::string ResultStorageArg::getName(Constants::ResultStorageID rsId) {
    switch(rsId) {
    case Constants::ResultStorageID::FILE_REPORT:
        return "File (report) storage";
    case Constants::ResultStorageID::DB_MYSQL:
        return "Database (MySQL) storage";
    default:
        raiseBugException("invalid result storage id");
    }
}

std::string ResultStorageArg::getShortName(Constants::ResultStorageID rsId) {
    switch(rsId) {
    case Constants::ResultStorageID::FILE_REPORT:
        return "file_report";
    case Constants::ResultStorageID::DB_MYSQL:
        return "db_mysql";
    default:
        raiseBugException("invalid result storage id");
    }
}

std::string ResultStorageArg::getDefaultShortName() {
    return getShortName(Constants::ResultStorageID::FILE_REPORT);
}

Constants::ResultStorageID ResultStorageArg::getResultStorageId() const {
    initCheck();

    return resultStorageId;
}

std::string ResultStorageArg::getName() {
    initCheck();

    return name;
}

std::string ResultStorageArg::getShortName() {
    initCheck();

    return shortName;
}

Constants::ResultStorageID ResultStorageArg::getResultStorageIdFromShortName(
        const std::string & shortName) {
    Constants::ResultStorageID rsId;
    for(int i = 1; i < static_cast<int>(Constants::ResultStorageID::LAST_ITEM); ++i) {
        rsId = static_cast<Constants::ResultStorageID>(i);
        if(shortName == getShortName(rsId))
            return rsId;
    }
    throw std::runtime_error("unknown result storage argument: " + shortName);
}

void ResultStorageArg::init(const std::string & shortName) {
    if(initialized)
        raiseBugException("ResultStorageArg is already initialized");

    resultStorageId = getResultStorageIdFromShortName(shortName);
    this->shortName = shortName;
    name = getName(resultStorageId);
    initialized = true;
}

void ResultStorageArg::initCheck() const {
    if(!initialized)
        raiseBugException("ResultStorageArg is not initialized");
}

} // namespace clinterface
} // namespace rtt

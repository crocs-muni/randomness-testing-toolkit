#include "istorage.h"

#include "rtt/storage/filestorage.h"
#include "rtt/storage/mysqlstorage.h"

namespace rtt {
namespace storage {

std::unique_ptr<IStorage> IStorage::getInstance(const GlobalContainer & container) {
    switch(container.getRttCliOptions()->getResultStorageId()) {
    case Constants::ResultStorageID::FILE_REPORT:
        return FileStorage::getInstance(container);
    case Constants::ResultStorageID::DB_MYSQL:
        return MySQLStorage::getInstance(container);
    default:
        raiseBugException("invalid result storage id");
    }


    /*if(container.getCliOptions()->getMysqlEid() != 0) {
        return MySQLStorage::getInstance(container);
    } else {
        return FileStorage::getInstance(container);
    }*/
    //return FileStorage::getInstance(container);
}

} // namespace storage
} // namespace rtt

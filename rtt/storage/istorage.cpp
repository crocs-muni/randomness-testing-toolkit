#include "istorage.h"

#include "rtt/storage/filestorage.h"
#include "rtt/storage/mysqlstorage.h"

namespace rtt {
namespace storage {

std::unique_ptr<IStorage> IStorage::getInstance(const GlobalContainer & container) {
    switch(container.getRttCliOptions()->getResultStorageId()) {
    case Constants::ResultStorageID::FILE_REPORT:
        return FileStorage::getInstance(container);
#ifdef USE_MYSQL_BACKEND
    case Constants::ResultStorageID::DB_MYSQL:
        return MySQLStorage::getInstance(container);
#endif
    default:
        raiseBugException("invalid result storage id");
    }
}

} // namespace storage
} // namespace rtt

#include "istorage.h"

#include "rtt/storage/filestorage.h"
#include "rtt/storage/mysqlstorage.h"

namespace rtt {
namespace storage {

std::unique_ptr<IStorage> IStorage::getInstance(const GlobalContainer & container) {
    if(container.getCliOptions()->getMysqlEid() != 0) {
        return MySQLStorage::getInstance(container);
    } else {
        return FileStorage::getInstance(container);
    }
}

} // namespace storage
} // namespace rtt

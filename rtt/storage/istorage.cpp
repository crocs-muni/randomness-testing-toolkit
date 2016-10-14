#include "istorage.h"

#include "rtt/storage/filestorage.h"
#include "rtt/storage/mysqlstorage.h"

namespace rtt {
namespace storage {

std::unique_ptr<IStorage> IStorage::getInstance(const GlobalContainer & container) {
    //return FileStorage::getInstance(container);
    return MySQLStorage::getInstance(container);
}

} // namespace storage
} // namespace rtt

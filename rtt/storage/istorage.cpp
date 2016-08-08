#include "istorage.h"

#include "rtt/storage/filestorage.h"

namespace rtt {
namespace storage {

std::unique_ptr<IStorage> IStorage::getInstance(const GlobalContainer & container) {
    return FileStorage::getInstance(container);
}

} // namespace storage
} // namespace rtt

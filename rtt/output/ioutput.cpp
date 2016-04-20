#include "rtt/output/ioutput-out.h"

#include "rtt/output/storage-file.h"

namespace rtt {
namespace output {

std::unique_ptr<IOutput> IOutput::getInstance(const GlobalContainer & container,
                                              const time_t & creationTime) {
    return file::Storage::getInstance(container , creationTime);
}

} // namespace output
} // namespace rtt

#include "rtt/output/ioutput-out.h"

#include "rtt/output/storage-file.h"

namespace rtt {
namespace output {

std::unique_ptr<IOutput> IOutput::getInstance(const GlobalContainer & container) {
    return file::Storage::getInstance(container);
}

} // namespace output
} // namespace rtt

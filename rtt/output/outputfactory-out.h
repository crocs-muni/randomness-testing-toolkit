#ifndef RTT_OUTPUT_INTERFACEFACTORY_H
#define RTT_OUTPUT_INTERFACEFACTORY_H

#include "rtt/globals.h"

#include "rtt/output/ioutput-out.h"
#include "rtt/output/storage-file.h"

namespace rtt {
namespace output {

class OutputFactory {
public:
    static std::unique_ptr<IOutput> createOutput(const Globals & globals,
                                                 const time_t & creationTime) {
        //throw std::runtime_error("not implemented yet!");
        return file::Storage::getInstance(globals , creationTime);
    }
};

} // namespace output
} // namespace rtt

#endif // RTT_OUTPUT_INTERFACEFACTORY_H

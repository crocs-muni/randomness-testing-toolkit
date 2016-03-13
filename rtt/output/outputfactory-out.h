#ifndef RTT_OUTPUT_INTERFACEFACTORY_H
#define RTT_OUTPUT_INTERFACEFACTORY_H

#include "rtt/constants.h"
#include "rtt/clioptions.h"

#include "rtt/output/ioutput-out.h"
#include "rtt/output/storage-file.h"

namespace rtt {
namespace output {

class OutputFactory {
public:
    static std::unique_ptr<IOutput> createOutput(TiXmlNode * root ,
                                                 const CliOptions & options ,
                                                 const time_t & creationTime) {
        //throw std::runtime_error("not implemented yet!");
        return file::Storage::getInstance(root , options , creationTime);
    }
};

} // namespace output
} // namespace rtt

#endif // RTT_OUTPUT_INTERFACEFACTORY_H

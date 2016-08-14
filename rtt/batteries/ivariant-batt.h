#ifndef RTT_BATTERIES_IVARIANT_H
#define RTT_BATTERIES_IVARIANT_H

#include "rtt/globalcontainer.h"

namespace rtt {
namespace batteries {

class IVariant {
public:
    static std::unique_ptr<IVariant> getInstance(int testId, uint variantIdx,
                                                 const GlobalContainer & cont);

    virtual ~IVariant() {}

    virtual std::string getCliArguments() const = 0;

    virtual std::string getStdInput() const = 0;

    virtual std::vector<std::string> getUserSettings() const = 0;

protected:
    IVariant() {}
};

} // namespace batteries
} // namespace rtt

#endif // RTT_BATTERIES_IVARIANT_H

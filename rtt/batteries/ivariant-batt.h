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

    std::string getCliArguments() const;

    std::string getStdInput() const;

    std::vector<std::string> getUserSettings() const;

protected:
    std::string objectInfo;
    int testId;
    uint variantIdx;
    Constants::Battery battId;
    std::string binaryDataPath;

    std::vector<std::string> userSettings;
    std::string cliArguments;
    std::string stdInput;

    IVariant(int testId, uint variantIdx, const GlobalContainer & cont);
};

} // namespace batteries
} // namespace rtt

#endif // RTT_BATTERIES_IVARIANT_H

#ifndef RTT_BATTERIES_NISTSTS_VARIANT_H
#define RTT_BATTERIES_NISTSTS_VARIANT_H

#include "rtt/batteries/ivariant-batt.h"
#include "rtt/batteries/testconstants.h"

namespace rtt {
namespace batteries {
namespace niststs {

class Variant : public IVariant {
public:
    static std::unique_ptr<Variant> getInstance(int testId, uint variationIndex,
                                                const GlobalContainer & cont);



    std::string getCliArguments() const;

    std::string getStdInput() const;

    std::vector<std::string> getUserSettings() const;

private:
    /* Variables */

    // General fields
    std::string objectInfo;
    int testId;
    Constants::Battery batt;
    std::string binaryDataPath;

    std::vector<std::string> userSettings;
    std::string cliArguments;
    std::string stdInput;

    // Nist sts specific fields
    std::string streamSize;
    std::string streamCount;
    std::string blockLength;
    bool adjustableBlockLength;

    /* Methods */
    Variant() {}

    void buildStrings();
};

} // namespace niststs
} // namespace batteries
} // namespace rtt

#endif // RTT_BATTERIES_NISTSTS_VARIANT_H

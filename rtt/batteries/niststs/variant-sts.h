#ifndef RTT_BATTERIES_NISTSTS_VARIANT_H
#define RTT_BATTERIES_NISTSTS_VARIANT_H

#include "rtt/batteries/ivariant-batt.h"
#include "rtt/batteries/testrunner-batt.h"

namespace rtt {
namespace batteries {
namespace niststs {

class Variant : public IVariant {
public:
    static std::unique_ptr<Variant> getInstance(int testId, std::string testObjInf,
                                                uint variantIdx, const GlobalContainer & cont);

    void execute();

    void setTestDir_mux(std::mutex * value);

    std::vector<std::string> getPValueFiles() const;

private:
    /* Variables */
    std::mutex * testDir_mux;
    std::string resultSubDir;
    std::string streamSize;
    std::string streamCount;
    std::string blockLength;
    bool adjustableBlockLength;

    /* pvalues will be read into this after execution */
    std::vector<std::string> pValueFiles;

    /* Methods */
    Variant(int testId, std::string testObjInf,
            uint variantIdx, const GlobalContainer & cont)
        : IVariant(testId, testObjInf, variantIdx, cont)
    {}

    void buildStrings();

    void readNistStsOutFiles();
};

} // namespace niststs
} // namespace batteries
} // namespace rtt

#endif // RTT_BATTERIES_NISTSTS_VARIANT_H

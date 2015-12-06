#include "rtt/batteries/niststs/battery.h"

namespace rtt {
namespace batteries {
namespace niststs {

Battery * Battery::getInstance(const CliOptions & options) {
    TiXmlNode * cfgRoot = NULL;
    loadXMLFile(cfgRoot , options.getInputCfgPath());

    std::vector<int> testIndices = options.getTestConsts();
    Test test = Test::getInstance(static_cast<TestIndex>(testIndices[0]) , cfgRoot , options.getBinFilePath());

    delete cfgRoot;
}



} // namespace niststs
} // namespace batteries
} // namespace rtt

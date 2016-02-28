#include "itest-batt.h"

namespace rtt {
namespace batteries {

std::string ITest::getTestOrDefOpt(TiXmlNode * cfgRoot , TiXmlNode * testNode ,
                                   const std::string & defaultPath ,
                                   const std::string & testPath) {
    if(!cfgRoot)
        throw std::runtime_error("null root");

    std::string nodeValue;
    if(!testNode) {
        nodeValue = getXMLElementValue(cfgRoot , defaultPath);
        return nodeValue;
    }

    nodeValue = getXMLElementValue(testNode , testPath);
    if(nodeValue.empty()) {
        nodeValue = getXMLElementValue(cfgRoot , defaultPath);
        return nodeValue;
    } else {
        return nodeValue;
    }
}

} // namespace batteries
} // namespace rtt


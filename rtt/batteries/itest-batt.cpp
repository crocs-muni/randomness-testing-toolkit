#include "itest-batt.h"

#include "rtt/batteries/niststs/test-sts.h"
#include "rtt/batteries/dieharder/test-dh.h"
#include "rtt/batteries/testu01/test-tu01.h"

namespace rtt {
namespace batteries {

std::unique_ptr<ITest> ITest::getInstance(int testIndex,
                                          const Globals & globals) {
    switch(globals.getCliOptions()->getBattery()) {
    case Constants::Battery::DIEHARDER:
        return dieharder::Test::getInstance(testIndex , globals);
    case Constants::Battery::NIST_STS:
        return niststs::Test::getInstance(testIndex , globals);
    case Constants::Battery::TU01_SMALLCRUSH:
    case Constants::Battery::TU01_CRUSH:
    case Constants::Battery::TU01_BIGCRUSH:
    case Constants::Battery::TU01_RABBIT:
    case Constants::Battery::TU01_ALPHABIT:
        return testu01::Test::getInstance(testIndex , globals);
    default:raiseBugException("invalid battery");
    }
}

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


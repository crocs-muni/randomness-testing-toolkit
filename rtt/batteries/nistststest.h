#ifndef RTT_BATTERIES_NISTSTSTEST_H
#define RTT_BATTERIES_NISTSTSTEST_H

#include <iostream>

#include "rtt/utils.h"

namespace rtt {
namespace batteries {

class NistStsTest {
private:
    std::string logicalName;
    std::string resultDir;
    int subTestCount;
    std::vector<std::vector<float>> testPValues;
    std::string testLog;
public:
    NistStsTest(std::string name , std::string dir , int testCount);

private:
    std::vector<float> readPVals(std::string fileName);
};

} // namespace batteries
} // namespace rtt

#endif // RTT_BATTERIES_NISTSTSTEST_H

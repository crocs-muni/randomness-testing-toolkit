#ifndef RTT_OUTPUT_INTERFACE_H
#define RTT_OUTPUT_INTERFACE_H

#include <string>
#include <vector>

namespace rtt {
namespace output {

class Interface {
public:

    virtual ~Interface() {}

    virtual void addNewTest(const std::string & testName) = 0;

    virtual void setTestOptions(const std::vector<std::string> & options) = 0;

    virtual void addSubTest() = 0;

    virtual void addStatisticResult(const std::string & statName , double value , int precision) = 0;

    virtual void addStatisticResult(const std::string & statName , const std::string & value , bool failed) = 0;

    virtual void addPValues(const std::vector<double> & pvals , int precision = 6) = 0;

    virtual void finalizeSubTest() = 0;

    virtual void finalizeTest() = 0;

    virtual void finalizeReport() = 0;
};

} // namespace output
} // namespace rtt

#endif // RTT_OUTPUT_INTERFACE_H
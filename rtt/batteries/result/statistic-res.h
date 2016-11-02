#ifndef RTT_BATTERIES_RESULT_STATISTIC_H
#define RTT_BATTERIES_RESULT_STATISTIC_H

#include <string>

#include "rtt/rttexception.h"

namespace rtt {
namespace batteries {
namespace result {

class Statistic {
public:
    static Statistic getInstance(const std::string & name,
                                 double value);

    std::string getName() const;

    double getValue() const;

private:
    Statistic(const std::string & name, double value)
        : name(name), value(value)
    {}

    std::string name;

    double value;
};

} // namespace result
} // namespace batteries
} // namespace rtt

#endif // RTT_BATTERIES_RESULT_STATISTIC_H

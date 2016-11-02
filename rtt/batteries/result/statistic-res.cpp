#include "statistic-res.h"

namespace rtt {
namespace batteries {
namespace result {

Statistic Statistic::getInstance(const std::string & name, double value) {
    if(name.empty())
        raiseBugException("empty statistic name");

    return Statistic(name, value);
}

std::string Statistic::getName() const {
    return name;
}

double Statistic::getValue() const {
    return value;
}

} // namespace result
} // namespace batteries
} // namespace rtt

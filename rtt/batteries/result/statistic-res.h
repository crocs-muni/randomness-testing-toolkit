#ifndef RTT_BATTERIES_RESULT_STATISTIC_H
#define RTT_BATTERIES_RESULT_STATISTIC_H

#include <string>

#include "rtt/rttexception.h"

namespace rtt {
namespace batteries {
namespace result {

/**
 * @brief The Statistic class Small class for storing result of a single statistic.
 */
class Statistic {
public:
    /**
     * @brief getInstance Initializes the object
     * @param name Human-readable name of the statistic
     * @param value Value of the statistic
     * @return instance
     */
    static Statistic getInstance(const std::string & name,
                                 double value);

    /**
     * @brief getName
     * @return Name of the statistic
     */
    std::string getName() const;

    /**
     * @brief getValue
     * @return Value of the statistic
     */
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

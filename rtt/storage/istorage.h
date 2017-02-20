#ifndef RTT_STORAGE_ISTORAGE_H
#define RTT_STORAGE_ISTORAGE_H

#include <string>
#include <vector>

#include "rtt/globalcontainer.h"
#include "rtt/batteries/itestresult-batt.h"

namespace rtt {
namespace storage {

class IStorage {
public:
    static std::unique_ptr<IStorage> getInstance(const GlobalContainer & container);

    virtual ~IStorage() {}

    virtual void writeResults(const std::vector<batteries::ITestResult *> & testResults) = 0;
};

} // namespace storage
} // namespace rtt

#endif // RTT_STORAGE_ISTORAGE_H

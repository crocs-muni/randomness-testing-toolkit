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
    /**
     * @brief getInstance Creates storage
     * object according to global settings in container
     * @param container Object with global settings
     * @return
     */
    static std::unique_ptr<IStorage> getInstance(const GlobalContainer & container);

    /**
     * @brief ~IStorage destructor
     */
    virtual ~IStorage() {}

    /**
     * @brief init Initializes the object. This must be done before writing any results.
     * If done multiple times on the same object, peviously written results may be discarded.
     */
    virtual void init() = 0;

    /**
     * @brief writeResults Will write results into the storage.
     * Can be called multiple times, the results will acummulate.
     * @param testResults Results of the tests
     */
    virtual void writeResults(const std::vector<batteries::ITestResult *> & testResults) = 0;

    /**
     * @brief close Closes storage, resets the state, saves changes in the files or databases.
     */
    virtual void close() = 0;

    /**
     * @brief addBatteryError Adds single battery runtime error into storage.
     * @param error
     */
    virtual void addBatteryError(const std::string & error) = 0;

    /**
     * @brief addBatteryErrors Adds multiple battery runtime errors into storage.
     * @param errors
     */
    virtual void addBatteryErrors(const std::vector<std::string> & errors) = 0;

    /**
     * @brief addBatteryWarning Adds single battery runtime warning into storage.
     * @param warning
     */
    virtual void addBatteryWarning(const std::string & warning) = 0;

    /**
     * @brief addBatteryWarnings Adds multiple battery runtime warnings into storage.
     * @param warnings
     */
    virtual void addBatteryWarnings(const std::vector<std::string> & warnings) = 0;

    /**
     * Ensures that storage is working before working with it (e.g., database connection is alive)
     */
    virtual void checkStorage() {};
};

} // namespace storage
} // namespace rtt

#endif // RTT_STORAGE_ISTORAGE_H

/*
 * =============================================================
 * *************************** TODO! ***************************
 * =============================================================
 * (It's important to have priorities!)
 * 1. Interface for stat batteries              (Ok)
 *  1.1. Settings                               (Ok)
 *  1.2. Executable runner                      (Ok)
 *  1.3. Reading results from battery output    (Ok)
 *  1.4. Log storage - battery and run output   (Ok)
 *  1.5. Run multiple tests in parallel         (Ok)
 * 2. Storing processed results
 *  2.1. Output Interface                       (Ok)
 *  2.2. Into file structure                    (Ok)
 *  2.3. Into database                          (Ok)
 * 3. Miscelaneous
 *  3.1. Better exception handling              (Ok)
 *  3.2. Batteries runtime error handling       (Ok)
 *  3.3. File logger                            (Ok)
 *  3.4. Better config file organization        (Ok)
 *  3.5. Create CMake project                   (Final step)
 *  3.6. Write documentation, refactor          (More final step)
 * 4. ???
 *     .
 *     .
 *     .
 * 5. Profit!
 * =============================================================
 * *************************************************************
 * =============================================================
 */
#include <iostream>
#include <stdexcept>

#include "rtt/storage/istorage.h"
#include "rtt/batteries/ibattery-batt.h"
#include "rtt/globalcontainer.h"
#include "rtt/version.h"

/* This line must stay in main! */
INITIALIZE_EASYLOGGINGPP

using namespace rtt;

int main (int argc , char * argv[]) try {
    if(argc == 1 || (argc == 2 && strcmp(argv[1] , "-h") == 0)) {
        std::cout << CliOptions::getUsage() << std::endl;
        return -1;
    }

    /* Initialization of global container.
     * Since we can't be sure if logger was initialized,
     * errors are written to cout and no log is created. */
    GlobalContainer gc;
    try {
        gc.initCliOptions(argc , argv);
        gc.initToolkitSettings(Constants::FILE_TOOLKIT_SETTINGS);

    } catch (std::exception & ex) {
        std::cout << "[Invalid toolkit configuration] " << ex.what() << std::endl;
        return -1;
    }

    /* Logger must be initialized last as it uses settings from main configuration file
     * and command line options. Otherwise exception is raised. */
    gc.initLogger("Randomness_Testing_Toolkit", true);

    /* Logger is now created and all subsequent errors are logged. */

    try {
        /* Initializing storage */
        auto storage = storage::IStorage::getInstance(gc);

        try {
            /* Initialization of battery configuration in container */
            gc.initBatteriesConfiguration(gc.getCliOptions()->getInputCfgPath());
            /* Initialization of battery */
            auto battery = batteries::IBattery::getInstance(gc);
            /* Executing analysis */
            battery->runTests();
            /* Obtaining and storing results */
            const auto & results = battery->getTestResults();;
            storage->writeResults(Utils::getRawPtrs(results));
            /* And we are done. */

        } catch(std::exception & ex) {
            /* Something happened during battery initialization/execution */
            gc.getLogger()->error(ex.what());
            /* Storage is still active, error can be stored. */
            storage->addBatteryWarnings(gc.getLogger()->getWarningMessages());
            storage->addBatteryErrors(gc.getLogger()->getErrorMessages());
            /* Close storage, end the program. */
            storage->close();
            return -1;
        }

        /* Store warnings and errors into storage */
        storage->addBatteryWarnings(gc.getLogger()->getWarningMessages());
        storage->addBatteryErrors(gc.getLogger()->getErrorMessages());
        /* Call to close storage is important -
         * changes are commited, files saved, etc... */
        storage->close();

    } catch(std::exception & ex) {
        /* Storage creation failed. */
        gc.getLogger()->error(ex.what());
        return -1;
    }

} catch(std::exception & ex) {
    std::cout << "[Error] " << ex.what() << std::endl << std::endl;
    return -1;
}

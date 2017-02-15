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
 *  .
 *  .
 *  .
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
    GlobalContainer container;
    try {
        container.initCliOptions(argc , argv);
        container.initToolkitSettings(Constants::FILE_TOOLKIT_SETTINGS);
        container.initBatteriesConfiguration(container.getCliOptions()->getInputCfgPath());

    } catch (std::exception & ex) {
        std::cout << "[Invalid configuration] " << ex.what() << std::endl;
        return -1;
    }

    /* Logger must be initialized last as it uses settings from main configuration file
     * and command line options. Otherwise exception is raised. */
    container.initLogger("Randomness_Testing_Toolkit", true);

    /* Logger is now created and all subsequent errors are logged. */
    try {
        /* Initializing storage */
        auto storage = storage::IStorage::getInstance(container);

        try {
            /* Initialization of battery */
            auto battery = batteries::IBattery::getInstance(container);
            /* Executing analysis */
            battery->runTests();
            /* Obtaining and storing results */
            auto results = battery->getTestResults();;
            storage->writeResults(Utils::getRawPtrs(results));
            /* Store warnings and errors into storage */
            // TODO: store errs/warns.
            /* And we are done. */


        } catch(std::exception & ex) {
            /* Something happened during battery initialization/execution */
            /* Storage is still active, error can be stored. */
            // TODO: store error to storage here!!!
            container.getLogger()->error(ex.what());
            return -1;
        }

    } catch(std::exception & ex) {
        /* Storage creation failed. */
        container.getLogger()->error(ex.what());
        return -1;
    }

} catch(std::exception & ex) {
    std::cout << "[Error] " << ex.what() << std::endl << std::endl;
    return -1;
}

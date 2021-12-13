#include <iostream>
#include <stdexcept>

#include "rtt/storage/istorage.h"
#include "rtt/batteries/ibattery-batt.h"
#include "rtt/clinterface/rttclioptions.h"
#include "rtt/globalcontainer.h"
#include "rtt/version.h"

/* This line must stay in main! */
INITIALIZE_EASYLOGGINGPP

using namespace rtt;

int main (int argc , char * argv[]) try {
    if(argc == 1 || (argc == 2 && (strcmp(argv[1], "-h") == 0 ||
                                   strcmp(argv[1], "--help") == 0))) {
        std::cout << clinterface::RTTCliOptions::getUsage() << std::endl;
        return -1;
    }

    /* Initialization of global container.
     * Since we can't be sure if logger was initialized,
     * errors are written to cout and no log is created. */
    GlobalContainer gc;
    try {
        gc.initRttCliOptions(argc , argv);
        gc.initToolkitSettings(gc.getRttCliOptions()->hasSettingsFilePath() ?
                               gc.getRttCliOptions()->getSettingsFilePath() :
                               Constants::FILE_TOOLKIT_SETTINGS);

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
        storage->init();

        try {
            /* Initialization of battery configuration in container -
             * should something go wrong, the error is logged in storage */
            gc.initBatteriesConfiguration(gc.getRttCliOptions()->getInputCfgPath());
            /* Initialization of battery */
            auto battery = batteries::IBattery::getInstance(gc);
            /* Executing analysis */
            battery->runTests();
            /* Obtaining and storing results */
            const auto & results = battery->getTestResults();;
            storage->checkStorage();
            storage->writeResults(Utils::getRawPtrs(results));
            /* And we are done. */

        } catch(std::exception & ex) {
            /* Something happened during battery initialization/execution */
            gc.getLogger()->error(ex.what());
        }

        /* Store warnings and errors into storage */
        storage->checkStorage();
        storage->addBatteryWarnings(gc.getLogger()->getWarningMessages());
        storage->addBatteryErrors(gc.getLogger()->getErrorMessages());
        /* Call to close storage is important -
         * changes are committed, files saved, etc... */
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

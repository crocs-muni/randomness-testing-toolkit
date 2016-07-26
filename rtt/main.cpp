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
 *  2.3. Into database                          (Will be done in next pahse)
 * 3. Miscelaneous
 *  3.1. Better exception handling              (Ok)
 *  3.2. Batteries runtime error handling       (Ok)
 *  3.3. File logger                            (Ok)
 *  3.4. Better config file organization        (Moving on to JSON format)
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
#include <cmath>

#include "rtt/batteries/ibattery-batt.h"
#include "rtt/globalcontainer.h"
#include "rtt/version.h"
#include "rtt/batteries/dieharder/battery-dh.h"

/* This line must stay in main! */
INITIALIZE_EASYLOGGINGPP

using namespace rtt;

//#define TESTING

int main (int argc , char * argv[]) {
#ifdef TESTING
#else
    if(argc == 1 || (argc == 2 && strcmp(argv[1] , "-h") == 0)) {
        std::cout << CliOptions::getUsage() << std::endl;
        return -1;
    }

    /* Initialization of global container.
     * Since I can't be sure if logger was initialized,
     * errors are written to cout and no log is created. */
    GlobalContainer container;
    try {
        container.initCliOptions(argc , argv);
        container.initBatteriesConfiguration(container.getCliOptions()->getInputCfgPath());
        container.initToolkitSettings(Constants::FILE_TOOLKIT_SETTINGS);
        /* A bit clumsy logger initialization */
        /* I should really change it to something more elegant */
        container.initLogger("Main_Application" ,
                             Utils::createLogFileName(container.getCreationTime() ,
                                                      container.getToolkitSettings()->getLoggerRunLogDir() ,
                                                      container.getCliOptions()->getBinFilePath() ,
                                                      Constants::batteryToStringShort(container.getCliOptions()->getBattery())),
                             true);
    } catch(RTTException ex) {
        std::cout << "[ERROR] " << ex.what() << std::endl << std::endl;
        return -1;
    } catch(XMLException ex) {
        std::cout << "[ERROR] " << ex.what() << std::endl << std::endl;
        return -1;
    } catch (BugException ex) {
        std::cout << "[ERROR] " << ex.what() << std::endl << std::endl;
        return -1;
    } catch(std::runtime_error ex) {
        std::cout << "[ERROR] " << ex.what() << std::endl << std::endl;
        return -1;
    } catch(std::bad_alloc ex) {
        std::cout << "[ERROR] " << ex.what() << std::endl << std::endl;
        return -1;
    }

    /* Actual functionality will be here... in time. */
    /* EDIT: In fact there already is some functionality. */
    try {
        /* Creation and execution of battery */
        auto battery = batteries::IBattery::getInstance(container);
        /* Executing tests as set in settings */
        battery->runTests();
        /* Processing and storing of results of the run */
        battery->processStoredResults();

    } catch(RTTException ex) {
        container.getLogger()->error(ex.what());
    } catch(XMLException ex) {
        container.getLogger()->error(ex.what());
    } catch (BugException ex) {
        container.getLogger()->error(ex.what());
    } catch(std::runtime_error ex) {
        container.getLogger()->error(ex.what());
    } catch(std::bad_alloc ex) {
        container.getLogger()->error(ex.what());
    }
#endif
}

//  =============================================================
//  *************************** TODO! ***************************
//  =============================================================
//  (It's important to have priorities!)
//  1. Interface for stat batteries                 (Ok)
//      1.1. Settings                               (Ok)
//      1.2. Executable runner                      (Ok)
//      1.3. Reading results from battery output    (Ok)
//      1.4. Log storage - battery and run output   (Ok)
//      1.5. Run multiple tests in parallel         (Ok)
//  2. Storing processed results
//      2.1. Output Interface                       (Ok)
//      2.2. Into file structure                    (Ok)
//      2.3. Into database                          (Not until Misc is completed)
//  3. Miscelaneous
//      3.1. Better exception handling
//      3.2. Batteries runtime error handling
//      3.3. File logger
//      3.4. Better config file organization
//      3.5. Create CMake project
//      3.6. Write documentation, refactor
//  4. ???
//      .
//      .
//      .
//  5. Profit!
//  =============================================================
//  *************************************************************
//  =============================================================
#include <iostream>
#include <stdexcept>
#include <cmath>

#include "rtt/batteries/batteryfactory-batt.h"
#include "rtt/toolkitsettings.h"
#include "rtt/clioptions.h"
#include "rtt/version.h"
#include "rtt/bugexception.h"
#include "rtt/rttexception.h"

//#define TESTING

using namespace rtt;

int main (int argc , char * argv[]) {
#ifdef TESTING
    try {
        auto toolkitSettings = ToolkitSettings::getInstance();
        raiseBugException("some bullshit");
    } catch (RTTException ex) {
        std::cout << "[ERROR] " << ex.what() << std::endl;
    } catch (XMLException ex) {
        std::cout << "[ERROR] " << ex.what() << std::endl;
    } catch (BugException ex) {
        std::cout << "[BUG]   " << ex.what() << std::endl;
    } catch (std::runtime_error ex) {
        std::cout << "[ERROR] " << ex.what() << std::endl;
    }

#else
    std::cout << "Randomness Testing Toolkit start. (build " << GIT_COMMIT_SHORT << ")" << std::endl;
    std::cout << "Start: " << Utils::getTime() << std::endl;

    if(argc == 1 || (argc == 2 && strcmp(argv[1] , "-h") == 0))
        std::cout << CliOptions::getUsage() << std::endl;

    /* Actual functionality will be here... in time. */
    try {
        auto options = CliOptions::getInstance(argc , argv);
        auto battery = batteries::BatteryFactory::createBattery(options);
        battery->runTests();
        battery->processStoredResults();
    } catch(RTTException ex) {
        std::cout << "[ERROR] " << ex.what() << std::endl;
    } catch(XMLException ex) {
        std::cout << "[ERROR] " << ex.what() << std::endl;
    } catch (BugException ex) {
        std::cout << "[BUG]   " << ex.what() << std::endl;
    } catch(std::runtime_error ex) {
        std::cout << "[ERROR] " << ex.what() << std::endl;
    } catch(std::bad_alloc ex) {
        std::cout << "[ERROR] Memory allocation failed: " << ex.what() << std::endl;
    }
    std::cout << "End: " << Utils::getTime() << std::endl;
#endif
}

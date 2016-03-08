//  =============================================================
//  *************************** TODO! ***************************
//  =============================================================
//  (It's important to have priorities!)
//  1. Interface for stat batteries                 (NIST STS , Dieharder , TestU01)
//      1.1. Settings                               (Ok)
//      1.2. Executable runner                      (Ok)
//      1.3. Reading results from battery output    (Ok)
//      1.4. Log storage - battery and run output   (Ok)
//      1.5. Run multiple tests in parallel         (Work in progress...)
//  2. Storing processed results
//      2.1. Output Interface                       (Ok)
//      2.2. Into file structure                    (Ok)
//      2.3. Into database
//  3. Logger, CMake project (?)
//      3.1. Maybe custom exception?
//  4. ???
//  .
//  .
//  .
//  5. Profit! (and maybe write documentation)
//  =============================================================
//  *************************************************************
//  =============================================================
#include <iostream>
#include <stdexcept>
#include <cmath>

#include "rtt/batteries/batteryfactory-batt.h"
#include "rtt/options.h"
#include "rtt/version.h"

//#define TESTING

using namespace rtt;

int main (int argc , char * argv[]) {
#ifdef TESTING
#else
    std::cout << "Randomness Testing Toolkit start. (build " << GIT_COMMIT_SHORT << ")" << std::endl;
    std::cout << "Start: " << Utils::getTime() << std::endl;

    CliOptions options;
    try {
        options.init(argc , argv);
    }
    catch(std::runtime_error ex) {
        std::cout << "[ERROR] " << ex.what() << std::endl;
        std::cout << options.getUsage();
        return 0;
    }

    /* Actual functionality will be here... in time. */
    try {
        std::unique_ptr<batteries::IBattery> battery =
                 batteries::BatteryFactory::createBattery(options);
        battery->runTests();
        battery->processStoredResults();
    } catch(XMLException ex) {
        std::cout << "[ERROR] " << ex.what() << std::endl;
    } catch(std::runtime_error ex) {
        std::cout << "[ERROR] " << ex.what() << std::endl;
    } catch(std::bad_alloc ex) {
        std::cout << "[ERROR] Memory allocation failed: " << ex.what() << std::endl;
    }
    std::cout << "End: " << Utils::getTime() << std::endl;
	return 0;
#endif
}

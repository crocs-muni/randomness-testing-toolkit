//  =============================================================
//  *************************** TODO! ***************************
//  =============================================================
//  (It's important to have priorities!)
//  1. Interface for stat batteries (work in progress...)
//      1.1. Settings                               (NIST STS , Dieharder , TestU01)
//      1.2. Executable runner                      (NIST STS , Dieharder , TestU01)
//      1.3. Reading results from battery output    (NIST STS , Dieharder , TestU01)
//      1.4. Log storage
//      1.5. Result processing and storing          (need database for this)
//  2. Logger, CMake project (?)
//      2.1. Maybe custom exception?
//  3. Store results into database
//  4. ???
//      .
//      .
//      .
//  5. Profit! (and write documentation maybe)
//  =============================================================
//  *************************************************************
//  =============================================================
#include <iostream>
#include <stdexcept>
#include <cmath>

#include "rtt/batteries/interfacefactory.h"
#include "rtt/options.h"
#include "rtt/version.h"

//#define TESTING

int main (int argc , char * argv[]) {
#ifdef TESTING
    /* Sometimes, here is some code I use for testing. */
#else
    std::cout << "Randomness Testing Toolkit start. (build " << GIT_COMMIT_SHORT << ")" << std::endl;

    rtt::CliOptions options;
    try {
        options.init(argc , argv);
    }
    catch(std::runtime_error ex) {
        std::cout << "[ERROR] " << ex.what() << std::endl;
        std::cout << options.getUsage();
        return 0;
    }

    // Actual functionality will be here... in time.
    try {
        std::unique_ptr<rtt::batteries::Interface> battery =
                rtt::InterfaceFactory::createBattery(options);
        battery->runTests();
        // Processing not implemented, only throws something
        battery->processStoredResults();
    } catch(std::runtime_error ex) {
        std::cout << "[ERROR] " << ex.what() << std::endl;
    } catch(std::bad_alloc ex) {
        std::cout << "[ERROR] Memory allocation failed: " << ex.what() << std::endl;
    }

	return 0;
#endif
}

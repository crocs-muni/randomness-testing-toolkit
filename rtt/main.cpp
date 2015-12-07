//  =============================================================
//  *************************** TODO! ***************************
//  =============================================================
//  (It's important to have priorities!)
//  1. Interface for stat batteries (work in progress...)
//      1.1. Settings                               (NIST STS , Dieharder)
//      1.2. Executable runner                      (NIST STS , Dieharder)
//      1.3. Reading results from battery output    (NIST STS , Dieharder)
//      1.4. Result processing and storing          (need database for this)
//  2. Logger, CMake project (?)
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

#include "rtt/batteries/interfacefactory.h"
#include "rtt/options.h"
#include "rtt/version.h"

int main (int argc , char * argv[]) {
    std::cout << "Randomness Testing Toolkit start. (build " << GIT_COMMIT_SHORT << ")" << std::endl;

    rtt::CliOptions options;
    try{
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
}

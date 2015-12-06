//  =============================================================
//  *************************** TODO! ***************************
//  =============================================================
//  (It's important to have priorities!)
//  1. Interface for stat batteries (work in progress...)
//      1.1. Settings
//      1.2. Executable runner
//      1.3. Reading results from battery output
//      1.4. Result processing and storing
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

#include "rtt/interfacecreator.h"
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
        // I migth want to avoid memory allocation here...
        rtt::batteries::Interface * battery =
                rtt::InterfaceCreator::createBattery(options);
        battery->runTests();
        // Processing not implemented, only prints results
        battery->processStoredResults();
        //rtt::InterfaceCreator::destroyBattery(battery);
    } catch(std::runtime_error ex) {
        std::cout << "[ERROR] " << ex.what() << std::endl;
    } catch(std::bad_alloc ex) {
        std::cout << "[ERROR] Memory allocation failed: " << ex.what() << std::endl;
    }

	return 0;
}

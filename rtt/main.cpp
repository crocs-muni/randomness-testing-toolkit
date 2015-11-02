//  =============================================================
//  *************************** TODO! ***************************
//  =============================================================
//  (It's important to have priorities!)
//  1. Interface for stat batteries (work in progress...)
//      1.1. Settings                               (done in Dieharder , NIST STS)
//      1.2. Executable runner                      (done in Dieharder , NIST STS)
//      1.3. Reading results from battery output    (done in Dieharder)
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

#include "InterfaceCreator.h"
#include "ToolkitOptions.h"
#include "Version.h"

int main (int argc , char * argv[]) {
    std::cout << "Randomness Testing Toolkit start. (build " << GIT_COMMIT_SHORT << ")" << std::endl;

    ToolkitOptions options;
    try{
        options.init(argc , argv);
    }
    catch(std::runtime_error ex) {
        std::cout << "[ERROR] " << ex.what() << std::endl;
        std::cout << options.getUsage();
        return 0;
    }

    // Actual functionality will be here... in time.
    try{
        StatBatteryInterface * battery = InterfaceCreator::createBattery(options.getBattery());
        battery->initBattery(options);
        battery->runTests();
        // Processing not implemented, only prints results
        battery->processStoredResults();
        InterfaceCreator::destroyBattery(battery);
    }
    catch(std::runtime_error ex) {
        std::cout << "[ERROR] " << ex.what() << std::endl;
    }

	return 0;
}

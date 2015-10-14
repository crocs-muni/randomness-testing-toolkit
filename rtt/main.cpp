/*
  TODO (it's important to have priorities!)
  1. Interface for stat batteries (work in progress...)
    1.1. Settings
    1.2. Executable runner
    1.3. Result file processor
  2. Logger
  3. Store results into database
  4. ???
  .
  .
  .
  5. Profit! (and write documentation maybe)
*/

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
        //battery->postprocess();
        InterfaceCreator::destroyBattery(battery);
    }
    catch(std::runtime_error ex) {
        std::cout << "[ERROR] " << ex.what() << std::endl;
    }

	return 0;
}

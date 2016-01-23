//  =============================================================
//  *************************** TODO! ***************************
//  =============================================================
//  (It's important to have priorities!)
//  1. Interface for stat batteries (work in progress...)
//      1.1. Settings                               (NIST STS , Dieharder , TestU01)
//      1.2. Executable runner                      (NIST STS , Dieharder , TestU01)
//      1.3. Reading results from battery output    (NIST STS , Dieharder)
//      1.4. Result processing and storing          (need database for this)
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

#include "rtt/batteries/interfacefactory.h"
#include "rtt/options.h"
#include "rtt/version.h"

//#define TESTING

int main (int argc , char * argv[]) {
#ifdef TESTING
    typedef std::pair<std::string , std::string> tParam;

    std::vector<tParam> params(3);

    tParam par1 {"N" , "1"};
    tParam par2 {"n" , "2000"};
    tParam par3 {"L" , "3000"};
    par1.second = "1000";
    tParam empty;

    if(params.at(0) == empty) {
        params[0] = par1;
    }
    if(params.at(1) == empty) {
        params[1] = par2;
    }
    if(params.at(1) == empty) {
        params[1] = par3;
    }
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

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
 *  2.3. Into database                          (Not until Misc is completed)
 * 3. Miscelaneous
 *  3.1. Better exception handling              (WIP)
 *  3.2. Batteries runtime error handling       (Partially)
 *  3.3. File logger
 *  3.4. Better config file organization        (Ok)
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
#include "rtt/globals.h"
#include "rtt/version.h"
#include "rtt/batteries/dieharder/battery-dh.h"

//#include <map>

//#define TESTING

using namespace rtt;

int main (int argc , char * argv[]) {
#ifdef TESTING
    /* Only temporary code here*/
    try {
        //auto conf = batteries::Configuration::getInstance("config.xml");
        Globals globals;
        //globals.initToolkitSettings(Constants::FILE_TOOLKIT_SETTINGS);
        auto ts = globals.getToolkitSettings();
        std::cout << ts->getRsFileOutFile() << std::endl;
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

//    class Comparable {
//    public:
//        Comparable(int x) : bot(x) , top(x) {}
//        Comparable(int b , int t) : bot(b) , top(t) {
//            if(t < b)
//                raiseBugException("bad comparable creation");
//        }

//        bool operator<(const Comparable & cmp) const {
//            return cmp.top < this->bot;
//        }

//    private:
//        int bot;
//        int top;
//    };

//    std::map<Comparable , std::string> mymap;
//    Comparable a(1,3);
//    Comparable b(4,6);
//    Comparable c(7,9);

//    mymap[a] = "1-3";
//    mymap[b] = "4-6";
//    mymap[c] = "7-9";
//    /* Use find instead */
//    std::cout << mymap[2] << std::endl;
//    std::cout << mymap[6] << std::endl;
//    std::cout << mymap[7] << std::endl;

#else
    std::cout << "Randomness Testing Toolkit start. (build " << GIT_COMMIT_SHORT << ")" << std::endl;
    std::cout << "Start: " << Utils::getTime() << std::endl;

    if(argc == 1 || (argc == 2 && strcmp(argv[1] , "-h") == 0))
        std::cout << CliOptions::getUsage() << std::endl;

    /* Actual functionality will be here... in time. */
    try {
        /* Initialization of run settings from config files */
        Globals globals;
        globals.initCliOptions(argc , argv);
        globals.initBatteriesConfiguration(globals.getCliOptions()->getInputCfgPath());
        globals.initToolkitSettings(Constants::FILE_TOOLKIT_SETTINGS);

        /* Creation and execution of battery */
        auto battery = batteries::IBattery::getInstance(globals);
        //auto battery = batteries::dieharder::Battery::getInstance(globals);
        /* Executing tests as set in settings */
        battery->runTests();
        /* Processing and storing of results of the run */
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

#ifndef STATBATTERYINTERFACE_H
#define STATBATTERYINTERFACE_H

#include "ToolkitOptions.h"

class StatBatteryInterface {
public:
    virtual ~StatBatteryInterface() {}

    virtual void initBattery(const ToolkitOptions & options) = 0;

    virtual void runTests() = 0;
};

#endif //STATBATTERYINTERFACE_H

#ifndef INTERFACECREATOR_H
#define INTERFACECREATOR_H

#include "ToolkitConstants.h"

#include "StatBatteryInterface.h"
#include "DieharderBattery.h"

class InterfaceCreator {
public:
    static StatBatteryInterface * createBattery(int batteryConst);

    static void destroyBattery(StatBatteryInterface * battery);
};

#endif //INTERFACECREATOR_H

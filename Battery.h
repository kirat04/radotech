#ifndef BATTERY_H
#define BATTERY_H

#include "SystemManager.h"
#include "UserInterface.h"
#include "DeviceManager.h"

class Battery {
public:
    int getCurrentLevel();
    void consume(int amount);
    bool isLowPower();
    void handleLowPower();
    void initiateGracefulShutdown();

private:
    SystemManager* systemManager;
    UserInterface* userInterface;
    DeviceManager* deviceManager;
};

#endif // BATTERY_H

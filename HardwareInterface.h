#ifndef HARDWAREINTERFACE_H
#define HARDWAREINTERFACE_H

#include "DeviceManager.h"

class HardwareInterface {
public:
    void initializeDevice();
    void shutdownDevice();
    void readSensorData();
    void sendCommand(const std::string& command);

private:
    DeviceManager* deviceManager;
};

#endif // HARDWAREINTERFACE_H

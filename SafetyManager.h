#ifndef SAFETYMANAGER_H
#define SAFETYMANAGER_H

#include "Application.h"
#include "MeasurementManager.h"
#include "DeviceManager.h"

class SafetyManager {
public:
    void performSafetyCheck();
    void handleEmergency();
    void logError(const std::string& error);
    void initiateEmergencyShutdown();

private:
    Application* application;
    MeasurementManager* measurementManager;
    DeviceManager* deviceManager;
};

#endif // SAFETYMANAGER_H

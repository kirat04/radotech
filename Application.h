#ifndef APPLICATION_H
#define APPLICATION_H

#include "UserManager.h"
#include "DeviceManager.h"
#include "MeasurementManager.h"
#include "DataProcessor.h"

class Application {
public:
    void initializeSystem();
    void startSession();
    void endSession();
    void handleShutdown();

private:
    UserManager* userManager;
    DeviceManager* deviceManager;
    MeasurementManager* measurementManager;
    DataProcessor* dataProcessor;
};

#endif // APPLICATION_H

#ifndef MEASUREMENTMANAGER_H
#define MEASUREMENTMANAGER_H

#include "DeviceManager.h"
#include "UserInterface.h"
#include "DataProcessor.h"

class MeasurementManager {
public:
    void startMeasurementSession();
    void captureMeasurement(const std::string& point);
    void validateMeasurement(const std::string& data);
    void retryMeasurement();

private:
    DeviceManager* deviceManager;
    UserInterface* userInterface;
    DataProcessor* dataProcessor;
};

#endif // MEASUREMENTMANAGER_H

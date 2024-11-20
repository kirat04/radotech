#ifndef DATAPROCESSOR_H
#define DATAPROCESSOR_H

#include "StorageManager.h"
#include "UserInterface.h"

class DataProcessor {
public:
    void processRawData(const std::string& data);
    void generateMetrics(const std::string& data);
    void createVisualization(const std::string& data);
    void prepareRecommendations(const std::string& metrics);

private:
    StorageManager* storageManager;
    UserInterface* userInterface;
};

#endif // DATAPROCESSOR_H

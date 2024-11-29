#include "measurementManager.h"


void MeasurementManager::captureInitMeasurement() {
   currMeasure = lowerWindow + (rand() % (upperWindow - lowerWindow + 1));
   measurements.push_back(currMeasure);
   qInfo("%d", currMeasure);
}

void MeasurementManager::captureMeasurement() {
   int newMeasure;
   do {
       newMeasure = currMeasure - 10 + (rand() % ((currMeasure + 10) - (currMeasure - 10) + 1));
   } while (!validateMeasurement(newMeasure));

   currMeasure = newMeasure;
   measurements.push_back(currMeasure);
   qInfo("%d", currMeasure);
}

bool MeasurementManager::validateMeasurement(int measure) {
   return (measure >= lowerWindow && measure <= upperWindow);
}

int MeasurementManager::getMeasurement() {
   return currMeasure;
}

QVector<int> MeasurementManager::getAllMeasurements() {
   return measurements;
}

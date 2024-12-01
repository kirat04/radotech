#include "measurementManager.h"

MeasurementManager::MeasurementManager(int lower, int upper)
    : upperWindow(upper), lowerWindow(lower), currMeasure(0) {}



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

double MeasurementManager::calculateAverage() const {
    if (measurements.isEmpty()) return 0.0;
    double sum = 0.0;
    for (int measure : measurements) {
        sum += measure;
    }
    return sum / measurements.size();
}

void MeasurementManager::setMeasurementRange(int lower, int upper) {
    lowerWindow = lower;
    upperWindow = upper;
}

QVector<int> MeasurementManager::getMeasurementsAbove(int threshold) const {
    QVector<int> result;
    for (int measure : measurements) {
        if (measure > threshold) {
            result.push_back(measure);
        }
    }
    return result;
}

QVector<int> MeasurementManager::getMeasurementsBelow(int threshold) const {
    QVector<int> result;
    for (int measure : measurements) {
        if (measure < threshold) {
            result.push_back(measure);
        }
    }
    return result;
}

QVector<int> MeasurementManager::getMeasurementsInRange(int lower, int upper) const {
    QVector<int> result;
    for (int measure : measurements) {
        if (measure >= lower && measure <= upper) {
            result.push_back(measure);
        }
    }
    return result;
}

void MeasurementManager::resetMeasurements() {
    measurements.clear();
    currMeasure = 0;
    qInfo("Measurements reset.");
}








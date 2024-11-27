#include "measurementManager.h"

void MeasurementManager::captureMeasurement()
{
    int currMeasure = rand() % (upperWindow + lowerWindow - 1) + lowerWindow;
    qInfo("%d", currMeasure);
}

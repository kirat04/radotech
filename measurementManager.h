#ifndef MEASUREMENTMANAGER_H
#define MEASUREMENTMANAGER_H



#include "random"
#include "QObject"



class MeasurementManager
{
public slots:
    void startMeasurementSession();
    void captureMeasurement();
    void validateMeasurement();
    void retryMeasurement();



private:
    int upperWindow = 160;
    int lowerWindow = 5;

};

#endif // MEASUREMENTMANAGER_H

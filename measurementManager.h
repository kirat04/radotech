#ifndef MEASUREMENTMANAGER_H
#define MEASUREMENTMANAGER_H



#include "random"
#include "QObject"
#include <QVector>

class MeasurementManager
{
public slots:
   void captureInitMeasurement();
   void captureMeasurement();
   bool validateMeasurement(int measure);

public:
   int getMeasurement();
   QVector<int> getAllMeasurements();

private:
   int upperWindow = 160;
   int lowerWindow = 5;
   int currMeasure;
   QVector<int> measurements;
};

#endif // MEASUREMENTMANAGER_H

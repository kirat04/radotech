#ifndef MEASUREMENTMANAGER_H
#define MEASUREMENTMANAGER_H

#include "random"
#include "QObject"
#include <QVector>
#include <QObject>
#include <QJsonArray>
#include "usermanager.h"
#include "storageManager.h"

class MeasurementManager
{
public slots:
   void captureInitMeasurement();
   void captureMeasurement();
   bool validateMeasurement(int measure);

public:
   MeasurementManager(int lower, int upper);
   int getMeasurement();
   QVector<int> getAllMeasurements();
   double calculateAverage() const;
   void setMeasurementRange(int lower, int upper);
   QVector<int> getMeasurementsAbove(int threshold) const;
   QVector<int> getMeasurementsBelow(int threshold) const;
   QVector<int> getMeasurementsInRange(int lower, int upper) const;
   QList<QJsonObject> getStoredMeasurements();
   void resetMeasurements();
   void storeMeasurements();

private:
   int upperWindow = 160;
   int lowerWindow = 5;
   int currMeasure;
   QVector<int> measurements;
   StorageManager* storageManager;
};

#endif // MEASUREMENTMANAGER_H

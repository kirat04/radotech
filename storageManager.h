#ifndef STORAGEMANAGER_H
#define STORAGEMANAGER_H

#include <QString>
#include <QFile>
#include <QJsonDocument>
#include <QDebug>
#include <QDir>
#include "userprofile.h"

class StorageManager {
public:
    static StorageManager& getInstance() { static StorageManager instance; return instance; }
    void saveMeasurement(const QJsonObject &measurement, const QString &fileName);
    void saveData(const QJsonObject &data, const QString &fileName);
    void saveUserProfile(const UserProfile &user, const QString &fileName);

    QJsonObject loadMeasurement(const QString &fileName) const;
    QJsonObject loadData(const QString &fileName) const;
    UserProfile loadUserProfile(const QString &fileName) const;
    QList<QJsonObject> loadAllMeasurements();

private:
    StorageManager() {} 
    StorageManager(const StorageManager&) = delete;
    StorageManager& operator=(const StorageManager&) = delete;
};

#endif // STORAGEMANAGER_H

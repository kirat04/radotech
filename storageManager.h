#ifndef STORAGEMANAGER_H
#define STORAGEMANAGER_H

#include <QString>
#include <QFile>
#include <QJsonDocument>
#include <QDebug>
#include "userprofile.h"

class StorageManager {
public:
    void saveMeasurement(const QJsonObject &measurement, const QString &fileName);
    void saveData(const QJsonObject &data, const QString &fileName);
    void saveUserProfile(const UserProfile &user, const QString &fileName);
};

#endif // STORAGEMANAGER_H

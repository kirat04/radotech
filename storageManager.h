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


    QJsonObject loadMeasurement(const QString &fileName) const;
    QJsonObject loadData(const QString &fileName) const;
    UserProfile loadUserProfile(const QString &fileName) const;
};

#endif // STORAGEMANAGER_H

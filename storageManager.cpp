#include "storageManager.h"

void StorageManager::saveMeasurement(const QJsonObject &measurement, const QString &fileName) {
    QJsonDocument doc(measurement);
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly)) {
        qDebug() << "Could not open" << fileName << "for writing";
        return;
    }
    file.write(doc.toJson());
    file.close();
    qDebug() << "Measurement saved to" << fileName;
}

void StorageManager::saveData(const QJsonObject &data, const QString &fileName) {
    QJsonDocument doc(data);
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly)) {
        qDebug() << "Could not open" << fileName << "for writing";
        return;
    }
    file.write(doc.toJson());
    file.close();
    qDebug() << "Data saved to" << fileName;
}

void StorageManager::saveUserProfile(const UserProfile &user, const QString &fileName) {
    QJsonObject userJson = user.toJson(); // Convert the user object to JSON
    QJsonDocument doc(userJson);
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly)) {
        qDebug() << "Could not open" << fileName << "for writing";
        return;
    }
    file.write(doc.toJson());
    file.close();
    qDebug() << "User profile saved to" << fileName;
}

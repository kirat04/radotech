#include "storageManager.h"

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
    QJsonObject userJson = user.toJson();
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


QJsonObject StorageManager::loadMeasurement(const QString &fileName) const {
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Could not open" << fileName << "for reading";
        return QJsonObject();
    }
    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    file.close();
    return doc.object();
}

QJsonObject StorageManager::loadData(const QString &fileName) const {
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Could not open" << fileName << "for reading";
        return QJsonObject();
    }
    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    file.close();
    return doc.object();
}

UserProfile StorageManager::loadUserProfile(const QString &fileName) const {
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Could not open" << fileName << "for reading";
        return UserProfile();
    }
    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    file.close();

    UserProfile user;
    user.fromJson(doc.object());
    return user;
}

void StorageManager::saveMeasurement(const QJsonObject &measurement, const QString &fileName) {
    QDir measurementDir("measurements");
    if (!measurementDir.exists()) {
        measurementDir.mkpath(".");
    }

    QString fullPath = measurementDir.filePath(fileName);
    QJsonDocument doc(measurement);

    QFile file(fullPath);
    if (!file.open(QIODevice::WriteOnly)) {
        qDebug() << "Could not open" << fullPath << "for writing";
        return;
    }

    file.write(doc.toJson(QJsonDocument::Indented));
    file.close();
    qDebug() << "Measurement saved to" << fullPath;
}

QList<QJsonObject> StorageManager::loadAllMeasurements() {
    QList<QJsonObject> measurements;
    QDir measurementDir("measurements");

    if (!measurementDir.exists()) return measurements;

    QStringList fileList = measurementDir.entryList(QStringList() << "*.json", QDir::Files);

    for (const QString &filename : fileList) {
        QJsonObject measurement = loadMeasurement(measurementDir.filePath(filename));
        if (!measurement.isEmpty()) {
            measurements.append(measurement);
        }
    }

    return measurements;
}

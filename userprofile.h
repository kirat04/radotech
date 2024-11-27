#ifndef USERPROFILE_H
#define USERPROFILE_H

#include <QString>
#include <QDate>
#include <QJsonObject>

class UserProfile {
public:
    int cuser;
    QString firstName;
    QString lastName;
    QString gender;
    double weight;
    double height;
    QDate dateOfBirth;
    QString country;
    QString phone;
    QString email;
    QString password;
    QString confirmPass;

    QJsonObject toJson() const;
    void fromJson(const QJsonObject &json);
    int getcuser() const { return cuser; }
    QString getFullName() const { return firstName + " " + lastName; }
};

#endif

#include "userprofile.h"

QJsonObject UserProfile::toJson() const {
    QJsonObject json;
    json["cuser"] = cuser;
    json["firstName"] = firstName;
    json["lastName"] = lastName;
    json["gender"]= gender;
    json["weight"] = weight;
    json["height"] = height;
    json["dateOfBirth"] = dateOfBirth.toString(Qt::ISODate);
    json["country"] = country;
    json["phone"] = phone;
    json["email"] = email;
    json["password"] = password;
    json["confirmPass"] = confirmPass;
    return json;
}

void UserProfile::fromJson(const QJsonObject &json) {
    cuser = json["cuser"].toInt();
    firstName = json["firstName"].toString();
    lastName = json["lastName"].toString();
    gender = json["gender"].toString();
    weight = json["weight"].toDouble();
    height = json["height"].toDouble();
    dateOfBirth = QDate::fromString(json["dateOfBirth"].toString(), Qt::ISODate);
    country = json["country"].toString();
    phone = json["phone"].toString();
    email = json["email"].toString();
    password = json["password"].toString();
    confirmPass = json["confirmPass"].toString();
}

#include "usermanager.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QDebug>
#include <QMessageBox>

UserManager& UserManager::getInstance() {
    static UserManager instance;
    return instance;
}

UserManager::UserManager() {
    loadProfiles();
}

void UserManager::addProfile(const UserProfile& profile) {
    if (profiles.size() < MAX_PROFILES) {
        // Ensure only one current user at a time
        for (auto& existingProfile : profiles) {
            existingProfile.cuser = 0;
        }
        UserProfile newProfile = profile;
        newProfile.cuser = 1;
        profiles.append(newProfile);
        saveProfiles();
    }
}

bool UserManager::removeProfile(int index) {
    if (index >= 0 && index < profiles.size()) {
        if (profiles[index].cuser == 1 && profiles.size() == 1) {
            // Cannot remove last profile
            return false;
        }
        if (profiles[index].cuser != 1) {
            profiles.remove(index);
            saveProfiles();
            return true;
        }
    }
    return false;
}

bool UserManager::editProfile(int index, const UserProfile& updatedProfile) {
    if (index >= 0 && index < profiles.size()) {
        int currentUserStatus = profiles[index].cuser;
        profiles[index] = updatedProfile;
        profiles[index].cuser = currentUserStatus;
        saveProfiles();
        return true;
    }
    return false;
}

UserProfile* UserManager::getCurrentUser() {
    for (auto& profile : profiles) {
        if (profile.cuser == 1) {
            return &profile;
        }
    }
    return nullptr;
}

void UserManager::setCurrentUser(int index) {
    if (index >= 0 && index < profiles.size()) {
        // Clear current user
        for (auto& profile : profiles) {
            profile.cuser = 0;
        }
        // Set new current user
        profiles[index].cuser = 1;
        saveProfiles();
    }
}

void UserManager::clearCurrentUser() {
    for (auto& profile : profiles) {
        profile.cuser = 0;
    }
    saveProfiles();
}

QVector<UserProfile>& UserManager::getAllProfiles() {
    return profiles;
}

int UserManager::getProfileCount() const {
    return profiles.size();
}

UserProfile* UserManager::getProfileByIndex(int index) {
    if (index >= 0 && index < profiles.size()) {
        return &profiles[index];
    }
    return nullptr;
}

void UserManager::loadProfiles() {
    QFile file("profiles.json");
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Could not open profiles file";
        return;
    }

    QByteArray saveData = file.readAll();
    QJsonDocument doc(QJsonDocument::fromJson(saveData));
    QJsonArray array = doc.array();

    profiles.clear();
    for (const QJsonValue &value : array) {
        QJsonObject obj = value.toObject();
        UserProfile profile;
        profile.fromJson(obj);
        profiles.append(profile);
    }
}

void UserManager::saveProfiles() {
    QJsonArray array;
    for (const UserProfile &profile : profiles) {
        array.append(profile.toJson());
    }

    QJsonDocument doc(array);
    QFile file("profiles.json");
    if (!file.open(QIODevice::WriteOnly)) {
        qDebug() << "Could not open profiles file for writing";
        return;
    }

    file.write(doc.toJson());
}

bool UserManager::hasCurrentUser() const {
    for (const auto& profile : profiles) {
        if (profile.cuser == 1) {
            return true;
        }
    }
    return false;
}

bool UserManager::isMaxProfileReached() const {
    return profiles.size() >= MAX_PROFILES;
}

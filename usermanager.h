#ifndef USERMANAGER_H
#define USERMANAGER_H

#include <QVector>
#include <QString>
#include "userprofile.h"

class UserManager {
public:
    static UserManager& getInstance();

    // User Profile Management
    void addProfile(const UserProfile& profile);
    bool removeProfile(int index);
    bool editProfile(int index, const UserProfile& updatedProfile);

    // Current User Management
    UserProfile* getCurrentUser();
    void setCurrentUser(int index);
    void clearCurrentUser();



    // Profile List Queries
    QVector<UserProfile>& getAllProfiles();
    int getProfileCount() const;
    UserProfile* getProfileByIndex(int index);

    // Persistence Methods
    void loadProfiles();
    void saveProfiles();

    // Utility Methods
    bool hasCurrentUser() const;
    bool isMaxProfileReached() const;

private:
    UserManager();
    UserManager(const UserManager&) = delete; 
    UserManager& operator=(const UserManager&) = delete; 

    static const int MAX_PROFILES = 5;
    QVector<UserProfile> profiles;
};

#endif // USERMANAGER_H

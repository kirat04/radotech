#ifndef PROFILEFORM_H
#define PROFILEFORM_H

#include <QWidget>
#include <QLineEdit>
#include <QDateEdit>
#include <QRadioButton>
#include "userprofile.h"
#include "usermanager.h"
#include <QPushButton>

class ProfileForm : public QWidget {
    Q_OBJECT

public:
    ProfileForm(QWidget *parent = nullptr);
    UserProfile getProfile() const;
    bool validateProfile();
    void setProfile(const UserProfile &profile);
    void clear();

signals:
    void profileCreate(UserProfile newProfile);
    void goBack();

private:
    QLineEdit *firstNameEdit;
    QLineEdit *lastNameEdit;
    QLineEdit *weightEdit;
    QLineEdit *heightEdit;
    QDateEdit *dobEdit;
    QLineEdit *countryEdit;
    QLineEdit *phoneEdit;
    QLineEdit *emailEdit;
    QLineEdit *passwordEdit;
    QLineEdit *confirmPassEdit;
    QRadioButton *maleRadio;
    QRadioButton *femaleRadio;
};

#endif

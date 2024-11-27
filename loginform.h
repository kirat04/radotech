#ifndef LOGINFORM_H
#define LOGINFORM_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include "userprofile.h"

class LoginForm : public QWidget {
    Q_OBJECT

public:
    explicit LoginForm(const UserProfile &profile, QWidget *parent = nullptr);
    bool validateLogin() const;

signals:
    void loginSuccessful();
    void backClicked();

private:
    QLineEdit *emailEdit;
    QLineEdit *passwordEdit;
    QPushButton *enterButton;
    QPushButton *backButton;
    const UserProfile &profile;
};

#endif // LOGINFORM_H

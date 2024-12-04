#include "loginform.h"
#include <QFormLayout>
#include <QMessageBox>
#include  <QProgressBar>
LoginForm::LoginForm(const UserProfile &prof, QWidget *parent)
    : QWidget(parent), profile(prof) {

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    QFormLayout *formLayout = new QFormLayout;

    // Create and setup email field
    emailEdit = new QLineEdit(this);
    emailEdit->setText(profile.email);
    emailEdit->setReadOnly(true);

    // Create and setup password field
    passwordEdit = new QLineEdit(this);
    passwordEdit->setEchoMode(QLineEdit::Password);

    // Add fields to form layout
    formLayout->addRow("Email:", emailEdit);
    formLayout->addRow("Password:", passwordEdit);

    // Create and setup buttons
    QHBoxLayout *buttonLayout = new QHBoxLayout;
    backButton = new QPushButton("Back", this);
    enterButton = new QPushButton("Enter", this);

    buttonLayout->addWidget(backButton);
    buttonLayout->addWidget(enterButton);

    // Add layouts to main layout
    mainLayout->addLayout(formLayout);
    mainLayout->addLayout(buttonLayout);

    // Connect signals
    connect(enterButton, &QPushButton::clicked, [this]() {
        if (validateLogin()) {
            emit loginSuccessful();
        }
    });

    connect(backButton, &QPushButton::clicked, [this]() {
        emit backClicked();
    });

    // Set focus to password field
    passwordEdit->setFocus();
}

bool LoginForm::validateLogin() const {
    if (passwordEdit->text() != profile.password) {
        QMessageBox::warning(
            const_cast<LoginForm*>(this),
            "Error",
            "Incorrect password!"
        );
        return false;
    }
    return true;
}

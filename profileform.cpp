#include "profileform.h"
#include <QVBoxLayout>
#include <QFormLayout>
#include <QLabel>
#include <QButtonGroup>
#include <QMessageBox>
#include  <QProgressBar>

ProfileForm::ProfileForm(QWidget *parent) : QWidget(parent) {


    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    QFormLayout *formLayout = new QFormLayout;

    firstNameEdit = new QLineEdit(this);
    lastNameEdit = new QLineEdit(this);
    weightEdit = new QLineEdit(this);
    heightEdit = new QLineEdit(this);
    dobEdit = new QDateEdit(this);
    countryEdit = new QLineEdit(this);
    phoneEdit = new QLineEdit(this);
    emailEdit = new QLineEdit(this);
    passwordEdit = new QLineEdit(this);
    confirmPassEdit = new QLineEdit(this);

    QWidget *genderWidget = new QWidget(this);
    QHBoxLayout *genderLayout = new QHBoxLayout(genderWidget);
    maleRadio = new QRadioButton("Male", this);
    femaleRadio = new QRadioButton("Female", this);
    QButtonGroup *genderGroup = new QButtonGroup(this);
    genderGroup->addButton(maleRadio);
    genderGroup->addButton(femaleRadio);
    genderLayout->addWidget(maleRadio);
    genderLayout->addWidget(femaleRadio);

    passwordEdit->setEchoMode(QLineEdit::Password);
    confirmPassEdit->setEchoMode(QLineEdit::Password);
    dobEdit->setDisplayFormat("dd/MM/yyyy");

    formLayout->addRow("First Name:", firstNameEdit);
    formLayout->addRow("Gender:", genderWidget);
    formLayout->addRow("Last Name:", lastNameEdit);
    formLayout->addRow("Weight:", weightEdit);
    formLayout->addRow("Height:", heightEdit);
    formLayout->addRow("Date of Birth:", dobEdit);
    formLayout->addRow("Country:", countryEdit);
    formLayout->addRow("Phone:", phoneEdit);
    formLayout->addRow("Email:", emailEdit);
    formLayout->addRow("Password:", passwordEdit);
    formLayout->addRow("Confirm Password:", confirmPassEdit);

    mainLayout->addLayout(formLayout);
    clear();
}

UserProfile ProfileForm::getProfile() const {
    UserProfile profile;
    if(maleRadio->isChecked()){
        profile.gender = "M";
    } else if (femaleRadio->isChecked()){
        profile.gender = "F";
    }
    profile.firstName = firstNameEdit->text();
    profile.lastName = lastNameEdit->text();
    profile.weight = weightEdit->text().toDouble();
    profile.height = heightEdit->text().toDouble();
    profile.dateOfBirth = dobEdit->date();
    profile.country = countryEdit->text();
    profile.phone = phoneEdit->text();
    profile.email = emailEdit->text();
    profile.password = passwordEdit->text();
    profile.confirmPass = confirmPassEdit->text();
    return profile;
}

void ProfileForm::setProfile(const UserProfile &profile) {
    if(profile.gender.toStdString() == "M"){
        maleRadio->setChecked(true);
    } else if (profile.gender.toStdString() == "F"){
        femaleRadio->setChecked(true);
    }
    firstNameEdit->setText(profile.firstName);
    lastNameEdit->setText(profile.lastName);
    weightEdit->setText(QString::number(profile.weight));
    heightEdit->setText(QString::number(profile.height));
    dobEdit->setDate(profile.dateOfBirth);
    countryEdit->setText(profile.country);
    phoneEdit->setText(profile.phone);
    emailEdit->setText(profile.email);
    passwordEdit->setText(profile.password);
    confirmPassEdit->setText(profile.password);
}

bool ProfileForm::validateProfile() {
    // Validate first name
    if (firstNameEdit->text().isEmpty()) {
        QMessageBox::warning(this, "Error", "Please enter first name!");
        return false;
    }

    // Validate last name
    if (lastNameEdit->text().isEmpty()) {
        QMessageBox::warning(this, "Error", "Please enter last name!");
        return false;
    }

    // Validate gender
    if (!maleRadio->isChecked() && !femaleRadio->isChecked()) {
        QMessageBox::warning(this, "Error", "Please select a gender!");
        return false;
    }

    // Validate email
    QString email = emailEdit->text();
    if (email.isEmpty() || !email.contains("@") || !email.contains(".")) {
        QMessageBox::warning(this, "Error", "Please enter a valid email address!");
        return false;
    }

    // Validate password
    QString password = passwordEdit->text();
    QString confirmPass = confirmPassEdit->text();
    if (password.isEmpty()) {
        QMessageBox::warning(this, "Error", "Please enter a password!");
        return false;
    }
    if (password != confirmPass) {
        QMessageBox::warning(this, "Error", "Passwords do not match!");
        return false;
    }

    // Validate weight and height (optional, but ensure they are numeric if entered)
    bool weightOk, heightOk;
    weightEdit->text().toDouble(&weightOk);
    heightEdit->text().toDouble(&heightOk);
    if (!weightEdit->text().isEmpty() && !weightOk) {
        QMessageBox::warning(this, "Error", "Invalid weight!");
        return false;
    }
    if (!heightEdit->text().isEmpty() && !heightOk) {
        QMessageBox::warning(this, "Error", "Invalid height!");
        return false;
    }
    return true;
}

void ProfileForm::clear() {
    firstNameEdit->clear();
    lastNameEdit->clear();
    weightEdit->clear();
    heightEdit->clear();
    dobEdit->setDate(QDate::currentDate());
    countryEdit->clear();
    phoneEdit->clear();
    emailEdit->clear();
    passwordEdit->clear();
    confirmPassEdit->clear();
    maleRadio->setChecked(false);
    femaleRadio->setChecked(false);
}

#include "editform.h"
#include <QMessageBox>

EditForm::EditForm(QVector<UserProfile> &profiles, int index, QWidget *parent)
    : QWidget(parent), profilesEdit(profiles), profileIndex(index) {

    QVBoxLayout *layout = new QVBoxLayout(this);

    editForm = new ProfileForm(this);
    editForm->setProfile(profiles[index]);

    QPushButton *saveButton = new QPushButton("Save Changes", this);
    QPushButton *backButton = new QPushButton("Back", this);
    QPushButton *deleteButton = new QPushButton("Delete Profile", this);
    deleteButton->setStyleSheet("background-color: #ff4444; color: white;");

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(backButton);
    buttonLayout->addWidget(deleteButton);
    buttonLayout->addWidget(saveButton);

    layout->addWidget(editForm);
    layout->addLayout(buttonLayout);

    connect(saveButton, &QPushButton::clicked, [this]() {
        int temp_cuser = profilesEdit[profileIndex].cuser;
        profilesEdit[profileIndex] = editForm->getProfile();
        profilesEdit[profileIndex].cuser = temp_cuser;
        emit profileEdited();
    });

    connect(deleteButton, &QPushButton::clicked, [this]() {
        if(profilesEdit.size() == 1 && profilesEdit[profileIndex].cuser == 1){
            QMessageBox::StandardButton reply;
            reply = QMessageBox::question(this, "Confirm Delete",
                "This is the last profile in the list, are you sure you want to delete this profile?",
                QMessageBox::Yes|QMessageBox::No);

            if (reply == QMessageBox::Yes) {
                profilesEdit.remove(profileIndex);
                emit lastprofileDeleted();
            }
        } else if(profilesEdit[profileIndex].cuser == 1){
            QMessageBox::warning(this, "Error", "This is the current user profile, switch to other profiles to delete");
        } else {
            QMessageBox::StandardButton reply;
            reply = QMessageBox::question(this, "Confirm Delete",
                "Are you sure you want to delete this profile?",
                QMessageBox::Yes|QMessageBox::No);

            if (reply == QMessageBox::Yes) {
                profilesEdit.remove(profileIndex);
                emit profileDeleted();
            }
        }
    });

    connect(backButton, &QPushButton::clicked, this, &EditForm::profileEdited);
}

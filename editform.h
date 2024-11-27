#ifndef EDITFORM_H
#define EDITFORM_H

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include "userprofile.h"
#include "profileform.h"

class EditForm : public QWidget {
    Q_OBJECT
public:
    EditForm(QVector<UserProfile> &profiles, int index, QWidget *parent = nullptr);

signals:
    void profileEdited();
    void profileDeleted();
    void lastprofileDeleted();

private:
    QVector<UserProfile> &profilesEdit;
    int profileIndex;
    ProfileForm *editForm;
};
#endif

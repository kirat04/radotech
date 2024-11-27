#ifndef HOMESCREEN_H
#define HOMESCREEN_H

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include "userprofile.h"

class HomeScreen : public QWidget {
    Q_OBJECT

public:
    HomeScreen(const QVector<UserProfile> &profiles, QWidget *parent = nullptr);
    void updateProfileList(const QVector<UserProfile> &profiles);

signals:
    void profileSelected(int index);
    void swapProfileClicked(int index);
    void LogOutProfileClicked(int index);
    void measureNowClicked();
    void historyClicked();
    void createProfClicked();

private:
    QVBoxLayout *mainLayout;
};

#endif


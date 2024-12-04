#include "homescreen.h"
#include <QLabel>
#include <QGridLayout>


HomeScreen::HomeScreen(const QVector<UserProfile> &profiles, QWidget *parent)
    : QWidget(parent) {

   battery = new QProgressBar(this);
    battery->setValue(100);

    mainLayout = new QVBoxLayout(this);

    for (int i = 0; i < profiles.size(); ++i) {
        if(profiles[i].cuser == 1){
            QLabel *nameLabel = new QLabel("Name: " + profiles[i].getFullName(), this);
            nameLabel->setAlignment(Qt::AlignCenter);
            mainLayout->addWidget(nameLabel);
        }
    }

    QPushButton *measureNowBtn = new QPushButton("Measure Now", this);
    QPushButton *historyBtn = new QPushButton("History", this);
QPushButton *specialistBtn = new QPushButton("Specialist Reccomendation", this);

    connect(measureNowBtn, &QPushButton::clicked, this, &HomeScreen::measureNowClicked);
    connect(historyBtn, &QPushButton::clicked, this, &HomeScreen::historyClicked);
    connect(specialistBtn, &QPushButton::clicked,  this,  &HomeScreen::specialistClicked);

    mainLayout->addWidget(measureNowBtn);
    mainLayout->addWidget(historyBtn);
    mainLayout->addWidget(specialistBtn);


    updateProfileList(profiles);

}

void HomeScreen::updateProfileList(const QVector<UserProfile> &profiles) {
    QWidget *profileWidget = new QWidget(this);
    QGridLayout *gridLayout = new QGridLayout(profileWidget);

    for (int i = 0; i < profiles.size(); ++i) {
        QLabel *nameLabel = new QLabel(profiles[i].getFullName(), this);
        QPushButton *editBtn = new QPushButton("Edit", this);

        gridLayout->addWidget(nameLabel, i, 0);
        gridLayout->addWidget(editBtn, i, 1);
        if(profiles[i].cuser == 0){
            QPushButton *LogInBtn = new QPushButton("Log In", this);
            gridLayout->addWidget(LogInBtn, i, 2);

            connect(LogInBtn, &QPushButton::clicked, this, [this, i]() {
                emit swapProfileClicked(i);
            });
        } else {
            QPushButton *LogOutBtn = new QPushButton("Log Out", this);
            gridLayout->addWidget(LogOutBtn, i, 2);

            connect(LogOutBtn, &QPushButton::clicked, this, [this, i]() {
                emit LogOutProfileClicked(i);
            });
        }

        connect(editBtn, &QPushButton::clicked, this, [this, i]() {
            emit profileSelected(i);
        });
    }

    QPushButton *createBtn = new QPushButton("Create", this);
    gridLayout->addWidget(createBtn, profiles.size(), 0, 1, 3);

    connect(createBtn, &QPushButton::clicked, this, &HomeScreen::createProfClicked);

    mainLayout->addWidget(profileWidget);
}
void HomeScreen::setBattery(int amount){

    battery->setValue(amount);
}

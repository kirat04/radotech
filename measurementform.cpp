#include "measurementform.h"
#include <QPushButton>
#include <QGridLayout>
#include <QLabel>
#include<QPixmap>
#include <QDir>


//Need to add innstructions
MeasurementForm::MeasurementForm(QWidget *parent)
    : QWidget(parent) {
    stepNumber = 0;
    measurementManager = new MeasurementManager();
    imagePaths.push_back("../radotech/images/testt.jpeg");
    imagePaths.push_back("../radotech/images/point1.png");
    imagePaths.push_back("../radotech/images/point2.png");
    imagePaths.push_back("../radotech/images/point3.png");
    imagePaths.push_back("../radotech/images/point4.png");
    imagePaths.push_back("../radotech/images/point5.png");
    imagePaths.push_back("../radotech/images/point6.png");
    imagePaths.push_back("../radotech/images/point7.png");
    imagePaths.push_back("../radotech/images/point8.png");
    imagePaths.push_back("../radotech/images/point9.png");
    imagePaths.push_back("../radotech/images/point10.png");
    imagePaths.push_back("../radotech/images/point11.png");
    imagePaths.push_back("../radotech/images/point12.png");




    mainLayout = new QVBoxLayout(this);
    QHBoxLayout* picLayout = new QHBoxLayout();

    picture = new QLabel();
    picture->setText("Please press the device to the displayed point to get a reading.\nWhen done, press 'Next' to display the next point.\nPress 'Next' to start");

    picLayout->addWidget(picture);
    QHBoxLayout* btnLayout = new QHBoxLayout();

    QPushButton *nextBtn = new QPushButton("Next", this);
    QPushButton *exitBtn = new QPushButton("Exit", this);
mainLayout->addLayout(picLayout);
mainLayout->addLayout(btnLayout);

    connect(nextBtn,&QPushButton::clicked,this,&MeasurementForm::nextClicked);
    connect(exitBtn,&QPushButton::clicked,this,&MeasurementForm::exitClicked);

    btnLayout->addWidget(nextBtn);
     btnLayout->addWidget(exitBtn);
}

//need a way to save the measurements
void MeasurementForm::handleNext(){
    stepNumber++;
    if(stepNumber == 1){
measurementManager->captureInitMeasurement();
picture->clear();
QPixmap image = QPixmap(imagePaths[stepNumber]);
picture->setPixmap(image);
    }

    else if(stepNumber > 12){
        picture->clear();
    picture->setText("Test Completed");

    }
    else{
        measurementManager->captureMeasurement();
        picture->clear();
    QPixmap image = QPixmap(imagePaths[stepNumber]);
    picture->setPixmap(image);
    }

}

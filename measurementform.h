#ifndef MEASUREMENTFORM_H
#define MEASUREMENTFORM_H

#include <QObject>
#include <QWidget>
#include "userprofile.h"
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include<QPixmap>
#include <QDir>
#include <vector>
#include  <QString>
#include "measurementManager.h"
#include "healthmetricVisualization.h"
#include  <QProgressBar>

class MeasurementForm : public QWidget
{
    Q_OBJECT
public:
    MeasurementForm(QWidget *parent = nullptr);
    void handleNext();
    void simulateDeviceContact();


signals:
    void measurementCompleted();
    void nextClicked();
    void exitClicked();
    void depleteBattery(int amount);
public slots:
   void setBattery(int level);

private:
    QVBoxLayout *mainLayout;
    HealthMetricVisualization* metricsVisualization;
    int stepNumber;
    bool noMeasure;
    bool isDeviceContacting;
    QLabel* picture;
   std::vector<QString> imagePaths;
   MeasurementManager* measurementManager;
   QLabel *contactStateLabel;
   QPushButton* viewVisualizationBtn;
   QPushButton *nextBtn;
   QPushButton *exitBtn;
   QProgressBar *battery;
   void showMeasurementVisualization();
   void startDeviceContact();
   void endDeviceContact();

};

#endif // MEASUREMENTFORM_H

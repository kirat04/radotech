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
class MeasurementForm : public QWidget
{
    Q_OBJECT
public:
    MeasurementForm(QWidget *parent = nullptr);
    void handleNext();
signals:
    void nextClicked();
    void exitClicked();
private:
    QVBoxLayout *mainLayout;
    int stepNumber;
    QLabel* picture;
   std::vector<QString> imagePaths;
   MeasurementManager* measurementManager;

};

#endif // MEASUREMENTFORM_H

#ifndef APPLICATION_H
#define APPLICATION_H
#include <QApplication>
#include "usermanager.h"
#include "screenmanager.h"
#include "measurementManager.h"
#include "mainwindow.h"
#include <QStackedWidget>
class Application
{
public:
   Application(MainWindow* w);
   int getCurrentScreen() const;
   void addScreen(QWidget* screen);
   void removeScreen(int screenIndex);

private:
    QStackedWidget* stackedWidget;

};

#endif // APPLICATION_H

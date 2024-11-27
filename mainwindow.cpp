#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) {
    setWindowTitle("Profile Manager");
    setMinimumSize(400, 420);

    // Create central stacked widget
    stackedWidget = new QStackedWidget(this);
    setCentralWidget(stackedWidget);

    // Initialize UserManager and ScreenManager
    UserManager& userManager = UserManager::getInstance();
    ScreenManager& screenManager = ScreenManager::getInstance(stackedWidget);

}

#include "application.h"

Application::Application(MainWindow* w)
{
   // Create central stacked widget
   stackedWidget = new QStackedWidget(w);
   w->setCentralWidget(stackedWidget);

   // Initialize UserManager and ScreenManager
   UserManager& userManager = UserManager::getInstance();
   ScreenManager& screenManager = ScreenManager::getInstance(stackedWidget);


}

int Application::getCurrentScreen() const {
    return stackedWidget->currentIndex();
}

void Application::addScreen(QWidget* screen) {
    stackedWidget->addWidget(screen);
}

void Application::removeScreen(int screenIndex) {
    QWidget* screen = stackedWidget->widget(screenIndex);
    if (screen) {
        stackedWidget->removeWidget(screen);
        delete screen;
    } else {
        qDebug() << "No screen at index:" << screenIndex;
    }
}

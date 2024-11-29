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

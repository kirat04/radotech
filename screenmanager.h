#ifndef SCREENMANAGER_H
#define SCREENMANAGER_H

#include <QStackedWidget>
#include <QWidget>
#include "usermanager.h"
#include "homescreen.h"
#include "loginform.h"
#include "editform.h"
#include "historyform.h"
#include "profileform.h"
#include "measurementform.h"
#include "battery.h"
class ScreenManager : public QObject {
    Q_OBJECT

public:
    static ScreenManager& getInstance(QStackedWidget* stackedWidget = nullptr);

    // Screen Navigation Methods
    void showFirstScreen();
    void showHomeScreen();
    void showCreateProfileScreen();
    void showLoginScreen(int profileIndex);
    void showLoginScreenSwap(int profileIndex);
    void showEditScreen(int profileIndex);
    void showMeasureScreen();
    void showHistoryScreen();

    // Screen Setup Methods
    void initializeScreens();
    HomeScreen* setUpHomeScreem();
    QWidget* setUpProfileScreen();
    QWidget* setUpfirstScreen();

signals:
    void screenChanged(int screenIndex);

private:
    ScreenManager(QStackedWidget* stackedWidget);
    ScreenManager(const ScreenManager&) = delete;
    ScreenManager& operator=(const ScreenManager&) = delete;

    void cleanupStackedWidget(int fromIndex);
    void refreshHomeScreen();

    QStackedWidget* stackedWidget;
    UserManager& userManager;
    Battery* battery;

    enum ScreenIndex {
        FIRST_SCREEN = 0,
        CREATE_PROFILE_SCREEN,
        HOME_SCREEN,
        LOGIN_SCREEN,
        EDIT_SCREEN
    };
};

#endif // SCREENMANAGER_H

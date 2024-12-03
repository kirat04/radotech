#include "screenmanager.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QMessageBox>
#include <QMessageBox>

ScreenManager& ScreenManager::getInstance(QStackedWidget* stackedWidget) {
    static ScreenManager instance(stackedWidget);
    return instance;
}

ScreenManager::ScreenManager(QStackedWidget* stackedWidget)
    : stackedWidget(stackedWidget), userManager(UserManager::getInstance()) {
    if (stackedWidget) {
        initializeScreens();
    }
}

void ScreenManager::cleanupStackedWidget(int fromIndex) {
    while (stackedWidget->count() > fromIndex) {
        QWidget* widget = stackedWidget->widget(stackedWidget->count() - 1);
        stackedWidget->removeWidget(widget);
        delete widget;
    }
}

void ScreenManager::refreshHomeScreen() {
    // Clean up everything after the create profile screen
    cleanupStackedWidget(HOME_SCREEN);

    // Create and add new home screen
    stackedWidget->addWidget(setUpHomeScreem());
}

void ScreenManager::initializeScreens() {

    // Add screens to stacked widget
    stackedWidget->addWidget(setUpfirstScreen());
    stackedWidget->addWidget(setUpProfileScreen());
    stackedWidget->addWidget(setUpHomeScreem());
}

QWidget* ScreenManager::setUpfirstScreen() {
    // First Screen (Initial Screen)

    QWidget* firstScreen = new QWidget();
    QVBoxLayout* firstLayout = new QVBoxLayout(firstScreen);

    QPushButton *createProfileBtn = new QPushButton("Create Profile", firstScreen);
    QPushButton *enterBtn = new QPushButton("Enter", firstScreen);

    firstLayout->addWidget(createProfileBtn);
    firstLayout->addWidget(enterBtn);

    connect(createProfileBtn, &QPushButton::clicked, this, &ScreenManager::showCreateProfileScreen);
    connect(enterBtn, &QPushButton::clicked, this, [this]() {
        if (userManager.getProfileCount() > 0) {
            showHomeScreen();
        } else {
            QMessageBox::warning(nullptr, "Error", "No profiles exist!");
        }
    });

    return firstScreen;
}


QWidget* ScreenManager::setUpProfileScreen() {
    // Create Profile Screen
    QWidget *createProfileScreen = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout(createProfileScreen);

    ProfileForm *profileForm = new ProfileForm(createProfileScreen);
    layout->addWidget(profileForm);

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    QPushButton *saveButton = new QPushButton("Save", createProfileScreen);
    QPushButton *backButton = new QPushButton("Back", createProfileScreen);
    buttonLayout->addWidget(backButton);
    buttonLayout->addWidget(saveButton);
    layout->addLayout(buttonLayout);

    connect(saveButton, &QPushButton::clicked, [this, profileForm]() {
        if (profileForm->validateProfile()) {
            UserProfile newProfile = profileForm->getProfile();
            userManager.addProfile(newProfile);
            refreshHomeScreen();
            showHomeScreen();
            profileForm->clear();
        }
    });

    connect(backButton, &QPushButton::clicked, [this]() {
        showFirstScreen();
    });

    return createProfileScreen;
}

HomeScreen* ScreenManager::setUpHomeScreem() {
    // Home Screen
    HomeScreen* homeScreen = new HomeScreen(userManager.getAllProfiles());

    // Home Screen Connections
    connect(homeScreen, &HomeScreen::profileSelected, this, &ScreenManager::showLoginScreen);
    connect(homeScreen, &HomeScreen::swapProfileClicked, this, &ScreenManager::showLoginScreenSwap);
    connect(homeScreen, &HomeScreen::createProfClicked, this, &ScreenManager::showCreateProfileScreen);
    connect(homeScreen, &HomeScreen::LogOutProfileClicked, [this] () {userManager.clearCurrentUser(); refreshHomeScreen(); stackedWidget->setCurrentIndex(FIRST_SCREEN); });

    connect(homeScreen, &HomeScreen::measureNowClicked, [this]() {
        if(!userManager.hasCurrentUser()){
            QMessageBox::warning(nullptr, "Error", "You are not logged in to a profile!");
        } else {
            showMeasureScreen();
//            QMessageBox::information(nullptr, "Measure Now", "Measurement feature coming soon!");
        }
    });

    connect(homeScreen, &HomeScreen::historyClicked, [this]() {
        if(!userManager.hasCurrentUser()){
            QMessageBox::warning(nullptr, "Error", "You are not logged in to a profile!");
        } else {
            QMessageBox::information(nullptr, "History", "History feature coming soon!");
        }
    });

    connect(homeScreen, &HomeScreen::specialistClicked, [this]() {
       QMessageBox::information(nullptr, "Specialist Recommendations", "Currently we have no recommendations");
    });

    connect(homeScreen, &HomeScreen::createProfClicked, [this]() {
        if(!userManager.isMaxProfileReached()){
            cleanupStackedWidget(CREATE_PROFILE_SCREEN + 1);
            refreshHomeScreen();
            stackedWidget->setCurrentIndex(CREATE_PROFILE_SCREEN);
        }
    });

    return homeScreen;
}

void ScreenManager::showFirstScreen() {
    stackedWidget->setCurrentIndex(FIRST_SCREEN);
}

void ScreenManager::showHomeScreen() {
    stackedWidget->setCurrentIndex(HOME_SCREEN);
}

void ScreenManager::showCreateProfileScreen() {
    if (!userManager.isMaxProfileReached()) {
        stackedWidget->setCurrentIndex(CREATE_PROFILE_SCREEN);
    } else {
        QMessageBox::warning(nullptr, "Error", "Maximum number of profiles reached!");
    }
}

void ScreenManager::showLoginScreen(int profileIndex) {
    cleanupStackedWidget(LOGIN_SCREEN);
    UserProfile* profile = userManager.getProfileByIndex(profileIndex);
    if (profile) {
        LoginForm* loginScreen = new LoginForm(*profile);

        // Modify the connection to match the signal's signature
        connect(loginScreen, &LoginForm::loginSuccessful, this, [this, profileIndex]() {
            showEditScreen(profileIndex);
        });

        connect(loginScreen, &LoginForm::backClicked, this, [this]() {
            cleanupStackedWidget(LOGIN_SCREEN);
            refreshHomeScreen();
            stackedWidget->setCurrentIndex(HOME_SCREEN); // Return to home screen
        });

        refreshHomeScreen();
        stackedWidget->addWidget(loginScreen);
        stackedWidget->setCurrentWidget(loginScreen);
    }
}

void ScreenManager::showLoginScreenSwap(int profileIndex) {
    cleanupStackedWidget(LOGIN_SCREEN);
    UserProfile* profile = userManager.getProfileByIndex(profileIndex);
    if (profile) {
        LoginForm* loginScreen = new LoginForm(*profile);

        // Modify the connection to match the signal's signature
        connect(loginScreen, &LoginForm::loginSuccessful, this, [this, profileIndex]() {
            userManager.setCurrentUser(profileIndex);
            refreshHomeScreen();
            stackedWidget->setCurrentIndex(HOME_SCREEN);
        });

        connect(loginScreen, &LoginForm::backClicked, this, [this]() {
            refreshHomeScreen();
            stackedWidget->setCurrentIndex(HOME_SCREEN);
        });

        refreshHomeScreen();
        stackedWidget->addWidget(loginScreen);
        stackedWidget->setCurrentWidget(loginScreen);
    }
}

void ScreenManager::showEditScreen(int profileIndex) {
    UserProfile* profile = userManager.getProfileByIndex(profileIndex);
    if (profile) {
        cleanupStackedWidget(EDIT_SCREEN);
        EditForm* editScreen = new EditForm(userManager.getAllProfiles(), profileIndex);
        stackedWidget->addWidget(editScreen);
        stackedWidget->setCurrentWidget(editScreen);
        // Connect the profile edited and deleted signals
        connect(editScreen, &EditForm::profileEdited, [this]() {
            userManager.saveProfiles();
            refreshHomeScreen();
            stackedWidget->setCurrentIndex(HOME_SCREEN);
        });

        connect(editScreen, &EditForm::profileDeleted, [this]() {
            userManager.saveProfiles();
            refreshHomeScreen();
            stackedWidget->setCurrentIndex(HOME_SCREEN);
        });

        connect(editScreen, &EditForm::lastprofileDeleted, [this]() {
            userManager.saveProfiles();
            refreshHomeScreen();
            stackedWidget->setCurrentIndex(FIRST_SCREEN);
        });
    }
}

void ScreenManager::showMeasureScreen(){
    MeasurementForm* measureScreen = new MeasurementForm();
    stackedWidget->addWidget(measureScreen);
    stackedWidget->setCurrentWidget(measureScreen);

    // Connect theexit and next signals
    connect(measureScreen, &MeasurementForm::exitClicked, [this]() {
        refreshHomeScreen();
        stackedWidget->setCurrentIndex(HOME_SCREEN);
    });

    connect(measureScreen, &MeasurementForm::nextClicked, measureScreen, &MeasurementForm::handleNext);
}

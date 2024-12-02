QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    application.cpp \
    battery.cpp \
    editform.cpp \
    homescreen.cpp \
    healthmetricVisualization.cpp \
    loginform.cpp \
    measurementManager.cpp \
    measurementform.cpp \
    profileform.cpp \
    screenmanager.cpp \
    storageManager.cpp \
    usermanager.cpp \
    main.cpp \
    userprofile.cpp\
    mainwindow.cpp

HEADERS += \
    application.h \
    battery.h \
    editform.h \
    homescreen.h \
    healthmetricVisualization.h \
    loginform.h \
    measurementform.h \
    profileform.h \
    screenmanager.h \
    measurementManager.h \
    storageManager.h \
    usermanager.h \
    userprofile.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES +=

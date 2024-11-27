QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Application.cpp \
    Battery.cpp \
    editform.cpp \
    DataProcessor.cpp \
    DeviceManager.cpp \
    HardwareInterface.cpp \
    homescreen.cpp \
    loginform.cpp \
    MeasurementManager.cpp \
    profileform.cpp \
    SafetyManager.cpp \
    screenmanager.cpp \
    UserInterface.cpp \
    UserManager.cpp \
    usermanager.cpp \
    main.cpp \
    serprofile.cpp\
    mainwindow.cpp

HEADERS += \
    Application.h \
    Battery.h \
    editform.h \
    DataProcessor.h \
    DeviceManager.h \
    HardwareInterface.h \
    homescreen.h \
    MeasurementManager.h \
    profileform.h \
    SafetyManager.h \
    screenmanager.h \
    UserInterface.h \
    UserManager.h \
    usermanager.h \
    serprofile.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

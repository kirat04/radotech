QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    editform.cpp \
    homescreen.cpp \
    loginform.cpp \
    main.cpp \
    mainwindow.cpp \
    profileform.cpp \
    screenmanager.cpp \
    usermanager.cpp \
    userprofile.cpp

HEADERS += \
    editform.h \
    homescreen.h \
    loginform.h \
    mainwindow.h \
    profileform.h \
    screenmanager.h \
    usermanager.h \
    userprofile.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

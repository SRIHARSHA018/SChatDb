QT       += core gui sql network testlib


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
CONFIG += testcase

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Testing/test_app.cpp \
    chatmanager.cpp \
    emoji_pop_up.cpp \
    main.cpp \
    mainwindow.cpp \
    task_manager.cpp

HEADERS += \
    Testing/test_app.h \
    chatmanager.h \
    emoji_pop_up.h \
    mainwindow.h \
    profile.h \
    task_manager.h

FORMS += \
    emoji_pop_up.ui \
    mainwindow.ui

# Default rules for deployment.


qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    profile.qrc


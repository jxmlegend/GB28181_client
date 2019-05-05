#-------------------------------------------------
#
# Project created by QtCreator 2019-04-29T16:44:21
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GBD2019_04_29
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        sipmainwindow.cpp \
    AlarmControlFactory.cpp \
    CameraControlFactory.cpp \
    CommFactory.cpp \
    Device.cpp \
    DeviceControlFactory.cpp \
    ExosipServer.cpp \
    GetFactory.cpp \
    InviteFactory.cpp \
    RecordControlFactory.cpp \
    RequestFactory.cpp \
    registfactory.cpp

HEADERS += \
        sipmainwindow.h \
    AlarmControlFactory.h \
    CameraControlFactory.h \
    CommFactory.h \
    Device.h \
    DeviceControlFactory.h \
    ExosipServer.h \
    GetFactory.h \
    InviteFactory.h \
    RecordControlFactory.h \
    RequestFactory.h \
    registfactory.h

FORMS += \
        sipmainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

LIBS += -L$$PWD -llibeay32
LIBS += -L$$PWD -lssleay32
win32: LIBS += -L$$PWD -llibcares
win32: LIBS += -L$$PWD -leXosip
win32: LIBS += -L$$PWD -losip2
win32: LIBS += -L$$PWD -losipparser2
LIBS += -lws2_32
LIBS += -ldelayimp
LIBS += -lAdvapi32
LIBS += -lDnsapi
LIBS += -lQwave

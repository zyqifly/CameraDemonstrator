#-------------------------------------------------
#
# Project created by QtCreator 2020-08-27T15:49:42
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ViewerWidget
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        widget.cpp

HEADERS  += widget.h

FORMS    += widget.ui

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../CameraFactorSDK/LIB_VS2013/x64/Release/ -lCameraFactory
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../CameraFactorSDK/LIB_VS2013/x64/Debug/ -lCameraFactoryd

INCLUDEPATH += $$PWD/../../CameraFactorSDK/include
DEPENDPATH += $$PWD/../../CameraFactorSDK/include

#-------------------------------------------------
#
# Project created by QtCreator 2016-05-05T16:24:43
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RPI_Photobooth
target.path = /home/pi
INSTALLS += target

TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp\
        button_lib.cpp \
    camerathread.cpp \
    gallerythread.cpp \
    settingsdialog.cpp

HEADERS  += mainwindow.h\
         button_lib.h\
         wiringPi.h \
    raspicam.h \
    raspicamtypes.h \
    camerathread.h \
    raspicam_still.h \
    settingsdialog.h \
    gallerythread.h

FORMS    += mainwindow.ui \
    SettingsDialog.ui

unix:!macx: LIBS += -L$$PWD/../libs/ -lwiringPi

CONFIG += c++11

INCLUDEPATH += $$PWD/../libs
DEPENDPATH += $$PWD/../libs

unix:!macx: LIBS += -L$$PWD/../libs/ -lraspicam

INCLUDEPATH += $$PWD/../libs
DEPENDPATH += $$PWD/../libs

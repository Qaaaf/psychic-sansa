#-------------------------------------------------
#
# Project created by QtCreator 2014-02-18T14:10:58
#
#-------------------------------------------------

QT       += core gui multimedia


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = WAMProto
CONFIG   += console
QT += multimedia


TEMPLATE = app


SOURCES += main.cpp \
    gamewindow.cpp \
    settingswindow.cpp \
    gameboard.cpp \
    tile.cpp \
    configfile.cpp \
    game.cpp \
    animal.cpp \
    star.cpp

HEADERS += \
    gamewindow.h \
    settingswindow.h \
    gameboard.h \
    tile.h \
    configfile.h \
    game.h \
    animal.h \
    star.h

RESOURCES += \
    resourcesWAM.qrc

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android

OTHER_FILES += \
    android/AndroidManifest.xml

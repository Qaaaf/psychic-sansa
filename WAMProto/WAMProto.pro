#-------------------------------------------------
#
# Project created by QtCreator 2014-02-18T14:10:58
#
#-------------------------------------------------

QT       += core gui


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
    game.cpp

HEADERS += \
    gamewindow.h \
    settingswindow.h \
    gameboard.h \
    tile.h \
    configfile.h \
    game.h

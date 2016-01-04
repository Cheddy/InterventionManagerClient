#-------------------------------------------------
#
# Project created by QtCreator 2016-01-04T16:45:27
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = InterventionManagerClient
TEMPLATE = app

CONFIG += c++11

SOURCES += main.cpp\
        mainwindow.cpp \
    Managers/genericmanager.cpp \
    Model/datastructure.cpp \
    Model/Impl/staffrank.cpp

HEADERS  += mainwindow.h \
    Managers/genericmanager.h \
    Model/datastructure.h \
    Model/Impl/staffrank.h

FORMS    += mainwindow.ui \
    Managers/genericmanager.ui

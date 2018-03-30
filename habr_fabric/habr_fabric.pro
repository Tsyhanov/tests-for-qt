#-------------------------------------------------
#
# Project created by QtCreator 2017-07-13T12:59:41
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = habr_fabric
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
    fabric.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

CONFIG += c++11

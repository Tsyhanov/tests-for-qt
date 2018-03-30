#-------------------------------------------------
#
# Project created by QtCreator 2017-07-19T14:02:23
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = customtreeview
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    treemodel.cpp \
    treeitem.cpp

HEADERS  += mainwindow.h \
    treemodel.h \
    treeitem.h

FORMS    += mainwindow.ui

DISTFILES +=

RESOURCES += \
    customtreeview.qrc

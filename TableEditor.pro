#-------------------------------------------------
#
# Project created by QtCreator 2015-09-18T08:30:09
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TableEditor
TEMPLATE = app


SOURCES += main.cpp\
    mytablemodel.cpp \
    mainwindow.cpp \
    plotwidget.cpp

HEADERS  += \
    mytablemodel.h \
    mainwindow.h \
    plotwidget.h

FORMS += \
    mainwindow.ui

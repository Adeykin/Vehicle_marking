#-------------------------------------------------
#
# Project created by QtCreator 2017-03-29T23:04:51
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = marking
TEMPLATE = app
CONFIG  += c++11


SOURCES += main.cpp\
        mainwindow.cpp \
    markwidget.cpp \
    helpers.cpp

HEADERS  += mainwindow.h \
    markwidget.h \
    helpers.h

FORMS    += mainwindow.ui

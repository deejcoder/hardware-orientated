#-------------------------------------------------
#
# Project created by QtCreator 2017-10-21T18:25:03
#
#-------------------------------------------------

QT       += core gui serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = assignment6-gui
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui


include(qextserialport/qextserialport.pri)

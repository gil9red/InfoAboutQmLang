QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = InfoAboutQmLang
TEMPLATE = app

DESTDIR = ../bin

SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

RESOURCES += \
    resource.qrc

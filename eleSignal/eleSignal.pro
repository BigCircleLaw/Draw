#-------------------------------------------------
#
# Project created by QtCreator 2019-07-28T16:22:48
#
#-------------------------------------------------

QT       += core gui
QT       += serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = eleSignal
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \ 
    MyParse.cpp

HEADERS  += mainwindow.h \
    public.h \
    MyParse.h 

FORMS    += mainwindow.ui

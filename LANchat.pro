#-------------------------------------------------
#
# Project created by QtCreator 2016-03-03T19:17:01
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

greaterThan(QT_MAJOR_VERSION, 4){
CONFIG += c++11
} else {
QMAKE_CXXFLAGS += -std=c++0x
}

TARGET = LANchat
TEMPLATE = app


SOURCES += main.cpp\
    viewWidget.cpp \
    mainwindow.cpp \
    network.cpp \
    tcplclient.cpp

HEADERS  += \
    viewWidget.h \
    mainwindow.h \
    network.h \
    sharedmemory.h \
    tcpclient.h

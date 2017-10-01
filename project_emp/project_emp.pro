#-------------------------------------------------
#
# Project created by QtCreator 2017-09-18T20:04:17
#
#-------------------------------------------------

QT       += core gui
QT       += sql
QT       += widgets
QT       += printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = output\bin
TEMPLATE = app

SOURCES += src/main.cpp \
    src/mainwindow.cpp \
    src/sqlconnector.cpp \
    src/databasedata.cpp \
    src/insertdialog.cpp \
    src/business.cpp \
    src/logindialog.cpp

HEADERS  += src/mainwindow.h \
    src/sqlconnector.h \
    src/databasedata.h \
    src/insertdialog.h \
    src/business.h \
    src/logindialog.h

FORMS    += src/mainwindow.ui \
    src/insertdialog.ui \
    src/logindialog.ui

INCLUDEPATH += /usr/include/mysql

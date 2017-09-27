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

TARGET = project_emp
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    sqlconnector.cpp \
    databasedata.cpp \
    insertdialog.cpp \
    business.cpp \
    logindialog.cpp

HEADERS  += mainwindow.h \
    sqlconnector.h \
    databasedata.h \
    insertdialog.h \
    business.h \
    logindialog.h

FORMS    += mainwindow.ui \
    insertdialog.ui \
    logindialog.ui

INCLUDEPATH += /usr/include/mysql

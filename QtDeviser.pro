#-------------------------------------------------
#
# Project created by QtCreator 2015-06-09T15:49:26
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QtDeviser
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    formdeviserpackage.cpp \
    formdeviserversion.cpp \
    formdeviserenum.cpp

HEADERS  += mainwindow.h \
    formdeviserpackage.h \
    formdeviserversion.h \
    formdeviserenum.h

FORMS    += mainwindow.ui \
    formdeviserpackage.ui \
    formdeviserversion.ui \
    formdeviserenum.ui

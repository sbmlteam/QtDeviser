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
    formdeviserenum.cpp \
    formdevisermapping.cpp \
    formdeviserclass.cpp \
    formdeviserplugin.cpp \
    dialogabout.cpp \
    dialoguml.cpp \
    dialoggenerate.cpp

HEADERS  += mainwindow.h \
    formdeviserpackage.h \
    formdeviserversion.h \
    formdeviserenum.h \
    formdevisermapping.h \
    formdeviserclass.h \
    formdeviserplugin.h \
    dialogabout.h \
    dialoguml.h \
    dialoggenerate.h

FORMS    += mainwindow.ui \
    formdeviserpackage.ui \
    formdeviserversion.ui \
    formdeviserenum.ui \
    formdevisermapping.ui \
    formdeviserclass.ui \
    formdeviserplugin.ui \
    dialogabout.ui \
    dialoguml.ui \
    dialoggenerate.ui

RESOURCES += \
    deviser-resources.qrc

win32 {
  RC_FILE = deviser.rc
}

DISTFILES += \
    deviser.rc


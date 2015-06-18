#-------------------------------------------------
#
# Project created by QtCreator 2015-06-09T15:49:26
#
#-------------------------------------------------

QT       += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QtDeviser
TEMPLATE = app


SOURCES += main.cpp\
           ui/mainwindow.cpp \
           ui/formdeviserpackage.cpp \
           ui/formdeviserversion.cpp \
           ui/formdeviserenum.cpp \
           ui/formdevisermapping.cpp \
           ui/formdeviserclass.cpp \
           ui/formdeviserplugin.cpp \
           ui/dialogabout.cpp \
           ui/dialoguml.cpp \
           ui/dialoggenerate.cpp \
    model/deviserbase.cpp \
    model/deviserattribute.cpp \
    model/deviserclass.cpp \
    model/deviserconcrete.cpp \
    model/deviserenum.cpp \
    model/deviserenumvalue.cpp \
    model/deviserlistofattribute.cpp \
    model/devisermapping.cpp \
    model/deviserversion.cpp \
    model/deviserplugin.cpp \
    model/deviserpackage.cpp \
    model/deviserreferenceattribute.cpp

HEADERS  += ui/mainwindow.h \
            ui/formdeviserpackage.h \
            ui/formdeviserversion.h \
            ui/formdeviserenum.h \
            ui/formdevisermapping.h \
            ui/formdeviserclass.h \
            ui/formdeviserplugin.h \
            ui/dialogabout.h \
            ui/dialoguml.h \
            ui/dialoggenerate.h \
    model/deviserbase.h \
    model/deviserattribute.h \
    model/deviserclass.h \
    model/deviserconcrete.h \
    model/deviserenum.h \
    model/deviserenumvalue.h \
    model/deviserlistofattribute.h \
    model/devisermapping.h \
    model/deviserversion.h \
    model/deviserplugin.h \
    model/deviserpackage.h \
    model/deviserreferenceattribute.h

FORMS    += ui/mainwindow.ui \
            ui/formdeviserpackage.ui \
            ui/formdeviserversion.ui \
            ui/formdeviserenum.ui \
            ui/formdevisermapping.ui \
            ui/formdeviserclass.ui \
            ui/formdeviserplugin.ui \
            ui/dialogabout.ui \
            ui/dialoguml.ui \
            ui/dialoggenerate.ui

RESOURCES += \
    deviser-resources.qrc

win32 {
  RC_FILE = deviser.rc
}

DISTFILES += \
    deviser.rc


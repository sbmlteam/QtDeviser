#-------------------------------------------------
#
# Project created by QtCreator 2015-06-09T15:49:26
#
#-------------------------------------------------

QT       += core gui xml network svg help #webkitwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DeviserEdit
TEMPLATE = app


SOURCES += main.cpp \
           util.cpp \
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
           ui/loattributesmodel.cpp\
           ui/concretesmodel.cpp\
           ui/enummodel.cpp\
           ui/mappingmodel.cpp\
           ui/attributesmodel.cpp \
           ui/qzoomgraphicsview.cpp \
           ui/dialogpreferences.cpp \
           ui/dialogerrors.cpp \
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
           model/deviserreferenceattribute.cpp \
           model/devisersettings.cpp \
           validation/deviservalidator.cpp \
           validation/devisermessage.cpp \
           validation/deviserconstraint.cpp \
           validation/packageconstraints.cpp \
           validation/haslistofconstraint.cpp \
           validation/hasmathconstraint.cpp \
           validation/haschildrenconstraint.cpp \
           validation/isbaseclassconstraint.cpp \
    ui/flowlayout.cpp \
    ui/smoothgraphicsitem.cpp \
    validation/typecodeconstraint.cpp \
    model/deviserlanguage.cpp \
    ui/workerthread.cpp \
    ui/dialogdisplaynumbers.cpp \
    validation/attributeconstraints.cpp \
    validation/enumconstraint.cpp \
    validation/instantiationconstraint.cpp \
    validation/uniquenameconstraint.cpp \
    ui/typechooserdelegate.cpp \
    ui/attributedelegate.cpp \
    ui/helpwindow.cpp \
    ui/helpbrowser.cpp \
    model/deviserlanguagedependency.cpp \
    model/deviserlanguageversion.cpp \
    ui/formdeviserlanguage.cpp \
    ui/dependencymodel.cpp \
    ui/languageversionmodel.cpp


HEADERS  += util.h \
            ui/mainwindow.h \
            ui/formdeviserpackage.h \
            ui/formdeviserversion.h \
            ui/formdeviserenum.h \
            ui/formdevisermapping.h \
            ui/formdeviserclass.h \
            ui/formdeviserplugin.h \
            ui/dialogabout.h \
            ui/dialoguml.h \
            ui/dialoggenerate.h \
            ui/loattributesmodel.h\
            ui/concretesmodel.h \
            ui/enummodel.h \
            ui/mappingmodel.h\
            ui/attributesmodel.h \
            ui/qzoomgraphicsview.h \
            ui/dialogpreferences.h \
            ui/dialogerrors.h \
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
            model/deviserreferenceattribute.h \
            model/devisersettings.h \
            model/deviserfwd.h \
            model/devisertypes.h \
            validation/deviservalidator.h \
            validation/devisermessage.h \
            validation/deviserconstraint.h \
            validation/packageconstraints.h \
            validation/haslistofconstraint.h \
            validation/hasmathconstraint.h \
            validation/haschildrenconstraint.h \
            validation/isbaseclassconstraint.h \
            validation/uniquenameconstraint.h \
    deviser-version.h \
    ui/flowlayout.h \
    ui/smoothgraphicsitem.h \
    validation/typecodeconstraint.h \
    model/deviserlanguage.h \
    ui/workerthread.h \
    ui/dialogdisplaynumbers.h \
    validation/attributeconstraints.h \
    validation/enumconstraint.h \
    validation/instantiationconstraint.h \
    ui/typechooserdelegate.h \
    ui/attributedelegate.h \
    ui/helpwindow.h \
    ui/helpbrowser.h \
    model/deviserlanguagedependency.h \
    model/deviserlanguageversion.h \
    ui/formdeviserlanguage.h \
    ui/dependencymodel.h \
    ui/languageversionmodel.h



FORMS    += ui/mainwindow.ui \
            ui/formdeviserpackage.ui \
            ui/formdeviserversion.ui \
            ui/formdeviserenum.ui \
            ui/formdevisermapping.ui \
            ui/formdeviserclass.ui \
            ui/formdeviserplugin.ui \
            ui/dialogabout.ui \
            ui/dialoguml.ui \
            ui/dialoggenerate.ui \
            ui/dialogpreferences.ui \
            ui/dialogerrors.ui \
    ui/dialogdisplaynumbers.ui \
    ui/helpwindow.ui \
    ui/formdeviserlanguage.ui

RESOURCES += \
    deviser-resources.qrc

win32
{
  RC_FILE = deviser.rc
}

DISTFILES += \
    deviser.rc \
    VERSION.txt \
    readme.md \
    license.txt \
    CMakeLists.txt \
    ChooseQtVersion.cmake \
    CoreClasses.txt \
    main.tex

target.path = $$PREFIX/
INSTALLS += DeviserEdit

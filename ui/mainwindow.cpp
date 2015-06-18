#include <QFileDialog>

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "formdeviserpackage.h"
#include "formdeviserversion.h"
#include "formdeviserenum.h"
#include "formdevisermapping.h"
#include "formdeviserclass.h"
#include "formdeviserplugin.h"

#include "dialogabout.h"
#include "dialoguml.h"
#include "dialoggenerate.h"

#include <model/deviserpackage.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    ctrlPackage(new FormDeviserPackage(this)),
    ctrlVersion(new FormDeviserVersion(this)),
    ctrlEnum(new FormDeviserEnum(this)),
    ctrlMapping(new FormDeviserMapping(this)),
    ctrlClass(new FormDeviserClass(this)),
    ctrlPlugin(new FormDeviserPlugin(this))
{
    ui->setupUi(this);

    ui->stackedWidget->addWidget(ctrlPackage);
    ui->stackedWidget->addWidget(ctrlVersion);
    ui->stackedWidget->addWidget(ctrlEnum);
    ui->stackedWidget->addWidget(ctrlMapping);
    ui->stackedWidget->addWidget(ctrlClass);
    ui->stackedWidget->addWidget(ctrlPlugin);

    ui->stackedWidget->setCurrentWidget(ctrlPackage);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void
MainWindow::showAbout()
{
    DialogAbout about;
    about.exec();
}

void
MainWindow::addClass()
{
ui->stackedWidget->setCurrentWidget(ctrlClass);
}

void
MainWindow::addEnum()
{
ui->stackedWidget->setCurrentWidget(ctrlEnum);
}

void
MainWindow::addPlugin()
{
ui->stackedWidget->setCurrentWidget(ctrlPlugin);
}

void
MainWindow::addVersion()
{
ui->stackedWidget->setCurrentWidget(ctrlVersion);
}

void
MainWindow::editPreferences()
{

}

void
MainWindow::fixErrors()
{

}

void
MainWindow::generate()
{
  DialogGenerate generate;
  generate.exec();
}

void
MainWindow::newModel()
{
    if (model != NULL)
        delete model;

    model = new DeviserPackage();
    currentElement = model;
    fileName = "";

}

void
MainWindow::updateUI()
{

}


void
MainWindow::openFile()
{

    QString oldDir;
    if (!fileName.isEmpty())
    {
        oldDir = QFileInfo(fileName).dir().dirName();
    }

    QString& fileName = QFileDialog::getOpenFileName(this, "Open Deviser Description", oldDir, "XML files (*.xml);;All files (*.*)");

    if (!fileName.isEmpty())
        openFile(fileName);



}

void MainWindow::openFile(const QString& fileName)
{
    if (model != NULL)
        delete model;

    model= new DeviserPackage(fileName);
    currentElement = model;
    updateUI();

}

void
MainWindow::saveFile()
{

}

void
MainWindow::saveFileAs()
{

}

void
MainWindow::saveAsFile(QString)
{

}

void
MainWindow::showUML()
{
    DialogUML uml;
    uml.exec();
}

void
MainWindow::validateDescription()
{

}
#include <iostream>

void MainWindow::on_treeWidget_itemSelectionChanged()
{
    const QList<QTreeWidgetItem*>& selectedItems = ui->treeWidget->selectedItems();
    if (selectedItems.size() == 0) return;

    foreach (QTreeWidgetItem* item, selectedItems) {
        if (item->text(0) == "Package")
        {
ui->stackedWidget->setCurrentWidget(ctrlPackage);
        } else if (item->text(0) == "Classes")
        {
ui->stackedWidget->setCurrentWidget(ctrlClass);
        } else if (item->text(0) == "Plugins")
        {
ui->stackedWidget->setCurrentWidget(ctrlPlugin);
        } else if (item->text(0) == "Mappings")
        {
ui->stackedWidget->setCurrentWidget(ctrlMapping);
        } else if (item->text(0) == "Enums")
        {
ui->stackedWidget->setCurrentWidget(ctrlEnum);
        }
        else if (item->text(0).startsWith("Version"))
                {
ui->stackedWidget->setCurrentWidget(ctrlVersion);
                }
    }

}

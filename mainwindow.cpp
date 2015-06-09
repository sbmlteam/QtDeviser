#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "formdeviserpackage.h"
#include "formdeviserversion.h"
#include "formdeviserenum.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    ctrlPackage(new FormDeviserPackage(this)),
    ctrlVersion(new FormDeviserVersion(this)),
    ctrlEnum(new FormDeviserEnum(this))
{
    ui->setupUi(this);

    ui->stackedWidget->addWidget(ctrlPackage);
    ui->stackedWidget->addWidget(ctrlVersion);
    ui->stackedWidget->addWidget(ctrlEnum);

    ui->stackedWidget->setCurrentWidget(ctrlEnum);

}

MainWindow::~MainWindow()
{
    delete ui;
}

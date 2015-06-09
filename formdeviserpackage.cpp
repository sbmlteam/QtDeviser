#include "formdeviserpackage.h"
#include "ui_formdeviserpackage.h"

FormDeviserPackage::FormDeviserPackage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormDeviserPackage)
{
    ui->setupUi(this);
}

FormDeviserPackage::~FormDeviserPackage()
{
    delete ui;
}

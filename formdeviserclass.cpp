#include "formdeviserclass.h"
#include "ui_formdeviserclass.h"

FormDeviserClass::FormDeviserClass(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormDeviserClass)
{
    ui->setupUi(this);
}

FormDeviserClass::~FormDeviserClass()
{
    delete ui;
}

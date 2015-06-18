#include "formdeviserenum.h"
#include "ui_formdeviserenum.h"

FormDeviserEnum::FormDeviserEnum(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormDeviserEnum)
{
    ui->setupUi(this);
}

FormDeviserEnum::~FormDeviserEnum()
{
    delete ui;
}


void
FormDeviserEnum::addRow()
{
  ui->tableWidget->insertRow(ui->tableWidget->rowCount());
}

void
FormDeviserEnum::deleteRow()
{

}

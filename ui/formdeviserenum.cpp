#include "formdeviserenum.h"
#include "ui_formdeviserenum.h"

#include <model/deviserenum.h>
#include <model/deviserenumvalue.h>

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
FormDeviserEnum::initializeFrom(DeviserEnum* devEnum)
{
    mEnum = devEnum;

    ui->txtName->clear();
    while(ui->tableWidget->rowCount() > 0)
        ui->tableWidget->removeRow(0);

    if (mEnum != NULL)
    {
        ui->txtName->setText(devEnum->getName());

        foreach(auto* enumValue, devEnum->getValues())
        {
            int index = ui->tableWidget->rowCount();
            ui->tableWidget->insertRow(index);
            ui->tableWidget->setItem(index, 0, new QTableWidgetItem(enumValue->getName()));
            ui->tableWidget->setItem(index, 1, new QTableWidgetItem(enumValue->getValue()));
        }
    }
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

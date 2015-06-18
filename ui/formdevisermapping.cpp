#include "formdevisermapping.h"
#include "ui_formdevisermapping.h"

#include <model/deviserversion.h>
#include <model/devisermapping.h>

FormDeviserMapping::FormDeviserMapping(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormDeviserMapping)
{
    ui->setupUi(this);
}

FormDeviserMapping::~FormDeviserMapping()
{
    delete ui;
}

void
FormDeviserMapping::initializeFrom(DeviserVersion* version)
{
    mVersion = version;

    while(ui->tableWidget->rowCount() > 0)
        ui->tableWidget->removeRow(0);

    if (mVersion != NULL)
    {
        foreach(auto* mapping, version->getMappings())
        {
            int index = ui->tableWidget->rowCount();
            ui->tableWidget->insertRow(index);

            ui->tableWidget->setItem(index, 0, new QTableWidgetItem(mapping->getName()));
            ui->tableWidget->setItem(index, 1, new QTableWidgetItem(mapping->getPackage()));
        }
    }

}

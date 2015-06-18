#include "formdeviserversion.h"
#include "ui_formdeviserversion.h"

#include <model/deviserversion.h>
#include <model/deviserclass.h>

FormDeviserVersion::FormDeviserVersion(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormDeviserVersion),
    mVersion(NULL)
{
    ui->setupUi(this);
}

FormDeviserVersion::~FormDeviserVersion()
{
    delete ui;
}


void
FormDeviserVersion::initializeFrom(DeviserVersion* version)
{
  mVersion = version;

  ui->txtCoreLevel->clear();
  ui->txtCoreVersion->clear();
  ui->txtPackageVersion->clear();

  ui->listWidget->clear();

  if (version != NULL)
  {
    ui->txtCoreLevel->setText(QString::number(version->getLevel()));
    ui->txtCoreVersion->setText(QString::number(version->getVersion()));
    ui->txtPackageVersion->setText(QString::number(version->getPkgVersion()));

    foreach(auto* element, version->getElements())
    {
     ui->listWidget->addItem(element->getName());
    }

  }

}

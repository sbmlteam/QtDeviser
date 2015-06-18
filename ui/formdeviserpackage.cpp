#include "formdeviserpackage.h"
#include "ui_formdeviserpackage.h"

#include <model/deviserpackage.h>

FormDeviserPackage::FormDeviserPackage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormDeviserPackage), 
    mPackage(NULL)
{
    ui->setupUi(this);
}

FormDeviserPackage::~FormDeviserPackage()
{
    delete ui;
}

void FormDeviserPackage::initializeFrom(DeviserPackage* package)
{
  mPackage = package;

  blockSignals(true);

  ui->txtDeclaration->clear();
  ui->txtFullName->clear();
  ui->txtImplementation->clear();
  ui->txtName->clear();
  ui->txtNumber->clear();
  ui->txtOffset->clear();
  ui->chkRequired->setChecked(false);
  ui->chkRequiresAdditionalCode->setChecked(false);
  ui->groupBox->setVisible(false);

  if (package != NULL)
  {
    ui->txtDeclaration->setText(package->getAdditionalDeclarations());
    ui->txtImplementation->setText(package->getAdditionalDefinitions());
    ui->chkRequiresAdditionalCode->setChecked(!package->getAdditionalDefinitions().isEmpty() || !package->getAdditionalDeclarations().isEmpty());
    ui->groupBox->setVisible(ui->chkRequiresAdditionalCode->isChecked());

    ui->txtName->setText(package->getName());
    ui->txtFullName->setText(package->getFullName());
    ui->txtNumber->setText(QString::number(package->getStartNumber()));
    ui->txtOffset->setText(QString::number(package->getOffset()));

    ui->chkRequired->setChecked(package->getRequired());

  }

  blockSignals(false);
}

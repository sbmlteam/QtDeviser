#include "formdeviserpackage.h"
#include "ui_formdeviserpackage.h"
#include "util.h"

#include <QFileDialog>

#include <model/deviserpackage.h>

#include <ui/dialogdisplaynumbers.h>

FormDeviserPackage::FormDeviserPackage(QWidget *parent)
  : QWidget(parent)
  , ui(new Ui::FormDeviserPackage)
  , mPackage(NULL)
  , mbInitializing(true)
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

  mbInitializing = true;

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
    nameModified(package->getName());
    ui->txtFullName->setText(package->getFullName());
    fullNameModified(package->getFullName());
    ui->txtNumber->setText(QString::number(package->getStartNumber()));
    numberModified(QString::number(package->getStartNumber()));
    ui->txtOffset->setText(QString::number(package->getOffset()));
    offsetModified(QString::number(package->getOffset()));

    ui->chkRequired->setChecked(package->isRequired());

  }

  mbInitializing = false;
}

void
FormDeviserPackage::browseImplementation()
{
  if (mPackage == NULL || mbInitializing) return;
  QString fileName = QFileDialog::getOpenFileName(this, "Select Implementation file", NULL, Util::getImplementationFilter());
  mPackage->setAdditionalDefinitions(fileName);
  ui->txtImplementation->setText(fileName);
}

void
FormDeviserPackage::browseDeclaration()
{
  if (mPackage == NULL || mbInitializing) return;
  QString fileName = QFileDialog::getOpenFileName(this, "Select Declaration file", NULL, Util::getHeaderFilter());
  mPackage->setAdditionalDeclarations(fileName);
  ui->txtDeclaration->setText(fileName);
}

void
FormDeviserPackage::additionalCodeStateChanged(int)
{
  ui->groupBox->setVisible(ui->chkRequiresAdditionalCode->isChecked());
}

void
FormDeviserPackage::requiredStateChanged(int)
{
  if (mPackage == NULL || mbInitializing) return;
  mPackage->setRequired(ui->chkRequired->isChecked());
}

void
FormDeviserPackage::offsetChanged(const QString&)
{
  if (mPackage == NULL || mbInitializing) return;
  mPackage->setOffset(ui->txtOffset->text().toInt());
}

void
FormDeviserPackage::numberChanged(const QString&)
{
  if (mPackage == NULL || mbInitializing) return;
  mPackage->setStartNumber(ui->txtNumber->text().toInt());
}

void
FormDeviserPackage::nameChanged(const QString&)
{
  if (mPackage == NULL || mbInitializing) return;
  mPackage->setName(ui->txtName->text());
}

void
FormDeviserPackage::implementationChanged(const QString&)
{
  if (mPackage == NULL || mbInitializing) return;
  mPackage->setAdditionalDefinitions(ui->txtImplementation->text());

}

void
FormDeviserPackage::fullNameChanged(const QString&)
{
  if (mPackage == NULL || mbInitializing) return;
  mPackage->setFullName(ui->txtFullName->text());

}

void
FormDeviserPackage::declarationChanged(const QString&)
{
  if (mPackage == NULL || mbInitializing) return;
  mPackage->setAdditionalDeclarations(ui->txtDeclaration->text());

}

void FormDeviserPackage::showNumbersAndOffsets()
{
  DialogDisplayNumbers dlg;
  dlg.exec();
}

void
FormDeviserPackage::nameModified(const QString &value)
{
  if (value.isEmpty() || QRegExp("\\s*").exactMatch(value))
    ui->txtName->setStyleSheet(Util::getErrorStyleSheet());
  else
    ui->txtName->setStyleSheet("");
}

void
FormDeviserPackage::fullNameModified(const QString &value)
{
  if (value.isEmpty() || QRegExp("\\s*").exactMatch(value))
    ui->txtFullName->setStyleSheet(Util::getErrorStyleSheet());
  else
    ui->txtFullName->setStyleSheet("");
}

void
FormDeviserPackage::numberModified(const QString &value)
{
  if (value.isEmpty() || QRegExp("\\s*").exactMatch(value) || !value.endsWith("00"))
    ui->txtNumber->setStyleSheet(Util::getErrorStyleSheet());
  else
    ui->txtNumber->setStyleSheet("");
}

void
FormDeviserPackage::offsetModified(const QString &value)
{
  if (value.isEmpty() || QRegExp("\\s*").exactMatch(value)|| !value.endsWith("00000"))
    ui->txtOffset->setStyleSheet(Util::getErrorStyleSheet());
  else
    ui->txtOffset->setStyleSheet("");
}

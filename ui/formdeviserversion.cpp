#include "formdeviserversion.h"
#include "ui_formdeviserversion.h"

#include <model/deviserversion.h>
#include <model/deviserclass.h>

FormDeviserVersion::FormDeviserVersion(QWidget *parent)
  : QWidget(parent)
  , ui(new Ui::FormDeviserVersion)
  , mVersion(NULL)
  , mbInitializing(true)
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

  mbInitializing = true;

  ui->txtCoreLevel->clear();
  ui->txtCoreVersion->clear();
  ui->txtPackageVersion->clear();
  ui->chkIgnorePackageVersion->setChecked(false);

  ui->lstClasses->clear();


  if (version != NULL)
  {
    ui->txtCoreLevel->setText(QString::number(version->getLevel()));
    ui->txtCoreVersion->setText(QString::number(version->getVersion()));
    ui->txtPackageVersion->setText(QString::number(version->getPkgVersion()));
    ui->chkIgnorePackageVersion->setChecked(version->getIgnorePackageVersion());

    foreach(DeviserClass* element, version->getElements())
    {
      ui->lstClasses->addItem(element->getName());
    }

  }

  mbInitializing = false;
}


void
FormDeviserVersion::downPressed()
{
  if (mVersion == NULL || mbInitializing) return;

  const QList<QListWidgetItem*>& selected = ui->lstClasses->selectedItems();
  foreach(const QListWidgetItem* item, selected)
  {
    int row = ui->lstClasses->row(item);
    if (row == ui->lstClasses->count()-1) continue;

    QListWidgetItem* taken = ui->lstClasses->takeItem(row);
    ui->lstClasses->insertItem(row + 1, taken);
    DeviserClass* current =  mVersion->getElements().takeAt(row);
    mVersion->getElements().insert(row + 1, current );

    ui->lstClasses->setCurrentRow(row + 1);
    break;

  }
}

void
FormDeviserVersion::upPressed()
{
  if (mVersion == NULL || mbInitializing) return;

  const QList<QListWidgetItem*>& selected = ui->lstClasses->selectedItems();
  foreach(const QListWidgetItem* item, selected)
  {
    int row = ui->lstClasses->row(item);
    if (row  == 0) continue;

    QListWidgetItem* taken = ui->lstClasses->takeItem(row);
    ui->lstClasses->insertItem(row - 1, taken);
    DeviserClass* current =  mVersion->getElements().takeAt(row);
    mVersion->getElements().insert(row - 1, current );

    ui->lstClasses->setCurrentRow(row - 1);
    break;

  }
}

void
FormDeviserVersion::levelChanged(const QString& level)
{
  if (mVersion == NULL || mbInitializing) return;
  mVersion->setLevel(level.toInt());
}

void
FormDeviserVersion::versionChanged(const QString& version)
{
  if (mVersion == NULL || mbInitializing) return;
  mVersion->setVersion(version.toInt());
}

void
FormDeviserVersion::pkgVersionChanged(const QString& version)
{
  if (mVersion == NULL || mbInitializing) return;
  mVersion->setPkgVersion(version.toInt());

}

void FormDeviserVersion::ignorePackageVersionChanged()
{
  if (mVersion == NULL || mbInitializing) return;
  mVersion->setIgnorePackageVersion(ui->chkIgnorePackageVersion->isChecked());
}


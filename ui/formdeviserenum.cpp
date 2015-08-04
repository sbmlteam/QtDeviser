#include "formdeviserenum.h"
#include "ui_formdeviserenum.h"

#include <set>

#include <QSortFilterProxyModel>

#include <model/deviserenum.h>
#include <model/deviserenumvalue.h>

#include <ui/enummodel.h>

FormDeviserEnum::FormDeviserEnum(QWidget *parent)
  : QWidget(parent)
  , ui(new Ui::FormDeviserEnum)
  , mpValues(NULL)
  , mpValuesFilter(NULL)
  , mbInitializing(true)

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

  mbInitializing = true;

  ui->tblValues->setModel(NULL);
  if (mpValuesFilter != NULL)
    mpValuesFilter->deleteLater();
  if (mpValues != NULL)
    mpValues->deleteLater();


  if (mEnum != NULL)
  {
    ui->txtName->setText(devEnum->getName());

    mpValuesFilter = new QSortFilterProxyModel(this);
    mpValues = new EnumModel(this, &mEnum->getValues());
    mpValuesFilter->setSourceModel(mpValues);
    ui->tblValues->setModel(mpValuesFilter);

  }

  mbInitializing = false;
}

void
FormDeviserEnum::addRow()
{
  if (mEnum == NULL) return;

  mpValues->beginAdding();
  mEnum->createValue();
  mpValues->endAdding();

}

void
FormDeviserEnum::deleteRow()
{
  const QModelIndexList& list = ui->tblValues->selectionModel()->selectedIndexes();
  if (list.count() == 0) return;

  std::set<int> rows;

  foreach(const QModelIndex& index, list)
  {
    rows.insert(index.row());
  }

  std::set<int>::reverse_iterator it = rows.rbegin();
  while (it != rows.rend())
  {
    mpValues->removeAttribute(*it);
    ++it;
  }
}

void
FormDeviserEnum::nameChanged(const QString& name)
{
  if (mEnum == NULL || mbInitializing) return;

  mEnum->setName(name);

}

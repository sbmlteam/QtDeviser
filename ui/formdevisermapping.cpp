#include "formdevisermapping.h"
#include "ui_formdevisermapping.h"

#include <QSortFilterProxyModel>

#include <model/deviserversion.h>
#include <model/devisermapping.h>

#include <ui/mappingmodel.h>

FormDeviserMapping::FormDeviserMapping(QWidget *parent) 
  : QWidget(parent)
  , ui(new Ui::FormDeviserMapping)
  , mVersion(NULL)
  , mpMappings(NULL)
  , mpMappingFilter(NULL)
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

  ui->tblMappings->setModel(NULL);
  if (mpMappingFilter != NULL)
    mpMappingFilter->deleteLater();
  if (mpMappings != NULL)
    mpMappings->deleteLater();

  if (mVersion != NULL)
  {
    version->initializeMappings();

    mpMappingFilter = new QSortFilterProxyModel(this);
    mpMappings = new MappingModel(this, &version->getMappings());
    mpMappingFilter->setSourceModel(mpMappings);
    ui->tblMappings->setModel(mpMappingFilter);

  }

}

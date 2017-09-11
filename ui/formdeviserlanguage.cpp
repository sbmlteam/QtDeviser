#include "formdeviserlanguage.h"
#include "ui_formdeviserlanguage.h"

#include <QSortFilterProxyModel>
#include <set>

#include <model/deviserlanguage.h>

#include <ui/languageversionmodel.h>
#include <ui/dependencymodel.h>

FormDeviserLanguage::FormDeviserLanguage(QWidget *parent)
  : QWidget(parent)
  , ui(new Ui::FormDeviserLanguage)
  , mLanguage(NULL)
  , mpDependencies(NULL)
  , mpDependenciesFilter(NULL)
  , mpVersions(NULL)
  , mpVersionsFilter(NULL)
  , mbInitializing(true)
{
  ui->setupUi(this);
}

FormDeviserLanguage::~FormDeviserLanguage()
{
  delete ui;
}

void
FormDeviserLanguage::initializeFrom(DeviserLanguage* language)
{
  mLanguage = language;

  mbInitializing = true;

  ui->txtBaseClass->clear();
  ui->txtDocumentClass->clear();
  ui->txtLibraryName->clear();
  ui->txtMajor->clear();
  ui->txtMinor->clear();
  ui->txtRevision->clear();
  ui->txtName->clear();
  ui->txtPrefix->clear();

  ui->tblDependencies->setModel(NULL);
  if (mpDependenciesFilter != NULL)
    mpDependenciesFilter->deleteLater();
  if (mpDependencies != NULL)
    mpDependencies->deleteLater();

  ui->tblLanguageVersions->setModel(NULL);
  if (mpVersionsFilter != NULL)
    mpVersionsFilter->deleteLater();
  if (mpVersions != NULL)
    mpVersions->deleteLater();


  if (language != NULL)
  {
    ui->txtBaseClass->setText(language->baseClass());
    ui->txtDocumentClass->setText(language->documentClass());
    ui->txtLibraryName->setText(language->libraryName());
    if (language->libraryMajorVersion() >=0)
    ui->txtMajor->setText(QString::number(language->libraryMajorVersion()));
    if (language->libraryMinorVersion() >=0)
    ui->txtMinor->setText(QString::number(language->libraryMinorVersion()));
    if (language->libraryRevision() >=0)
    ui->txtRevision->setText(QString::number(language->libraryRevision()));
    ui->txtName->setText(language->name());
    ui->txtPrefix->setText(language->prefix());

    ui->chkIsPackage->setChecked(language->isPackage());
    ui->grpDependencies->setEnabled(!language->isPackage());
    ui->grpLanguageVersions->setEnabled(!language->isPackage());
    ui->grpLanguage->setEnabled(!language->isPackage());

    mpDependenciesFilter = new QSortFilterProxyModel(this);
    mpDependencies = new DependencyModel(this, &language->getDependencies());
    mpDependenciesFilter->setSourceModel(mpDependencies);
    ui->tblDependencies->setModel(mpDependenciesFilter);

    mpVersionsFilter = new QSortFilterProxyModel(this);
    mpVersions = new LanguageVersionModel(this, &language->getVersions());
    mpVersionsFilter->setSourceModel(mpVersions);
    ui->tblLanguageVersions->setModel(mpVersionsFilter);


  }

  mbInitializing = false;

}

void FormDeviserLanguage::isPackageToggled()
{
  if (mbInitializing || mLanguage == NULL) return;
  mbInitializing = true;
  mLanguage->setIsPackage(ui->chkIsPackage->isChecked());
  ui->grpDependencies->setEnabled(!mLanguage->isPackage());
  ui->grpLanguageVersions->setEnabled(!mLanguage->isPackage());
  ui->grpLanguage->setEnabled(!mLanguage->isPackage());
  mbInitializing = false;
}

void FormDeviserLanguage::markupNameChanged(QString)
{
  if (mLanguage == NULL || mbInitializing) return;
  mLanguage->setName(ui->txtName->text());
}

void FormDeviserLanguage::prefixChanged(QString)
{
  if (mLanguage == NULL || mbInitializing) return;
  mLanguage->setPrefix(ui->txtPrefix->text());

}

void FormDeviserLanguage::documentClassChanged(QString)
{
  if (mLanguage == NULL || mbInitializing) return;
  mLanguage->setDocumentClass(ui->txtDocumentClass->text());

}

void FormDeviserLanguage::baseClassChanged(QString)
{
  if (mLanguage == NULL || mbInitializing) return;
  mLanguage->setBaseClass(ui->txtBaseClass->text());

}

void FormDeviserLanguage::libraryNameChanged(QString)
{
  if (mLanguage == NULL || mbInitializing) return;
  mLanguage->setLibraryName(ui->txtLibraryName->text());

}

void FormDeviserLanguage::majorChanged(QString)
{
  if (mLanguage == NULL || mbInitializing) return;
  bool valid = false;
  int intValue = ui->txtMajor->text().toInt(&valid);
  if (!valid) return;
  mLanguage->setLibraryRevision(intValue);

}

void FormDeviserLanguage::minorChanged(QString)
{
  if (mLanguage == NULL || mbInitializing) return;
  bool valid = false;
  int intValue = ui->txtMinor->text().toInt(&valid);
  if (!valid) return;
  mLanguage->setLibraryRevision(intValue);

}

void FormDeviserLanguage::revisionChanged(QString)
{
  if (mLanguage == NULL || mbInitializing) return;
  bool valid = false;
  int intValue = ui->txtRevision->text().toInt(&valid);
  if (!valid) return;
  mLanguage->setLibraryRevision(intValue);

}

void FormDeviserLanguage::addVersion()
{
  if (mLanguage == NULL) return;

  mpVersions->beginAdding();
  mLanguage->createVersion();
  mpVersions->endAdding();
}

void FormDeviserLanguage::delVersion()
{
  const QModelIndexList& list = ui->tblLanguageVersions->selectionModel()->selectedIndexes();
  if (list.count() == 0) return;

  std::set<int> rows;

  foreach(const QModelIndex& index, list)
  {
    rows.insert(index.row());
  }

  std::set<int>::reverse_iterator it = rows.rbegin();
  while (it != rows.rend())
  {
    mpVersions->removeVersion(*it);
    ++it;
  }

}

void FormDeviserLanguage::addDependency()
{
  if (mLanguage == NULL) return;

  mpDependencies->beginAdding();
  mLanguage->createDependency();
  mpDependencies->endAdding();
}

void FormDeviserLanguage::delDependency()
{
  const QModelIndexList& list = ui->tblDependencies->selectionModel()->selectedIndexes();
  if (list.count() == 0) return;

  std::set<int> rows;

  foreach(const QModelIndex& index, list)
  {
    rows.insert(index.row());
  }

  std::set<int>::reverse_iterator it = rows.rbegin();
  while (it != rows.rend())
  {
    mpDependencies->removeDependency(*it);
    ++it;
  }
}
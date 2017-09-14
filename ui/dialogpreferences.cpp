#include "dialogpreferences.h"
#include "ui_dialogpreferences.h"

#include <model/devisersettings.h>
#include <model/deviserpackage.h>
#include <util.h>

#include <QFileDialog>
#include <QMessageBox>
#include <QColorDialog>

#include <set>

DialogPreferences::DialogPreferences(DeviserPackage* package, QWidget *parent)
 : QDialog(parent)
 , ui(new Ui::DialogPreferences)
 , mpTypes(NULL)
 , mpTypesFilter(NULL)
 , mpModel(package)
 , mbInitializing(true)
 , mColor(255,0,0,127)
{
  ui->setupUi(this);
}

void
DialogPreferences::loadSettings()
{
  DeviserSettings* settings = DeviserSettings::getInstance();

  ui->txtCMake->setText(settings->getCmakeExecutable());
  ui->txtCompiler->setText(settings->getCompiler());
  ui->txtDependencies->setText(settings->getDependencySourceDir());
  ui->txtDeviserRepo->setText(settings->getDeviserRepository());
  ui->txtLibSBMLSource->setText(settings->getLibSBMLSourceDir());
  ui->txtMikTexBinDir->setText(settings->getMikTexBinDir());
  ui->txtOutputDir->setText(settings->getDefaultOutputDir());
  ui->txtPython->setText(settings->getPythonInterpreter());
  //ui->txtPythonIncludes->setText(settings->getPythonIncludes());
  //ui->txtPythonLib->setText(settings->getPythonLib());
  ui->txtSbmlPkgSpec->setText(settings->getSbmlPkgSpecDir());
  ui->txtSwig->setText(settings->getSwigExecutable());

  mColor = settings->getValidationColor();

  ui->cmdValidationColor->setStyleSheet(QString("QPushButton, QPushButton:hover{"
                                        "  background-color: rgba(%1,%2,%3,%4);"
                                        "  selection-background-color:rgba(%1,%2,%3,%4);"
                                        "  border-width: 1px;"
                                        "  border-color: black;"
                                        "  border: 1px solid gray;"
                                        "}")
                                        .arg(mColor.red())
                                        .arg(mColor.green())
                                        .arg(mColor.blue())
                                        .arg(mColor.alpha()));

  ui->tblUserDefinedTypes->setModel(NULL);
  if (mpTypesFilter != NULL)
    mpTypesFilter->deleteLater();
  if (mpTypes != NULL)
    mpTypes->deleteLater();

  mpTypesFilter = new QSortFilterProxyModel(this);
  mpTypes = new QStandardItemModel(this);
  mpTypes->setHorizontalHeaderLabels( QStringList() << "type");

  foreach(QString type, settings->getUserDefinedTypes())
  {
    mpTypes->appendRow(new QStandardItem( type ));
  }
  mpTypesFilter->setSourceModel(mpTypes);
  ui->tblUserDefinedTypes->setModel(mpTypesFilter);



}

void
DialogPreferences::saveSettings()
{
  DeviserSettings* settings = DeviserSettings::getInstance();

  settings->setCmakeExecutable(ui->txtCMake->text());
  settings->setCompiler(ui->txtCompiler->text());
  settings->setDependencySourceDir(ui->txtDependencies->text());
  settings->setDeviserRepository(ui->txtDeviserRepo->text());
  settings->setLibSBMLSourceDir(ui->txtLibSBMLSource->text());
  settings->setMikTexBinDir(ui->txtMikTexBinDir->text());
  settings->setDefaultOutputDir(ui->txtOutputDir->text());
  settings->setPythonInterpreter(ui->txtPython->text());
  //settings->setPythonIncludes(ui->txtPythonIncludes->text());
  //settings->setPythonLib(ui->txtPythonLib->text());
  settings->setSbmlPkgSpecDir(ui->txtSbmlPkgSpec->text());
  settings->setSwigExecutable(ui->txtSwig->text());
  settings->setValidationColor(mColor);

  QStringList& types = settings->getUserDefinedTypes();
  types.clear();

  for (int i = 0; i < mpTypes->rowCount(); ++i)
  {
    types << mpTypes->data(mpTypes->index(i, 0)).toString();
  }

  settings->saveSettings();

}

void DialogPreferences::addType()
{
  mpTypes->appendRow( new QStandardItem( "newType" ) );
}

void DialogPreferences::delType()
{
  const QModelIndexList& list = ui->tblUserDefinedTypes->selectionModel()->selectedIndexes();
  if (list.count() == 0) return;

  std::set<int> rows;

  QStringList usedTypes = mpModel->getUsedTypes();

  foreach(const QModelIndex& index, list)
  {
    rows.insert(index.row());
    QString type = mpTypesFilter->data(index).toString();
    if (usedTypes.contains(type))
    {
      QMessageBox::critical(this, "Type still in use",
                            QString("The type '%1' cannot be deleted, as it is still used in the model. Please make sure that the type is no longer in use before deleting it.").arg(type),
                            QMessageBox::Ok, QMessageBox::Ok);
      return;
    }
  }



  std::set<int>::reverse_iterator it = rows.rbegin();
  while (it != rows.rend())
  {
    mpTypes->removeRow(*it);
    ++it;
  }
}


DialogPreferences::~DialogPreferences()
{
  delete ui;
}


void
DialogPreferences::browsePython()
{
  QString fileName =
      QFileDialog::getOpenFileName(
        this,
        "Select Python Interpreter", ui->txtPython->text(),
        Util::getExecutableFilter());

  if (fileName.isEmpty())
    return;
  ui->txtPython->setText(fileName);

}

void
DialogPreferences::browseDeviserRepo()
{
  QString dir =
      QFileDialog::getExistingDirectory(
        this,
        "Select Deviser Repo", ui->txtDeviserRepo->text());

  if (dir.isEmpty())
    return;
  ui->txtDeviserRepo->setText(dir);
}

void
DialogPreferences::browseOutputDir()
{
  QString dir =
      QFileDialog::getExistingDirectory(
        this,
        "Select Output dir", ui->txtDeviserRepo->text());

  if (dir.isEmpty())
    return;
  ui->txtOutputDir->setText(dir);

}

void
DialogPreferences::browseSbmlPkgSpec()
{
  QString dir =
      QFileDialog::getExistingDirectory(
        this,
        "Select SBML Pkg Spec dir", ui->txtSbmlPkgSpec->text());

  if (dir.isEmpty())
    return;
  ui->txtSbmlPkgSpec->setText(dir);

}

void
DialogPreferences::browseMikTex()
{
  QString dir =
      QFileDialog::getExistingDirectory(
        this,
        "Select MikTex bin dir", ui->txtMikTexBinDir->text());

  if (dir.isEmpty())
    return;
  ui->txtMikTexBinDir->setText(dir);
}

void
DialogPreferences::browseLibSBML()
{
  QString dir =
      QFileDialog::getExistingDirectory(
        this,
        "Select LibSBML dir", ui->txtLibSBMLSource->text());

  if (dir.isEmpty())
    return;
  ui->txtLibSBMLSource->setText(dir);
}

void
DialogPreferences::selectCompiler()
{
  QString fileName =
      QFileDialog::getOpenFileName(
        this,
        "Select Compiler", ui->txtCompiler->text(),
        Util::getExecutableFilter());

  if (fileName.isEmpty())
    return;
  ui->txtCompiler->setText(fileName);

}

void
DialogPreferences::browseCMakeExecutable()
{
  QString fileName =
      QFileDialog::getOpenFileName(
        this,
        "Select CMake executable", ui->txtCMake->text(),
        Util::getExecutableFilter());

  if (fileName.isEmpty())
    return;
  ui->txtCMake->setText(fileName);

}

void
DialogPreferences::browseDependencies()
{
  QString dir =
      QFileDialog::getExistingDirectory(
        this,
        "Select libSBML Dependencies dir", ui->txtDependencies->text());

  if (dir.isEmpty())
    return;
  ui->txtDependencies->setText(dir);

}

void
DialogPreferences::browseSWIG()
{
  QString fileName =
      QFileDialog::getOpenFileName(
        this,
        "Select SWIG executable", ui->txtSwig->text(),
        Util::getExecutableFilter());

  if (fileName.isEmpty())
    return;
  ui->txtSwig->setText(fileName);

}

void
DialogPreferences::browsePythonInclude()
{
  //QString dir =
  //    QFileDialog::getExistingDirectory(
  //      this,
  //      "Select libSBML include dir", ui->txtPythonIncludes->text());

  //if (dir.isEmpty())
  //  return;
  //ui->txtPythonIncludes->setText(dir);

}

void
DialogPreferences::browsePythonLib()
{
  //QString fileName =
  //    QFileDialog::getOpenFileName(
  //      this,
  //      "Select Python lib", ui->txtPythonLib->text(),
  //      Util::getLibFilter());

  //if (fileName.isEmpty())
  //  return;
  //ui->txtPythonLib->setText(fileName);
}

void
DialogPreferences::selectValidationColor()
{
  mColor = QColorDialog::getColor(mColor, this, "Select Validation Color", QColorDialog::ShowAlphaChannel);
  ui->cmdValidationColor->setStyleSheet(QString("QPushButton, QPushButton:hover{"
                                        "  background-color: rgba(%1,%2,%3,%4);"
                                        "  selection-background-color:rgba(%1,%2,%3,%4);"
                                        "  border-width: 1px;"
                                        "  border-color: black;"
                                        "  border: 1px solid gray;"
                                        "}")
                                        .arg(mColor.red())
                                        .arg(mColor.green())
                                        .arg(mColor.blue())
                                        .arg(mColor.alpha()));

}


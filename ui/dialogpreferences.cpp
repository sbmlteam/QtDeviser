#include "dialogpreferences.h"
#include "ui_dialogpreferences.h"

#include <model/devisersettings.h>
#include <util.h>

#include <QFileDialog>

DialogPreferences::DialogPreferences(QWidget *parent)
 : QDialog(parent)
 , ui(new Ui::DialogPreferences)
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
  ui->txtPythonIncludes->setText(settings->getPythonIncludes());
  ui->txtPythonLib->setText(settings->getPythonLib());
  ui->txtSbmlPkgSpec->setText(settings->getSbmlPkgSpecDir());
  ui->txtSwig->setText(settings->getSwigExecutable());

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
  settings->setPythonIncludes(ui->txtPythonIncludes->text());
  settings->setPythonLib(ui->txtPythonLib->text());
  settings->setSbmlPkgSpecDir(ui->txtSbmlPkgSpec->text());
  settings->setSwigExecutable(ui->txtSwig->text());

  settings->saveSettings();

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
  QString dir =
      QFileDialog::getExistingDirectory(
        this,
        "Select libSBML include dir", ui->txtPythonIncludes->text());

  if (dir.isEmpty())
    return;
  ui->txtPythonIncludes->setText(dir);

}

void
DialogPreferences::browsePythonLib()
{
  QString fileName =
      QFileDialog::getOpenFileName(
        this,
        "Select Python lib", ui->txtPythonLib->text(),
        Util::getLibFilter());

  if (fileName.isEmpty())
    return;
  ui->txtPythonLib->setText(fileName);
}


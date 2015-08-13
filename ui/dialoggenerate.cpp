#include "dialoggenerate.h"
#include "ui_dialoggenerate.h"

#include <QDir>
#include <QUrl>
#include <QProcess>
#include <QFileDialog>
#include <QStringList>
#include <QDesktopServices>

#include <model/devisersettings.h>
#include <model/deviserpackage.h>

DialogGenerate::DialogGenerate(QWidget *parent)
  : QDialog(parent)
  , ui(new Ui::DialogGenerate)
  , mPackage(NULL)
  , mpProcess(NULL)
{
  ui->setupUi(this);
}

DialogGenerate::~DialogGenerate()
{
  delete ui;
  if (mpProcess != NULL)
  {
    if (mpProcess->state() == QProcess::Running)
      mpProcess->kill();

    mpProcess->deleteLater();
  }
}

void
DialogGenerate::loadModel(DeviserPackage* package, const QString& fileName)
{
  mPackage = package;

  ui->txtOutDir->setText(
        DeviserSettings::getInstance()->getDefaultOutputDir());
  ui->txtPackageName->setText(package->getName());
  ui->txtPackageFile->setText(fileName);  
}

void
DialogGenerate::testLibSBML()
{

}

void
DialogGenerate::removeFromSourceDir()
{

}

void
DialogGenerate::openOutputDir()
{
  QUrl url("file:///" + ui->txtOutDir->text().replace("\\", "/"), QUrl::TolerantMode);
  QDesktopServices::openUrl(url);
}

void
DialogGenerate::generateTex()
{
  ui->plainTextEdit->clear();
  addMessage("Generating Latex");
  addMessage("================");
  addMessage();

  QString outDir = ui->txtOutDir->text();
  QDir out = QDir(outDir);
  if (!out.exists())
    out.mkdir(".");

  QString packageName = ui->txtPackageName->text();
  QString packageDesc = ui->txtPackageFile->text();

  if (outDir.isEmpty() || !QDir(outDir).exists())
  {
    addMessage("Error: No output dir specified, or output dir does not exist.");
    return;
  }

  QString lowerCasePackageName = packageName.toLower();
  QString dest = outDir + "/" + lowerCasePackageName + "-spec";
  QDir destDir = QDir(dest);

  if (!destDir.exists())
    destDir.mkdir(".");

  QString deviser = DeviserSettings::getInstance()->getDeviserRepository() + "/generator/deviser.py";
  deviser = deviser.replace("\\", "/");

  QStringList args;
  args << deviser
       << "--latex"
       << packageDesc;

  mpProcess = new QProcess();
  mpProcess->setWorkingDirectory(dest);

  mpProcess->start(DeviserSettings::getInstance()->getPythonInterpreter(),
                   args);

  connect(mpProcess, SIGNAL(finished(int,QProcess::ExitStatus)),
          this, SLOT(finished(int,QProcess::ExitStatus)));
  connect(mpProcess, SIGNAL(readyReadStandardError()),
          this, SLOT(readyOutput()));
  connect(mpProcess, SIGNAL(error(QProcess::ProcessError)),
          this, SLOT(readyOutput()));


  setEnabled(false);  

}

void
DialogGenerate::error(QProcess::ProcessError)
{
  setEnabled(true);
  addMessage(mpProcess->readAllStandardError());
  addMessage();

}

void
DialogGenerate::generatePackageCode()
{
  ui->plainTextEdit->clear();
  addMessage("Generating Latex");
  addMessage("================");
  addMessage();

  QString outDir = ui->txtOutDir->text();
  QDir out = QDir(outDir);
  if (!out.exists())
    out.mkdir(".");

  QString packageName = ui->txtPackageName->text();
  QString packageDesc = ui->txtPackageFile->text();

  if (outDir.isEmpty() || !QDir(outDir).exists())
  {
    addMessage("Error: No output dir specified, or output dir does not exist.");
    return;
  }

  QString deviser = DeviserSettings::getInstance()->getDeviserRepository() + "/generator/deviser.py";
  deviser = deviser.replace("\\", "/");

  QStringList args;
  args << deviser
       << "-g"
       << packageDesc;

  mpProcess = new QProcess();
  mpProcess->setWorkingDirectory(outDir);

  mpProcess->start(DeviserSettings::getInstance()->getPythonInterpreter(),
                   args);

  connect(mpProcess, SIGNAL(finished(int,QProcess::ExitStatus)),
          this, SLOT(finished(int,QProcess::ExitStatus)));
  connect(mpProcess, SIGNAL(readyReadStandardError()),
          this, SLOT(readyOutput()));
  connect(mpProcess, SIGNAL(error(QProcess::ProcessError)),
          this, SLOT(readyOutput()));


  setEnabled(false);
}

void
DialogGenerate::addMessage(const QString& message)
{

  ui->plainTextEdit->moveCursor (QTextCursor::End);
  ui->plainTextEdit->insertPlainText (message);
  ui->plainTextEdit->insertPlainText ("\n");
  ui->plainTextEdit->moveCursor (QTextCursor::End);
}


void
DialogGenerate::finished(int /*exitCode*/, QProcess::ExitStatus /*exitStatus*/)
{
  addMessage(mpProcess->readAllStandardOutput());
  addMessage(mpProcess->readAllStandardError());
  addMessage();
  addMessage("DONE");
  addMessage();
  setEnabled(true);


}

void
DialogGenerate::readyOutput()
{
  if (mpProcess == NULL) return;

  addMessage(mpProcess->readAll());
}

void
DialogGenerate::compileTex()
{

}

void
DialogGenerate::compileLibSBML()
{

}

void
DialogGenerate::compileDependencies()
{

}

void
DialogGenerate::browseOutputDir()
{
  QString dir =
      QFileDialog::getExistingDirectory(
        this,
        "Select Output dir", ui->txtOutDir->text());

  if (dir.isEmpty())
    return;
  ui->txtOutDir->setText(dir);
}

void
DialogGenerate::addToSourceDir()
{

}

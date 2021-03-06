#include "dialoggenerate.h"
#include "ui_dialoggenerate.h"

#include <QDir>
#include <QUrl>
#include <QFile>
#include <QProcess>
#include <QEventLoop>
#include <QTextStream>
#include <QFileDialog>
#include <QStringList>
#include <QMessageBox>
#include <QApplication>
#include <QDesktopServices>
#include <QProcessEnvironment>

#include <model/deviserenum.h>
#include <model/deviserclass.h>
#include <model/deviserplugin.h>
#include <model/deviserpackage.h>
#include <model/devisersettings.h>

#include <ui/flowlayout.h>
#include <ui/dialoguml.h>

#include <util.h>


DialogGenerate::DialogGenerate(QWidget *parent)
  : QDialog(parent)
  , ui(new Ui::DialogGenerate)
  , mPackage(NULL)
  , mVersion(NULL)
  , mpProcess(NULL)
  , workerThread(this)
  , mLastAction(OTHER)
{
  ui->setupUi(this);

  connect (&workerThread, SIGNAL(finished(int)), this, SLOT(finished(int)));

  FlowLayout::applyToWidget(ui->tabIntegration);

  ui->cmdTestLibSBML->setVisible(false);

}

DialogGenerate::~DialogGenerate()
{
  delete ui;
  workerThread.quit();
  workerThread.wait();

  if (mpProcess != NULL)
  {
    if (mpProcess->state() == QProcess::Running)
      mpProcess->kill();

    mpProcess->deleteLater();
  }
}

void
DialogGenerate::loadModel(DeviserPackage* package,
                          DeviserVersion* version,
                          const QString& fileName)
{
  mPackage = package;
  mVersion = version;

  ui->txtOutDir->setText(
        DeviserSettings::getInstance()->getDefaultOutputDir());
  ui->txtPackageName->setText(package->getName());
  ui->txtPackageFile->setText(fileName);
}

void DialogGenerate::createImagesIn(const QString &destDir)
{

  foreach(DeviserVersion* version, mPackage->getVersions())
  {
    const QString& yuml = version->toYuml();
    downloadFiles(yuml, QString("%1/%2_version_%3_complete")
                  .arg(destDir)
                  .arg(mPackage->getName().toLower())
                  .arg(version->getPkgVersion()));

    foreach(DeviserClass* element, version->getElements())
    {
      const QString& yuml = element->toYuml();
      downloadFiles(yuml, QString("%1/%2_%3_uml")
                    .arg(destDir)
                    .arg(mPackage->getName().toLower())
                    .arg(element->getName().toLower()));
    }

    foreach(DeviserPlugin* plugin, version->getPlugins())
    {
      const QString& yuml = plugin->toYuml();
      downloadFiles(yuml, QString("%1/%2_extended_%3_uml")
                    .arg(destDir)
                    .arg(mPackage->getName().toLower())
                    .arg(plugin->getExtensionPoint().toLower()));
    }

    foreach(DeviserEnum* element, version->getEnums())
    {
      const QString& yuml = element->toYuml();
      downloadFiles(yuml, QString("%1/%2_type_enum_%3_uml")
                    .arg(destDir)
                    .arg(mPackage->getName().toLower())
                    .arg(element->getName().toLower()));
    }
  }
}

void DialogGenerate::downloadFiles(const QString &yuml, const QString &baseName)
{
  QEventLoop loop1;
  QEventLoop loop2;
  DialogUML *uml = new DialogUML(this);

  connect(uml, SIGNAL(finishedUpdate()), &loop1, SLOT(quit()));
  connect(uml, SIGNAL(finishedDownload()), &loop2, SLOT(quit()));
  uml->loadYuml(yuml);
  QFileInfo info(baseName);
  addMessage("...Uploading Yuml for: " + info.baseName() );
  loop1.exec();

  uml->exportImage(baseName + ".pdf","pdf");
  addMessage("...Downloading PDF");

  loop2.exec();
  uml->exportImage(baseName + ".png","png");
  addMessage("...Downloading PNG");
  loop2.exec();

  addMessage("...DONE");
}

void
DialogGenerate::testLibSBML()
{
  ui->plainTextEdit->clear();
  addMessage("testing libsbml");
  addMessage("========================");
  addMessage("not yet implemented .... ");

}

void
DialogGenerate::removeFromSourceDir()
{
  ui->plainTextEdit->clear();
  addMessage("Remove Package From Source");
  addMessage("==========================");
  addMessage();

  QString libSBMLSourceDir = DeviserSettings::getInstance()->getLibSBMLSourceDir();
  QString packageName = ui->txtPackageName->text();

  if (!QDir(libSBMLSourceDir).exists())
  {
    addMessage("Error: Missing source dir.");
    return ;
  }

  QString lowerFirst = Util::lowerFirst( packageName );

  Util::removeDir( libSBMLSourceDir + "/" + lowerFirst + "-package.cmake");
  Util::removeDir(libSBMLSourceDir + "/" + "src" + "/" + lowerFirst + "-package.cmake");
  Util::removeDir(libSBMLSourceDir + "/" + "src/sbml/packages" + "/" + lowerFirst + "-register.cxx");
  Util::removeDir(libSBMLSourceDir + "/" + "src/sbml/packages" + "/" + lowerFirst + "-register.h");
  Util::removeDir(libSBMLSourceDir + "/" + "src/sbml/packages" + "/" + lowerFirst );
  Util::removeDir(libSBMLSourceDir + "/" + "examples" + "/" + lowerFirst + "-package.cmake");
  Util::removeDir(libSBMLSourceDir + "/" + "examples/c++" + "/" + lowerFirst);

  Util::removeDir(libSBMLSourceDir + "/" + "src/bindings" , lowerFirst);

  addMessage();
  addMessage("DONE");
  addMessage();

}

void
DialogGenerate::openOutputDir()
{
  QUrl url("file:///" + ui->txtOutDir->text().replace("\\", "/"), QUrl::TolerantMode);
  QDesktopServices::openUrl(url);
}

void
DialogGenerate::generateTex(bool withFigures)
{
  mLastAction = GENERATE_TEX;

  ui->plainTextEdit->clear();
  addMessage("Generating LaTex");
  addMessage("================");
  addMessage();

  QString outDir = ui->txtOutDir->text();
  QDir out(outDir);
  if (!out.exists())
    if (!out.mkdir("."))
    {
      QDir().mkdir(ui->txtOutDir->text());
    }

  QString packageName = ui->txtPackageName->text();
  QString packageDesc = ui->txtPackageFile->text();

  if (outDir.isEmpty() || !QDir(outDir).exists())
  {
    addMessage("Error: No output dir specified, or output dir does not exist.");
    return;
  }


  QString deviserRepo = DeviserSettings::getInstance()->getDeviserRepository();
  if (deviserRepo.isEmpty() || !QDir(deviserRepo).exists())
  {
    addMessage("Error: No deviser repository dir specified, or deviser repository dir does not exist.");
    return;
  }

  QString python = DeviserSettings::getInstance()->getPythonInterpreter();
  if (python.isEmpty())
  {
    addMessage("Error: No python interpreter specified.");
    return;
  }


  QString lowerCasePackageName = packageName.toLower();
  QString dest = outDir + "/" + lowerCasePackageName + "-spec";
  QDir destDir(dest);

  if (!destDir.exists())
    if (!destDir.mkdir("."))
    {
      QDir().mkdir(dest);
    }

  if (withFigures)
  {
    QString figures = dest + "/figures";
    QDir figuresDir(figures);
    if (!figuresDir.exists())
      if (!figuresDir.mkdir("."))
      {
        QDir().mkdir(figures);
      }

    createImagesIn(figures);
  }

  QString deviser = DeviserSettings::getInstance()->getDeviserRepository()
      + "/generator/deviser.py";
  deviser = deviser.replace("\\", "/");

  QStringList args;
  args << deviser
       << "--latex"
       << packageDesc;

  mpProcess = new QProcess();
  mpProcess->setWorkingDirectory(dest);

  mpProcess->moveToThread(&workerThread);
  workerThread.setProcess(mpProcess,
                          DeviserSettings::getInstance()->getPythonInterpreter(),
                          args);
  workerThread.start();

  toggleControls(false);

}

void DialogGenerate::generateTexWithFigures()
{
  generateTex(true);
}

void
DialogGenerate::error(QProcess::ProcessError)
{
  while(mpProcess->canReadLine())
    addMessage(mpProcess->readLine());
  addMessage();
  toggleControls(true);
}

void
DialogGenerate::toggleControls(bool enable) const
{
  ui->widgetControls->setEnabled(enable);
  ui->widgetsButtons->setEnabled(enable);
  ui->widgetTitle->setEnabled(enable);
}

void
DialogGenerate::generatePackageCode()
{
  mLastAction = GENERATE_PACKAGE_CODE;


  ui->plainTextEdit->clear();
  addMessage("Generating Package Code");
  addMessage("=======================");
  addMessage();

  QString outDir = ui->txtOutDir->text();
  QDir out = QDir(outDir);
  if (!out.exists())
    if (!out.mkdir("."))
      QDir().mkdir(outDir);

  QString packageDesc = ui->txtPackageFile->text();

  if (outDir.isEmpty() || !QDir(outDir).exists())
  {
    addMessage("Error: No output dir specified, or output dir does not exist.");
    return;
  }

  QString deviserRepo = DeviserSettings::getInstance()->getDeviserRepository();
  if (deviserRepo.isEmpty() || !QDir(deviserRepo).exists())
  {
    addMessage("Error: No deviser repository dir specified, or deviser repository dir does not exist.");
    return;
  }

  QString python = DeviserSettings::getInstance()->getPythonInterpreter();
  if (python.isEmpty())
  {
    addMessage("Error: No python interpreter specified.");
    return;
  }

  QString deviser =
      DeviserSettings::getInstance()->getDeviserRepository()
      + "/generator/deviser.py";
  deviser = deviser.replace("\\", "/");

  QStringList args;
  args << deviser
       << "-g"
       << packageDesc;

  mpProcess = new QProcess();
  mpProcess->setWorkingDirectory(outDir);


  mpProcess->moveToThread(&workerThread);
  workerThread.setProcess(mpProcess,
                          DeviserSettings::getInstance()->getPythonInterpreter(),
                          args);
  workerThread.start();

  toggleControls(false);
}

void
DialogGenerate::addMessage(const QString& message)
{
  ui->plainTextEdit->moveCursor (QTextCursor::End);
  ui->plainTextEdit->insertPlainText (message);
  if (!message.endsWith('\n'))
  ui->plainTextEdit->insertPlainText ("\n");
  ui->plainTextEdit->moveCursor (QTextCursor::End);  
}


void
DialogGenerate::finished(int code /*= 0*/)
{
  while(mpProcess->canReadLine())
    addMessage(mpProcess->readLine());
  addMessage();

  if (mLastAction != GENERATE_PACKAGE_CODE &&
      mLastAction != GENERATE_TEX)
  {
    addMessage("DONE");
    addMessage();
    toggleControls(true);
    mLastAction = OTHER;
    return;
  }


  switch(code)
  {
  case 1:
    addMessage("Error: Failed to read file.");
    break;
  case 2:
    addMessage("Error: Missing function argument.");
    break;
  case 3:
    addMessage("Error: Invalid function arguments.");
    break;
  case 4:
    addMessage("Error: Parsing error.");
    break;
  case 5:
    addMessage("Warning: Unknown type used.");
    break;
  case 6:
    addMessage("Error: Unknown error - please report.");
    break;

  case 0:
  default:
    addMessage("DONE");
    break;
  }

  addMessage();
  toggleControls(true);
  mLastAction = OTHER;

}

void
DialogGenerate::readyOutput()
{
  if (mpProcess == NULL) return;

  while(mpProcess->canReadLine())
    addMessage(mpProcess->readLine());

}

void
DialogGenerate::compileTex()
{
  mLastAction = COMPILE_TEX;

  ui->plainTextEdit->clear();
  addMessage("Compile Latex");
  addMessage("=============");
  addMessage();

  QString outDir = ui->txtOutDir->text();
  QString packageName = ui->txtPackageName->text();

  QDir qoutDir(outDir);

  if (outDir.isEmpty() || !qoutDir.exists())
  {
    addMessage("Error: No output dir specified, or output dir does not exist.");
    return;
  }

  QString lowerCasePackageName = packageName.toLower();
  QDir destDir (outDir + "/" + lowerCasePackageName + "-spec");
  if (!destDir.exists())
  {
    addMessage("Error: Please 'generate latex' first before trying to compile. (latex dir not present)");
    return;
  }

  if (!QFile( destDir.absolutePath() + "/" + "apdx-validation.tex").exists() ||
      !QFile( destDir.absolutePath() + "/" + "body.tex").exists() ||
      !QFile( destDir.absolutePath() + "/" + "macros.tex").exists())
  {
    addMessage("Error: Please 'generate latex' first before trying to compile, that should have generated three files: 'body.tex', 'macros.tex' and 'apdx-validation.tex' however those files are not present.");
    return;
  }

  QFile pdfFile (destDir.absolutePath() + "/" + "main.pdf");
  if (pdfFile.exists())
  {
    if (!pdfFile.remove())
    {
      addMessage("Error: The PDF is already present and cannot be overwritten. Please ensure that it is not open in a PDF viewer.");
      return;
    }
  }

  QFile mainFile (destDir.absolutePath() + "/" + "main.tex");
  if (!mainFile .exists())
  {
    QFile templateFile(":/main.tex");
    templateFile.open(QIODevice::ReadOnly);
    QString mainText = templateFile.readAll();
    templateFile.close();

    QString fullPackageName =
        mPackage != NULL && !mPackage->getFullName().isEmpty() ?
          mPackage->getFullName() :
          lowerCasePackageName;

    int coreLevel = mVersion != NULL ?
          mVersion->getLevel() :
          mPackage != NULL && mPackage->getVersions().count() > 0 ?
          mPackage->getVersions().at(0)->getLevel() :
          3;
    int coreVersion = mVersion != NULL ?
          mVersion->getVersion() :
          mPackage != NULL && mPackage->getVersions().count() > 0 ?
          mPackage->getVersions().at(0)->getVersion() :
          1;
    int packageVersion = mVersion != NULL ?
          mVersion->getPkgVersion() :
          mPackage != NULL && mPackage->getVersions().count() > 0 ?
          mPackage->getVersions().at(0)->getPkgVersion() :
          1;

    mainText = mainText.replace("@@PACKAGENAME@@", lowerCasePackageName)
        .replace("@@FULL_PACKAGE_NAME@@", fullPackageName)
        .replace("@@CORE_LEVEL@@", QString::number(coreLevel))
        .replace("@@CORE_VERSION@@", QString::number(coreVersion))
        .replace("@@PACKAGE_VERSION@@", QString::number(packageVersion))
        ;


    mainFile.open(QIODevice::WriteOnly);
    mainFile.write(mainText.toUtf8());
    mainFile.close();

  }

  QString mikTexDir = DeviserSettings::getInstance()->getMikTexBinDir();

  if (Util::isWindows() && !QFile(mikTexDir + "/" + "texify.exe").exists())
  {
    if (mikTexDir.isEmpty() || !QDir(mikTexDir).exists())
    {
      addMessage("Error: miktex dir is empty or does not exist.");
    }
    else
    {
      addMessage("Error: texify.exe was not present in '" + mikTexDir + "' please ensure you have the path entered correctly.");
    }
    return;
  }


  QStringList args;
  QString executable;
  if (Util::isWindows())
  {
    executable = mikTexDir + "/"  + "texify.exe";
    args
        << "--pdf"
        << "--batch";
  }
  else
  {
    executable = mikTexDir + "/"  + "pdflatex";
    args
        << "-interaction=nonstopmode";
  }
  args << "main.tex";

  mpProcess = new QProcess();
  mpProcess->setWorkingDirectory(destDir.absolutePath());

  QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
  env.remove("TEXINPUTS");
  env.remove("BIBINPUTS");

  QString sbmlPkgSpecDir = DeviserSettings::getInstance()->getSbmlPkgSpecDir();
  if (sbmlPkgSpecDir.endsWith("\\"))
    sbmlPkgSpecDir = sbmlPkgSpecDir.left(sbmlPkgSpecDir.length()-1) + "//";
  if (!sbmlPkgSpecDir.endsWith("//"))
    sbmlPkgSpecDir += "//";

  if (Util::isWindows() && env.contains("TEXINPUTS"))
  {
    sbmlPkgSpecDir = env.value("TEXINPUTS") + ":" + sbmlPkgSpecDir;
  }
  else if (!Util::isWindows())
  {
    sbmlPkgSpecDir = "/usr/share/texmf//:/usr/share/texlive//:" + sbmlPkgSpecDir;
  }

  if (!Util::isWindows())
    sbmlPkgSpecDir += ":.";

  env.insert("TEXINPUTS", sbmlPkgSpecDir);
  env.insert("BIBINPUTS", sbmlPkgSpecDir);
  mpProcess->setProcessEnvironment(env);

  mpProcess->moveToThread(&workerThread);
  workerThread.setProcess(mpProcess, executable, args);
  workerThread.start();

  toggleControls(false);

}

void
DialogGenerate::compileLibSBML()
{
  mLastAction = COMPILE_LIBSBML;

  ui->plainTextEdit->clear();
  addMessage("Compiling LibSBML");
  addMessage("=================");
  addMessage();

  QString outDir = ui->txtOutDir->text();
  QDir qoutDir(outDir);


  if (outDir.isEmpty() || !qoutDir.exists())
  {
    addMessage("Error: No output dir specified, or output dir does not exist.");
    return;
  }

  QString dependencySourceDir = DeviserSettings::getInstance()->getDependencySourceDir();

  if (!QDir(dependencySourceDir).exists())
  {
    addMessage("Error: The dependencies source dir does not exist, please validate your settings.");
    return;
  }

  if (!QFile(DeviserSettings::getInstance()->getCmakeExecutable()).exists())
  {
    addMessage("Error: The CMake executable does not exist, please validate your settings.");
    return;
  }

  if (Util::isWindows() && !QFile(DeviserSettings::getInstance()->getVsBatchFile()).exists())
  {
    addMessage("Error: The Visual studio file does not exist, please validate your settings.");
    return;
  }

  if (!QDir(outDir + "/" + "install_dependencies").exists())
  {
    addMessage("Error: The dependency install dir does not exist, please compile dependencies first.");
    return;
  }

  QString packageName = ui->txtPackageName->text();
  QString buildDir(outDir + "/" + "build_" + packageName.toLower() + "_package");

  if (!QDir(buildDir).exists())
    if (!QDir(buildDir).mkdir("."))
      QDir().mkdir(buildDir);


  QString file;

  if (Util::isWindows())
  {
    file = buildDir + "/" + "script.bat";

    QFile script(file);
    script.open(QIODevice::WriteOnly);
    QTextStream stream(&script);

    stream << "@echo off" << endl;
    if (DeviserSettings::getInstance()->getCmakeExecutable().isEmpty())
      stream << "SET CMAKE=cmake" << endl;
    else
      stream << "SET CMAKE=" << DeviserSettings::getInstance()->getCmakeExecutable() << endl;

    stream << "call \"" << DeviserSettings::getInstance()->getVsBatchFile() << "\"" << endl;

    stream << "\"%CMAKE%\" -G \"NMake Makefiles\" "
              "-DCMAKE_BUILD_TYPE=Release "
              "-DSWIG_EXECUTABLE=\"" << DeviserSettings::getInstance()->getSwigExecutable() << "\" "
              "-DWITH_PYTHON=ON "
              "-DPYTHON_EXECUTABLE=\"" << DeviserSettings::getInstance()->getPythonInterpreter() << "\" "
              "-DPYTHON_LIBRARY=\"" << DeviserSettings::getInstance()->getPythonLib() <<  "\" "
              "-DPYTHON_INCLUDE_DIR=\"" << DeviserSettings::getInstance()->getPythonIncludes() << "\" "
              "-DLIBSBML_DEPENDENCY_DIR=\"" << outDir + "/" + "install_dependencies" <<  "\" "
              "-DENABLE_LAYOUT=ON "
              "-DENABLE_" << packageName.toUpper() << "=ON "
              "-DCMAKE_INSTALL_PREFIX=../install__" << packageName.toLower() << "_package "
              "\""  << DeviserSettings::getInstance()->getLibSBMLSourceDir() << "\""
           << endl;

    stream << "nmake" << endl;
    stream << "nmake install" << endl;

    script.close();

  }
  else
  {
    file = buildDir + "/" + "script.sh";

    QFile script(file);
    script.open(QIODevice::WriteOnly);
    QTextStream stream(&script);

    stream << "cd \"" << buildDir << "\"" << endl;

    if (DeviserSettings::getInstance()->getCmakeExecutable().isEmpty())
      stream << "CMAKE=cmake" << endl;
    else
      stream << "CMAKE=" << DeviserSettings::getInstance()->getCmakeExecutable() << endl;

    stream << "$CMAKE -G \"Unix Makefiles\" "
              "-DCMAKE_BUILD_TYPE=Release "
              "-DSWIG_EXECUTABLE=\"" << DeviserSettings::getInstance()->getSwigExecutable() << "\" "
              "-DWITH_PYTHON=ON "
              "-DPYTHON_EXECUTABLE=\"" << DeviserSettings::getInstance()->getPythonInterpreter() << "\" "
              "-DPYTHON_LIBRARY=\"" << DeviserSettings::getInstance()->getPythonLib() <<  "\" "
              "-DPYTHON_INCLUDE_DIR=\"" << DeviserSettings::getInstance()->getPythonIncludes() << "\" "
              "-DLIBSBML_DEPENDENCY_DIR=\"" << outDir + "/" + "install_dependencies" <<  "\" "
              "-DENABLE_LAYOUT=ON "
              "-DENABLE_" << packageName.toUpper() << "=ON "
              "-DCMAKE_INSTALL_PREFIX=../install__" << packageName.toLower() << "_package "
              "\""  << DeviserSettings::getInstance()->getLibSBMLSourceDir() << "\""
           << endl;

    stream << "make" << endl;
    stream << "make install" << endl;

    script.close();

    script.setPermissions(QFile::ExeGroup | QFile::ReadGroup |
                          QFile::ExeOther | QFile::ReadOther |
                          QFile::ExeUser | QFile::ReadOwner );

  }

  mpProcess = new QProcess();
  mpProcess->setWorkingDirectory(buildDir);

  if (Util::isWindows())
  {
    mpProcess->moveToThread(&workerThread);
    workerThread.setProcess(mpProcess, file, QStringList());
    workerThread.start();

  }
  else
  {
    QStringList args;
    args << "-c" << file;

    mpProcess->moveToThread(&workerThread);
    workerThread.setProcess(mpProcess, "bash", args);
    workerThread.start();

  }

  toggleControls(false);

}

void
DialogGenerate::compileDependencies()
{
  mLastAction = COMPILE_DEPENDENCIES;

  ui->plainTextEdit->clear();

  addMessage("Compile Dependencies");
  addMessage("====================");
  addMessage();

  QString outDir = ui->txtOutDir->text();
  QDir qoutDir(outDir);


  if (outDir.isEmpty() || !qoutDir.exists())
  {
    addMessage("Error: No output dir specified, or output dir does not exist.");
    return;
  }

  QString dependencySourceDir = DeviserSettings::getInstance()->getDependencySourceDir();

  if (dependencySourceDir.isEmpty() || !QDir(dependencySourceDir).exists())
  {
    addMessage("Error: The dependencies source dir does not exist, please validate your settings.");
    return ;
  }

  if (!QFile(DeviserSettings::getInstance()->getCmakeExecutable()).exists())
  {
    addMessage("Error: The CMake executable does not exist, please validate your settings.");
    return;
  }

  if (Util::isWindows() && !QFile(DeviserSettings::getInstance()->getVsBatchFile()).exists())
  {
    addMessage("Error: The Visual studio file does not exist, please validate your settings.");
    return ;
  }

  QString buildDir ( outDir + "/" + "build_dependencies" );

  if (!QDir(buildDir).exists())
    if (!QDir(buildDir).mkdir("."))
      QDir().mkdir(buildDir);


  QString file;

  if (Util::isWindows())
  {
    file = buildDir + "/" +  "script.bat";

    QFile script (file);
    script.open(QIODevice::WriteOnly);
    QTextStream stream(&script);

    stream << "@echo off" << endl;
    stream << "call \"" << DeviserSettings::getInstance()->getVsBatchFile() << "\"" << endl;
    stream << "cmake -G \"NMake Makefiles\" -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=../install_dependencies  \""
           << dependencySourceDir << "\"" << endl;
    stream << "nmake" << endl;
    stream << "nmake install" << endl;

    script.close();

  }
  else
  {
    file = buildDir + "/" + "script.sh";

    QFile script (file);
    script.open(QIODevice::WriteOnly);
    QTextStream stream(&script);

    stream << "cd  \"" << buildDir << "\"" << endl;
    stream << "cmake -G \"Unix Makefiles\" -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=../install_dependencies  \""
    << dependencySourceDir << "\"" << endl;
    stream << "make" << endl;
    stream << "make install" << endl;

    script.close();
    script.setPermissions(QFile::ExeGroup | QFile::ReadGroup | QFile::WriteGroup |
                          QFile::ExeOther | QFile::ReadOther | QFile::WriteOther |
                          QFile::ExeUser | QFile::ReadOwner | QFile::WriteOwner );

  }

  mpProcess = new QProcess();
  mpProcess->setWorkingDirectory(buildDir);

  if (Util::isWindows())
  {
    mpProcess->moveToThread(&workerThread);
    workerThread.setProcess(mpProcess, file, QStringList());
    workerThread.start();

  }
  else
  {
    QStringList args;
    args << "-c" << file;

    mpProcess->moveToThread(&workerThread);
    workerThread.setProcess(mpProcess, "bash", args);
    workerThread.start();

  }

  toggleControls(false);

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
  ui->plainTextEdit->clear();
  addMessage("Adding Package to Source");
  addMessage("========================");
  addMessage();

  QString outDir = ui->txtOutDir->text();
  QString packageName = ui->txtPackageName->text();
  QDir qOutDir(outDir);

  if (outDir.isEmpty() || !qOutDir.exists())
  {
    addMessage("Error: No output dir specified, or output dir does not exist.");
    return;
  }

  QString lowerFirst = Util::lowerFirst( packageName);
  QString packageDir = QDir(outDir + "/" + lowerFirst).absolutePath();
  if (!QDir(packageDir).exists())
  {
    addMessage("Error: please select 'Generate Package Code' first.");
    return ;
  }

  QString libSBMLSourceDir =
      QDir(DeviserSettings::getInstance()->getLibSBMLSourceDir()).absolutePath();
  if (!QDir(libSBMLSourceDir).exists())
  {
    addMessage("Error: Missing 'libSBML source' dir.");
    return ;
  }

  if (QFile::exists(libSBMLSourceDir + "/" + lowerFirst + "-package.cmake"))
  {
    if (QMessageBox::question(this, "Overwrite existing files?",
                              "The package has been previously integrated into the libSBML source tree. Do you want those files to be overwritten? \nWARNING: you will loose all changes that you made in the integrated branch.",
                              QMessageBox::Yes | QMessageBox::No , QMessageBox::No) != QMessageBox::Yes)
    {
      addMessage("'Adding code to source tree' cancelled.");
      return;
    }
  }


  if (!Util::copyDir(
    packageDir + "/" + "src",
    libSBMLSourceDir + "/" + "src"
    ))
  {
    addMessage("'Adding code to source tree' failed!");
  }

  if (!Util::copyDir(
    packageDir + "/" + "examples",
    libSBMLSourceDir + "/" + "examples"
    ))
  {
    addMessage("'Adding code to source tree' failed!");
  }

  Util::copyDir(
        packageDir + "/" + lowerFirst + "-package.cmake",
        libSBMLSourceDir
        );
  addMessage();

  addMessage("DONE");
  addMessage();
}



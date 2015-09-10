#include "devisersettings.h"

#include <QApplication>
#include <QFile>
#include <QFileInfo>

#include <QDomDocument>
#include <QDomElement>
#include <QDomNodeList>

#include <QXmlStreamWriter>
#include <util.h>

#include <cstdlib>

DeviserSettings* DeviserSettings::mpInstance = NULL;

DeviserSettings::DeviserSettings(QObject *parent)
  : QObject(parent)
{

}

DeviserSettings*
DeviserSettings::getInstance()
{
  if (mpInstance == NULL)
  {
    mpInstance = new DeviserSettings();
    mpInstance->loadSettings(getSettingsFile());

    std::atexit(&DeviserSettings::removeInstance);
  }

  return mpInstance;
}

QString readElement(QDomElement& element, const QString& name)
{
  QDomNodeList list = element.elementsByTagName(name);
  if (list.isEmpty()) return "";
  return list.at(0).toElement().text();
}

void
DeviserSettings::loadSettings(const QString& settingsFile)
{
  QString fileName = settingsFile;
  if (fileName.isEmpty()) return;

  QFile file(fileName);
  if (!file.exists()) return;
  file.open(QIODevice::ReadOnly);


  QByteArray data = file.readAll();
  data.replace("utf-16", "UTF-8");

  QDomDocument document;
  document.setContent(data);

  QDomElement root = document .documentElement();

  mPythonInterpreter = readElement(root, "PythonInterpreter");
  mPythonIncludes = readElement(root, "PythonIncludes");
  mPythonLib = readElement(root, "PythonLibrary");
  mDeviserRepository = readElement(root, "DeviserRepository");
  mDefaultOutputDir = readElement(root, "DefaultOutputDir");
  mSbmlPkgSpecDir = readElement(root, "SBMLPkgSpecDir");
  mMikTexBinDir = readElement(root, "MikTexDir");
  mLibSBMLSourceDir = readElement(root, "LibSBMLSourceDir");
  mDependencySourceDir = readElement(root, "DependenciesSourceDir");
  mCompiler = readElement(root, "Compiler");
  mVsBatchFile = readElement(root, "VSBatchFile");
  mCmakeExecutable = readElement(root, "CMake");
  mSwigExecutable = readElement(root, "Swig");
  mWidth = readElement(root, "Width").toInt();
  mHeight = readElement(root, "Height").toInt();
  mUseSVG = readElement(root, "UseSVG") != "false";
  mFitUML = readElement(root, "FitUML") != "false";

  mRecentFiles.clear();
  QDomNodeList list =  root.elementsByTagName("file");
  for (int i = 0; i < list.count(); ++i)
  {
    mRecentFiles << list.at(i).toElement().text();
  }

}

void
DeviserSettings::saveSettings()
{
  QString fileName = getSettingsFile();
  if (fileName.isEmpty()) return;

  QFile file(fileName);
  if (!file.open(QIODevice::WriteOnly))
    return;

  QXmlStreamWriter writer(&file);
  writer.setAutoFormatting(true);
  writer.setAutoFormattingIndent(2);
  writer.setCodec("UTF-8");
  writer.writeStartDocument();

  writer.writeStartElement("DeviserSettings");
  writer.writeAttribute("xmlns:xsi", "http://www.w3.org/2001/XMLSchema-instance");
  writer.writeAttribute("xmlns:xsd", "http://www.w3.org/2001/XMLSchema");

  writer.writeTextElement("PythonInterpreter", mPythonInterpreter);
  writer.writeTextElement("PythonIncludes", mPythonIncludes);
  writer.writeTextElement("PythonLibrary", mPythonLib);

  writer.writeTextElement("DeviserRepository", mDeviserRepository);
  writer.writeTextElement("DefaultOutputDir", mDefaultOutputDir);
  writer.writeTextElement("SBMLPkgSpecDir", mSbmlPkgSpecDir);
  writer.writeTextElement("MikTexDir", mMikTexBinDir);
  writer.writeTextElement("LibSBMLSourceDir", mLibSBMLSourceDir);
  writer.writeTextElement("DependenciesSourceDir", mDependencySourceDir);

  writer.writeTextElement("VSBatchFile", mVsBatchFile);
  writer.writeTextElement("Compiler", mCompiler);

  writer.writeTextElement("CMake", mCmakeExecutable);
  writer.writeTextElement("Swig", mSwigExecutable);

  writer.writeTextElement("Width", QString::number(mWidth));
  writer.writeTextElement("Height", QString::number(mHeight));

  writer.writeTextElement("UseSVG", mUseSVG ? "true" : "false");
  writer.writeTextElement("FitUML", mFitUML ? "true" : "false");

  writer.writeStartElement("RecentFiles");
  foreach(QString filename, mRecentFiles)
  {
    writer.writeTextElement("file", filename);
  }

  writer.writeEndElement();

  writer.writeEndElement();

  writer.writeEndDocument();
  file.close();

}

int DeviserSettings::getWidth() const
{
  return mWidth;
}

void DeviserSettings::setWidth(int width)
{
  mWidth = width;
}
int DeviserSettings::getHeight() const
{
  return mHeight;
}

void DeviserSettings::setHeight(int height)
{
  mHeight = height;
}

const QString& DeviserSettings::getVsBatchFile() const
{
  return mVsBatchFile;
}

void DeviserSettings::setVsBatchFile(const QString &vsBatchFile)
{
  mVsBatchFile = vsBatchFile;
}

QStringList &DeviserSettings::getRecentFiles()
{
  return mRecentFiles;
}

void DeviserSettings::addRecentFile(const QString &filename)
{
  removeRecentFile(filename);
  mRecentFiles.insert(0, filename);

  while (mRecentFiles.count() > 9)
  {
    mRecentFiles.removeAt(9);
  }

  saveSettings();

}

void DeviserSettings::removeRecentFile(const QString &filename)
{
  mRecentFiles.removeAll(filename);
  saveSettings();
}
bool DeviserSettings::getUseSVG() const
{
    return mUseSVG;
}

void DeviserSettings::setUseSVG(bool useSVG)
{
    mUseSVG = useSVG;
}
bool DeviserSettings::getFitUML() const
{
    return mFitUML;
}

void DeviserSettings::setFitUML(bool fitUML)
{
    mFitUML = fitUML;
}


QString
DeviserSettings::getSettingsFile()
{
    QByteArray dir = Util::isWindows() ?  qgetenv("APPDATA")
                                        : qgetenv("HOME");

  {
    QFile file(dir + "/" + ".deviser_config.xml");
    if (file.exists())
      return QFileInfo(file).absoluteFilePath();
  }

  {
    QFile file(dir + "/" + "deviser_config.xml");
    if (file.exists())
      return QFileInfo(file).absoluteFilePath();
  }

  dir.clear();
  dir.append(QApplication::applicationDirPath());
  {
    QFile file(dir + "/" + "deviser_config.xml");
    if (file.exists())
      return QFileInfo(file).absoluteFilePath();
  }


  // file does not exist, lets return the default

  if (Util::isWindows())
  {
    QByteArray dir = qgetenv("APPDATA");
    return QFileInfo(dir + "/" + "deviser_config.xml").absoluteFilePath();
  }

  // on all other platforms we hide
  {
    QByteArray dir = qgetenv("HOME");
    return QFileInfo(dir + "/" + ".deviser_config.xml").absoluteFilePath();
  }
}

const QString& DeviserSettings::getPythonInterpreter() const
{
  return mPythonInterpreter;
}

void DeviserSettings::setPythonInterpreter(const QString &pythonInterpreter)
{
  mPythonInterpreter = pythonInterpreter;
}

const QString& DeviserSettings::getDeviserRepository() const
{
  return mDeviserRepository;
}

void DeviserSettings::setDeviserRepository(const QString &deviserRepository)
{
  mDeviserRepository = deviserRepository;
}

const QString& DeviserSettings::getDefaultOutputDir() const
{
  return mDefaultOutputDir;
}

void DeviserSettings::setDefaultOutputDir(const QString &defaultOutputDir)
{
  mDefaultOutputDir = defaultOutputDir;
}

const QString& DeviserSettings::getSbmlPkgSpecDir() const
{
  return mSbmlPkgSpecDir;
}

void DeviserSettings::setSbmlPkgSpecDir(const QString &sbmlPkgSpecDir)
{
  mSbmlPkgSpecDir = sbmlPkgSpecDir;
}

const QString& DeviserSettings::getMikTexBinDir() const
{
  return mMikTexBinDir;
}

void DeviserSettings::setMikTexBinDir(const QString &mikTexBinDir)
{
  mMikTexBinDir = mikTexBinDir;
}

const QString& DeviserSettings::getLibSBMLSourceDir() const
{
  return mLibSBMLSourceDir;
}

void DeviserSettings::setLibSBMLSourceDir(const QString &libSBMLSourceDir)
{
  mLibSBMLSourceDir = libSBMLSourceDir;
}

const QString& DeviserSettings::getCompiler() const
{
  if (mCompiler.isEmpty())
    return mVsBatchFile;

  return mCompiler;
}

void DeviserSettings::setCompiler(const QString &compiler)
{
  mCompiler = compiler;
}

const QString& DeviserSettings::getCmakeExecutable() const
{
  return mCmakeExecutable;
}

void DeviserSettings::setCmakeExecutable(const QString &cmakeExecutable)
{
  mCmakeExecutable = cmakeExecutable;
}

const QString& DeviserSettings::getDependencySourceDir() const
{
  return mDependencySourceDir;
}

void DeviserSettings::setDependencySourceDir(const QString &dependencySourceDir)
{
  mDependencySourceDir = dependencySourceDir;
}

const QString& DeviserSettings::getSwigExecutable() const
{
  return mSwigExecutable;
}

void DeviserSettings::setSwigExecutable(const QString &swigExecutable)
{
  mSwigExecutable = swigExecutable;
}

const QString& DeviserSettings::getPythonIncludes() const
{
  return mPythonIncludes;
}

void DeviserSettings::setPythonIncludes(const QString &pythonIncludes)
{
  mPythonIncludes = pythonIncludes;
}

const QString& DeviserSettings::getPythonLib() const
{
  return mPythonLib;
}

void DeviserSettings::setPythonLib(const QString &pythonLib)
{
  mPythonLib = pythonLib;
}

void DeviserSettings::removeInstance()
{
  if (mpInstance != NULL)
    delete mpInstance;
  mpInstance = NULL;
}

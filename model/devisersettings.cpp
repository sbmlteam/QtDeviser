#include "devisersettings.h"

#include <QApplication>
#include <QFile>

#include <QDomDocument>
#include <QDomElement>
#include <QDomNodeList>

#include <QXmlStreamWriter>

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
QString DeviserSettings::getVsBatchFile() const
{
  return mVsBatchFile;
}

void DeviserSettings::setVsBatchFile(const QString &vsBatchFile)
{
  mVsBatchFile = vsBatchFile;
}





QString
DeviserSettings::getSettingsFile()
{
  QByteArray dir = qgetenv("APPDATA");
  if (dir.isEmpty())
    dir = qgetenv("HOME");

  {
    QFile file(dir + "/" + "deviser_config.xml");
    if (file.exists())
      return file.fileName();
  }

  dir.clear();
  dir.append(QApplication::applicationDirPath());
  {
    QFile file(dir + "/" + "deviser_config.xml");
    if (file.exists())
      return file.fileName();
  }

  return "";
}

QString DeviserSettings::getPythonInterpreter() const
{
  return mPythonInterpreter;
}

void DeviserSettings::setPythonInterpreter(const QString &pythonInterpreter)
{
  mPythonInterpreter = pythonInterpreter;
}
QString DeviserSettings::getDeviserRepository() const
{
  return mDeviserRepository;
}

void DeviserSettings::setDeviserRepository(const QString &deviserRepository)
{
  mDeviserRepository = deviserRepository;
}
QString DeviserSettings::getDefaultOutputDir() const
{
  return mDefaultOutputDir;
}

void DeviserSettings::setDefaultOutputDir(const QString &defaultOutputDir)
{
  mDefaultOutputDir = defaultOutputDir;
}
QString DeviserSettings::getSbmlPkgSpecDir() const
{
  return mSbmlPkgSpecDir;
}

void DeviserSettings::setSbmlPkgSpecDir(const QString &sbmlPkgSpecDir)
{
  mSbmlPkgSpecDir = sbmlPkgSpecDir;
}
QString DeviserSettings::getMikTexBinDir() const
{
  return mMikTexBinDir;
}

void DeviserSettings::setMikTexBinDir(const QString &mikTexBinDir)
{
  mMikTexBinDir = mikTexBinDir;
}
QString DeviserSettings::getLibSBMLSourceDir() const
{
  return mLibSBMLSourceDir;
}

void DeviserSettings::setLibSBMLSourceDir(const QString &libSBMLSourceDir)
{
  mLibSBMLSourceDir = libSBMLSourceDir;
}
QString DeviserSettings::getCompiler() const
{
  if (mCompiler.isEmpty())
    return mVsBatchFile;

  return mCompiler;
}

void DeviserSettings::setCompiler(const QString &compiler)
{
  mCompiler = compiler;
}
QString DeviserSettings::getCmakeExecutable() const
{
  return mCmakeExecutable;
}

void DeviserSettings::setCmakeExecutable(const QString &cmakeExecutable)
{
  mCmakeExecutable = cmakeExecutable;
}
QString DeviserSettings::getDependencySourceDir() const
{
  return mDependencySourceDir;
}

void DeviserSettings::setDependencySourceDir(const QString &dependencySourceDir)
{
  mDependencySourceDir = dependencySourceDir;
}
QString DeviserSettings::getSwigExecutable() const
{
  return mSwigExecutable;
}

void DeviserSettings::setSwigExecutable(const QString &swigExecutable)
{
  mSwigExecutable = swigExecutable;
}
QString DeviserSettings::getPythonIncludes() const
{
  return mPythonIncludes;
}

void DeviserSettings::setPythonIncludes(const QString &pythonIncludes)
{
  mPythonIncludes = pythonIncludes;
}
QString DeviserSettings::getPythonLib() const
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











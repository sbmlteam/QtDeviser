#include "util.h"

#include <QFile>
#include <QDir>
#include <QStringList>
#include <QString>
#include <QTextStream>

#include <model/devisersettings.h>

Util::Util()
{

}

QString
Util::guessPlural(const QString &s)
{
  QString str(s);
  if (str.endsWith("Information")) return str;
  if (str.endsWith("Index")) return str.replace("Index", "Indices");
  if (str.endsWith("s")) return str;
  if (str.endsWith("x")) return str + "es";
  return str + "s";
}

QString
Util::lowerFirst(const QString& s)
{
  QString str(s);
  return str.left(1).toLower() + str.right(str.length()-1);
}

QString Util::upperFirst(const QString &s)
{
  QString str(s);
  return str.left(1).toUpper() + str.right(str.length()-1);
}

QList<QString>
Util::getCoreClasses()
{
  return getCoreClassesMap().keys();
}

QMap<QString, QString>
Util::getCoreClassesMap()
{
  QMap<QString, QString> result;
  QFile data(":/CoreClasses.txt");
  data.open(QIODevice::ReadOnly);
  QTextStream in(&data);

  while(!in.atEnd()) {
      QString line = in.readLine();
      line = line.replace(" ", "");
      QStringList fields = line.split(",");
      result[fields[0].trimmed()] = fields[1].trimmed();
  }
  data.close();

  return result;
}

QStringList Util::getKnownTypes()
{
  return QStringList()
      << "enum"
      << "array"
      << "element"
      << "lo_element"
      << "inline_lo_element"
      << "string"
      << "double"
      << "int"
      << "bool"
      << "boolean"
      << "uint"
      << "unsigned int"
      << "positive int"
      << "non-negative int"
      << "integer"
      << "unsigned integer"
      << "positive integer"
      << "non-negative integer"
      << "ID"
      << "IDREF"
      << "SId"
      << "SIdRef"
      << "UnitSId"
      << "UnitSIdRef";
}

QStringList& Util::getUserDefinedTypes()
{
  DeviserSettings* instance = DeviserSettings::getInstance();
  return instance->getUserDefinedTypes();
}

QString Util::getErrorStyleSheet()
{
  QColor color = DeviserSettings::getInstance()->getValidationColor();

  return QString("QLineEdit, QLineEdit:hover {"
         "  background-color: rgba(%1,%2,%3,%4);"
         "  selection-background-color:rgba(%1,%2,%3,%4);"
         "  border-width: 1px;"
         "  border-color: black;"
         "  border: 1px solid gray;"
         "}")
      .arg(color.red())
      .arg(color.green())
      .arg(color.blue())
      .arg(color.alpha());
}

QString
Util::getClassColor()
{
  return "linen";
}

QString
Util::getEnumColor()
{
  return "gold";
}

QString
Util::getExtensionColor()
{
  return "palegreen";
}

QString
Util::getEnumPrefix()
{
  return QString::fromUtf8("\xC2\xAB%1\xC2\xBB;").arg("Enumeration");
}

QString
Util::getExecutableFilter()
{
#ifdef Q_OS_WIN
  return "Executable files (*.exe; *.bat; *.cmd);;All files (*.*)";
#else
  return "Executable files (*.*; *.sh);;All files (*.*)";
#endif
}


QString
Util::getLibFilter()
{
#ifdef Q_OS_WIN
  return "Library files (*.lib);;All files (*.*)";
#else
  return "Library files (*.a*; *.so; *.dylib);;All files (*.*)";
#endif
}

QString Util::getHeaderFilter()
{
  return "Header files (*.h; *.h++; *.hpp; *.hh; *.hxx);;All files (*.*)";
}

QString Util::getImplementationFilter()
{
  return "C++ files (*.c; *.c++; *.cpp; *.cc; *.cxx);;All files (*.*)";
}


bool Util::isWindows()
{
#ifdef Q_OS_WIN
  return true;
#else
  return false;
#endif
}

bool Util::removeDir(const QString &dirPath, const QString &filter)
{
  QFileInfo dirInfo(dirPath);
  if (dirInfo.isFile())
  {
    return QFile (dirPath).remove();
  }

  QDir dir(dirPath);
  if (!dir.exists())
    return true;

  foreach(const QFileInfo &info, dir.entryInfoList(QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot))
  {
    if (info.isDir())
    {
      if (!removeDir(info.filePath(), filter))
        return false;
    }
    else
    {
      if (!filter.isEmpty() && !info.fileName().contains(filter))
        continue;

      if (!dir.remove(info.fileName()))
        return false;
    }
  }

  if (filter.isEmpty())
  {
   QDir parentDir(QFileInfo(dirPath).path());
   return parentDir.rmdir(QFileInfo(dirPath).fileName());
  }

  return true;
}

bool
Util::copyDir(const QString &srcPath, const QString &dstPath, bool overwrite)
{

  QDir parentDstDir(QFileInfo(dstPath).path());
  parentDstDir.mkdir(QFileInfo(dstPath).fileName());
    

  QFileInfo srcInfo(srcPath);
  if (srcInfo.isFile())
  {
    QString dstItemPath = dstPath + "/" + srcInfo.fileName();
    if (QFile::exists(dstItemPath) && overwrite)
      QFile::remove(dstItemPath);
    return  QFile::copy(srcPath, dstItemPath);
  }

  QDir srcDir(srcPath);
  foreach(const QFileInfo &info, srcDir.entryInfoList(QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot))
  {
    QString srcItemPath = srcPath + "/" + info.fileName();
    QString dstItemPath = dstPath + "/" + info.fileName();
    if (info.isDir())
    {
      if (!copyDir(srcItemPath, dstItemPath, overwrite))
      {
        return false;
      }
    }
    else if (info.isFile())
    {
      if (QFile::exists(dstItemPath) && overwrite)
        QFile::remove(dstItemPath);
      if (!QFile::copy(srcItemPath, dstItemPath))
      {
        return false;
      }
    } 
  }
  return true;
}

QString
Util::toARgbString(const QColor& color)
{
  return
      byteToHex(color.alpha()) +
      byteToHex(color.red()) +
      byteToHex(color.green()) +
      byteToHex(color.blue())
      ;
}

QString
Util::byteToHex(int oByte)
{
  if (oByte == 0)
    return QString("00");
  QString sResult = QString::number(oByte, 16);
  if (sResult.length() == 1)
    sResult = "0" + sResult;
  return sResult;
}

QColor
Util::parseColor(const QString& sColor)
{
  QColor oResult;
  if (sColor.isEmpty()) return oResult;

  if (sColor.length() == 8)
  {
    int nAlpha = sColor.mid(0,2).toInt(NULL, 16);
    int nRed = sColor.mid(2,2).toInt(NULL, 16);
    int nGreen = sColor.mid(4,2).toInt(NULL, 16);
    int nBlue = sColor.mid(6,2).toInt(NULL, 16);
    oResult = QColor(nRed, nGreen, nBlue, nAlpha);
  }
  else if (sColor.length() == 6)
  {
    int nRed = sColor.mid(0,2).toInt(NULL, 16);
    int nGreen = sColor.mid(2,2).toInt(NULL, 16);
    int nBlue = sColor.mid(4,2).toInt(NULL, 16);
    oResult = QColor(nRed, nGreen, nBlue, 255);
  }
  return oResult;
}


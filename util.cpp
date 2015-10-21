#include "util.h"

#include <QFile>
#include <QDir>
#include <QStringList>
#include <QString>
#include <QTextStream>

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
  return "Executable files (*.*, *.sh);;All files (*.*)";
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
  foreach(const QFileInfo &info, dir.entryInfoList(QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot)) {
    if (info.isDir()) {
      if (!removeDir(info.filePath(), filter))
        return false;
    } else {
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

bool Util::copyDir(const QString &srcPath, const QString &dstPath)
{

  QDir parentDstDir(QFileInfo(dstPath).path());
  parentDstDir.mkdir(QFileInfo(dstPath).fileName());
    

  QFileInfo srcInfo(srcPath);
  if (srcInfo.isFile())
  {
    QString dstItemPath = dstPath + "/" + srcInfo.fileName();

    return  QFile::copy(srcPath, dstItemPath);
  }

  QDir srcDir(srcPath);
  foreach(const QFileInfo &info, srcDir.entryInfoList(QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot)) {
    QString srcItemPath = srcPath + "/" + info.fileName();
    QString dstItemPath = dstPath + "/" + info.fileName();
    if (info.isDir()) {
      if (!copyDir(srcItemPath, dstItemPath)) {
        return false;
      }
    } else if (info.isFile()) {
      if (!QFile::copy(srcItemPath, dstItemPath)) {
        return false;
      }
    } 
  }
  return true;
}


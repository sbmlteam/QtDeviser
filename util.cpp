#include "util.h"

#include <QFile>
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
  //return QString::fromUtf8("\u00ABEnumeration\u00BB;");
  return QString::fromUtf8("Enumeration;");
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

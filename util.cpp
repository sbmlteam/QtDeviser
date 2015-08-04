#include "util.h"

#include <QFile>
#include <QStringList>

Util::Util()
{

}

QString Util::guessPlural(const QString &str)
{
  if (str.endsWith("Information")) return str;
  if (str.endsWith("Index")) return str.replace("Index", "Indices");
  if (str.endsWith("s")) return str;
  if (str.endsWith("x")) return str + "es";
  return str + "s";
}

QList<QString> Util::getCoreClasses()
{
  return getCoreClassesMap().keys();
}

QMap<QString, QString> Util::getCoreClassesMap()
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


#ifndef UTIL_H
#define UTIL_H

#include <QList>
#include <QString>
#include <QMap>

class Util
{
public:
  Util();

  static QString guessPlural(const QString& str);
  static QList<QString> getCoreClasses();
  static QMap<QString, QString> getCoreClassesMap();

protected:

};

#endif // UTIL_H

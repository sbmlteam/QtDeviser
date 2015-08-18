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
  static QString lowerFirst(const QString& str);

  static QList<QString> getCoreClasses();
  static QMap<QString, QString> getCoreClassesMap();

  static QString getClassColor();
  static QString getEnumColor();
  static QString getExtensionColor();
  static QString getEnumPrefix();
  static QString getExecutableFilter();
  static QString getLibFilter();

  static bool isWindows();

  static bool removeDir(const QString &dirPath, const QString& filter = "");
  static bool copyDir(const QString &srcPath, const QString &dstPath);

protected:

};

#endif // UTIL_H

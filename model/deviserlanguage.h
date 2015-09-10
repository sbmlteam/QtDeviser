#ifndef DEVISERLANGUAGE_H
#define DEVISERLANGUAGE_H

#include <model/deviserbase.h>

class DeviserLanguage : public DeviserBase
{
  Q_OBJECT

public:
  DeviserLanguage();
  DeviserLanguage(const DeviserLanguage& other);
  virtual void initializeFrom(const QDomElement& element);

  virtual void writeAttributesTo(QXmlStreamWriter& writer) const;
  virtual void writeTo(QXmlStreamWriter& writer) const;

  bool isEmpty() const;

  QString name() const;
  void setName(const QString &name);

  QString baseClass() const;
  void setBaseClass(const QString &baseClass);

  QString documentClass() const;
  void setDocumentClass(const QString &documentClass);

  QString prefix() const;
  void setPrefix(const QString &prefix);

  QString libraryName() const;
  void setLibraryName(const QString &libraryName);

protected:

  QString mName;
  QString mBaseClass;
  QString mDocumentClass;
  QString mPrefix;
  QString mLibraryName;

};

#endif // DEVISERLANGUAGE_H

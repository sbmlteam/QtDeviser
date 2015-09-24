#ifndef DEVISERLANGUAGE_H
#define DEVISERLANGUAGE_H

#include <model/deviserbase.h>

class DeviserLanguage : public DeviserBase
{
  Q_OBJECT

public:
  DeviserLanguage();
  DeviserLanguage(const DeviserLanguage& other);
  DeviserLanguage& operator= (const DeviserLanguage& rhs);

  virtual void initializeFrom(const QDomElement& element);

  virtual void writeAttributesTo(QXmlStreamWriter& writer) const;
  virtual void writeTo(QXmlStreamWriter& writer) const;

  bool isEmpty() const;

  const QString &name() const;
  void setName(const QString &name);

  const QString &baseClass() const;
  void setBaseClass(const QString &baseClass);

  const QString &documentClass() const;
  void setDocumentClass(const QString &documentClass);

  const QString &prefix() const;
  void setPrefix(const QString &prefix);

  const QString &libraryName() const;
  void setLibraryName(const QString &libraryName);

  const QString &listOfClass() const;
  void setListOfClass(const QString &listOfClass);

protected:

  QString mName;
  QString mBaseClass;
  QString mDocumentClass;
  QString mPrefix;
  QString mLibraryName;
  QString mListOfClass;

};

#endif // DEVISERLANGUAGE_H

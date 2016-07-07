#ifndef DEVISERLANGUAGEDEPENDENCY_H
#define DEVISERLANGUAGEDEPENDENCY_H

#include <model/deviserbase.h>

class DeviserLanguageDependency : public DeviserBase
{
  Q_OBJECT

public:
  DeviserLanguageDependency();
  DeviserLanguageDependency(const DeviserLanguageDependency& other);
  DeviserLanguageDependency& operator= (const DeviserLanguageDependency& rhs);

  virtual void initializeFrom(const QDomElement& element);

  virtual void writeAttributesTo(QXmlStreamWriter& writer) const;

  virtual void writeTo(QXmlStreamWriter& writer) const;

  QString libraryName() const;

  void setLibraryName(const QString& libraryName);

  QString prefix() const;

  void setPrefix(const QString& prefix);

protected:

  QString mLibraryName;
  QString mPrefix;

};

#endif // DEVISERLANGUAGEDEPENDENCY_H

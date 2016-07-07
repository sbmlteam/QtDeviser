#ifndef DEVISERLANGUAGEVERSION_H
#define DEVISERLANGUAGEVERSION_H

#include <model/deviserbase.h>

class DeviserLanguageVersion : public DeviserBase
{
  Q_OBJECT

public:
  DeviserLanguageVersion();
  DeviserLanguageVersion(const DeviserLanguageVersion& other);
  DeviserLanguageVersion& operator= (const DeviserLanguageVersion& rhs);

  virtual void initializeFrom(const QDomElement& element);

  virtual void writeAttributesTo(QXmlStreamWriter& writer) const;
  virtual void writeTo(QXmlStreamWriter& writer) const;

  QString namespaceUri() const;
  void setNamespaceUri(const QString& namespaceUri);

  int level() const;
  void setLevel(int level);

  int version() const;
  void setVersion(int version);

protected:
  QString mNamespaceUri;
  int mLevel;
  int mVersion;

};

#endif // DEVISERLANGUAGEVERSION_H

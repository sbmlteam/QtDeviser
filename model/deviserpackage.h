#ifndef DEVISERPACKAGE_H
#define DEVISERPACKAGE_H

#include <model/deviserbase.h>
#include <model/deviserversion.h>
#include <model/deviserlanguage.h>


class DeviserPackage : public DeviserBase
{
  Q_OBJECT

public:
  DeviserPackage();
  DeviserPackage(const DeviserPackage& other);
  DeviserPackage(const QString& fileName);
  DeviserPackage(QDomElement& element);

  virtual void initializeFrom(const QDomElement& element);

  virtual void setParent(DeviserPackage* doc);

  virtual QString toXmlString() const;
  virtual QString toYuml(bool usecolor = true) const;

  virtual void writeAttributesTo(QXmlStreamWriter& writer) const;
  virtual void writeElementsTo(QXmlStreamWriter& writer) const;
  virtual void writeTo(QXmlStreamWriter& writer) const;

  virtual void writeTo(const QString& fileName) const;

  QList<DeviserVersion*>& getVersions();
  const QList<DeviserVersion*>& getVersions() const;

  DeviserVersion* getVersion(const QString& name);
  DeviserVersion* getVersion(int level, int version, int pkgVersion);

  const QString& getName() const;
  void setName(const QString& name);
  const QString& getFullName() const;
  void setFullName(const QString& fullName);
  int getStartNumber() const;
  void setStartNumber(int startNumber);
  int getOffset() const;
  void setOffset(int offset);
  int getVersion() const;
  void setVersion(int version);
  bool isRequired() const;
  void setRequired(bool isRequired);
  const QString& getAdditionalDeclarations() const;
  void setAdditionalDeclarations(const QString& additionalDeclarations);
  const QString& getAdditionalDefinitions() const;
  void setAdditionalDefinitions(const QString& additionalDefinitions);

  DeviserVersion* createVersion();

  bool getModified() const;
  void setModified(bool modified);

signals:
  void nameChanged();
  void fullNameChanged();
  void startNumberChanged();
  void offsetChanged();
  void versionChanged();
  void requiredChanged();
  void additionalDeclarationsChanged();
  void additionalDefinitionsChanged();
  void modifiedChanged();

protected:
  QString mName;
  QString mFullName;
  int mStartNumber;
  int mOffset;
  int mVersion;
  bool mRequired;
  QString mAdditionalDeclarations;
  QString mAdditionalDefinitions;

  QList<DeviserVersion*> mVersions;

  bool mModified;

  DeviserLanguage mLanguage;

};

#endif // DEVISERPACKAGE_H

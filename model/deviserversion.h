#ifndef DEVISERVERSION_H
#define DEVISERVERSION_H

#include <model/deviserbase.h>

class DeviserClass;
class DeviserPlugin;
class DeviserEnum;
class DeviserMapping;

class DeviserVersion : public DeviserBase
{
  Q_OBJECT

public:
  DeviserVersion();

  DeviserVersion(const DeviserVersion& other);

  virtual void initializeFrom(const QDomElement& element);
  virtual void setParent(DeviserPackage* doc);

  QString toString() const;

  int getLevel() const;
  void setLevel(int level);

  int getVersion() const;
  void setVersion(int version);

  int getPkgVersion() const;
  void setPkgVersion(int pkgVersion);

  const QList<DeviserClass*>& getElements() const;
  QList<DeviserClass*>& getElements();

  const QList<DeviserPlugin*>& getPlugins() const;
  QList<DeviserPlugin*>& getPlugins();

  const QList<DeviserEnum*>& getEnums() const;
  QList<DeviserEnum*>& getEnums();

  const QList<DeviserMapping*>& getMappings() const;
  QList<DeviserMapping*>& getMappings();

  bool hasMappingFor(const QString& element) const;

  DeviserClass* getElement(const QString& name);
  DeviserClass* createElement();

  DeviserPlugin* getPlugin(const QString& name);
  DeviserPlugin* createPlugin();

  DeviserEnum* getEnum(const QString& name);
  DeviserEnum* createEnum();

  virtual void writeAttributesTo(QXmlStreamWriter& writer) const;
  virtual void writeElementsTo(QXmlStreamWriter& writer) const;

  virtual void writeTo(QXmlStreamWriter& writer) const;

  virtual QString toYuml(bool usecolor = true) const;

  bool getIgnorePackageVersion() const;
  void setIgnorePackageVersion(bool ignorePackageVersion);

  void initializeMappings();

  QList<QString> getUsedClasses() const;
  QList<QString> getDefinedClasses() const;

signals:
  void identityChanged(const QString& oldIdentity, const QString& newIdentity,
                       const DeviserVersion* version);
  void levelChanged();
  void versionChanged();
  void pkgVersionChanged();

protected: 
  int mLevel;
  int mVersion;
  int mPkgVersion;

  QList<DeviserClass*> mElements;
  QList<DeviserPlugin*> mPlugins;
  QList<DeviserEnum*> mEnums;
  QList<DeviserMapping*> mMappings;

  bool mIgnorePackageVersion;

};

#endif // DEVISERVERSION_H

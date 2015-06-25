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

    int getLevel() const { return mLevel; }
    int getVersion() const { return mVersion; }
    int getPkgVersion() const { return mPkgVersion; }

    void setLevel(int level) { mLevel = level; emit levelChanged(); }
    void setVersion(int version) { mVersion = version; emit versionChanged(); }
    void setPkgVersion(int pkgVersion) { mPkgVersion = pkgVersion; emit pkgVersionChanged();}

    const QList<DeviserClass*>& getElements() const { return mElements; }
    const QList<DeviserPlugin*>& getPlugins() const { return mPlugins; }
    const QList<DeviserEnum*>& getEnums() const { return mEnums; }
    const QList<DeviserMapping*>& getMappings() const { return mMappings; }

    DeviserClass* getElement(const QString& name);
    DeviserClass* createElement();

    DeviserPlugin* getPlugin(const QString& name);
    DeviserPlugin* createPlugin();

    DeviserEnum* getEnum(const QString& name);
    DeviserEnum* createEnum();


signals:
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

};

#endif // DEVISERVERSION_H

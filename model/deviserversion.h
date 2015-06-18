#ifndef DEVISERVERSION_H
#define DEVISERVERSION_H

#include <model/deviserbase.h>

class DeviserClass;
class DeviserPlugin;
class DeviserEnum;
class DeviserMapping;

class DeviserVersion : public DeviserBase
{
public:
    DeviserVersion();

    DeviserVersion(const DeviserVersion& other);

    virtual void initializeFrom(const QDomElement& element);

    QString toString() const;


    const QList<DeviserClass*> getElements() const { return mElements; }
    const QList<DeviserClass*> getPlugins() const { return mPlugins; }
    const QList<DeviserEnum*> getEnums() const { return mEnums; }
    const QList<DeviserMapping*> getMappings() const { return mMappings; }


protected: 
  int mLevel;
  int mVersion;
  int mPkgVersion;

  QList<DeviserClass*> mElements;
  QList<DeviserClass*> mPlugins;
  QList<DeviserEnum*> mEnums;
  QList<DeviserMapping*> mMappings;

};

#endif // DEVISERVERSION_H

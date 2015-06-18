#include "deviserversion.h"

#include "deviserclass.h"
#include "deviserenum.h"
#include "deviserplugin.h"
#include "devisermapping.h"

DeviserVersion::DeviserVersion()
  : DeviserBase()
  , mLevel(0)
  , mVersion(0)
  , mPkgVersion(1)
  , mElements()
  , mPlugins()
  , mEnums()
  , mMappings()
{

}


DeviserVersion::DeviserVersion(const DeviserVersion& other)
  : DeviserBase(other)
  , mLevel(other.mLevel)
  , mVersion(other.mVersion)
  , mPkgVersion(other.mPkgVersion)
  , mElements()
  , mPlugins()
  , mEnums()
  , mMappings()
{
  cloneElements(other.mElements, mElements);
  cloneElements(other.mPlugins, mPlugins);
  cloneElements(other.mEnums, mEnums);
  cloneElements(other.mMappings, mMappings);
}

void DeviserVersion::initializeFrom(const QDomElement& element)
{
  DeviserBase::initializeFrom(element);
}

QString DeviserVersion::toString() const
{
  return QString("Version: %1,%2,%3").arg(mLevel).arg(mVersion).arg(mPkgVersion);
}
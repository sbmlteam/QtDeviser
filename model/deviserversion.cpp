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

void DeviserVersion::setParent(DeviserPackage* doc)
{
    DeviserBase::setParent(doc);

    setParentOn(mElements, doc, this);
    setParentOn(mPlugins, doc, this);
    setParentOn(mEnums, doc, this);
    setParentOn(mMappings, doc, this);
}

void DeviserVersion::initializeFrom(const QDomElement& element)
{
  DeviserBase::initializeFrom(element);

  mLevel = element.attribute("level").toInt();
  mVersion = element.attribute("version").toInt();
  mPkgVersion = element.attribute("pkg_version").toInt();

  initializeListFrom(mElements, element, "element");
  initializeListFrom(mPlugins, element, "plugin");
  initializeListFrom(mEnums, element, "enum");
  initializeListFrom(mMappings, element, "mapping");

}

QString DeviserVersion::toString() const
{
  return QString("Version: %1,%2,%3").arg(mLevel).arg(mVersion).arg(mPkgVersion);
}

DeviserEnum* DeviserVersion::getEnum(const QString& name)
{
  if (mEnums.empty()) return NULL;
    for (auto& it = mEnums.begin(); it != mEnums.end(); ++it)
        if ((*it)->getName() == name)
            return *it;
    return NULL;
}

DeviserPlugin* DeviserVersion::getPlugin(const QString& name)
{
  if (mPlugins.empty()) return NULL;
    for (auto& it = mPlugins.begin(); it != mPlugins.end(); ++it)
        if ((*it)->getExtensionPoint() == name)
            return *it;
    return NULL;
}

DeviserClass* DeviserVersion::getElement(const QString& name)
{
  if (mElements.empty()) return NULL;
    for (auto& it = mElements.begin(); it != mElements.end(); ++it)
        if ((*it)->getName() == name)
            return *it;
    return NULL;
}

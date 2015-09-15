#include "deviserversion.h"

#include "deviserclass.h"
#include "deviserenum.h"
#include "deviserplugin.h"
#include "devisermapping.h"

#include <QByteArray>
#include <QTextStream>

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

void 
DeviserVersion::initializeFrom(const QDomElement& element)
{
  DeviserBase::initializeFrom(element);

  mLevel = element.attribute("level").toInt();
  mVersion = element.attribute("version").toInt();
  mPkgVersion = element.attribute("pkg_version").toInt();
  mIgnorePackageVersion = element.attribute("ignorePackageversion") == "true";

  initializeListFrom(mElements, element, "element");
  initializeListFrom(mPlugins, element, "plugin");
  initializeListFrom(mEnums, element, "enum");
  initializeListFrom(mMappings, element, "mapping");

}

void 
DeviserVersion::writeTo(QXmlStreamWriter& writer) const
{
  writeElementsWithNameTo(writer, "pkgVersion");
}

void 
DeviserVersion::writeAttributesTo(QXmlStreamWriter& writer) const
{
  DeviserBase::writeAttributesTo(writer);

  if (mLevel != 0)
    writer.writeAttribute("level", QString::number(mLevel));
  if (mVersion != 0)
    writer.writeAttribute("version", QString::number(mVersion));
  if (mPkgVersion != 0)
    writer.writeAttribute("pkg_version", QString::number(mPkgVersion));

  if (mIgnorePackageVersion)
    writer.writeAttribute("ignorePackageVersion", "true");
}

void 
DeviserVersion::writeElementsTo(QXmlStreamWriter& writer) const
{
  DeviserBase::writeElementsTo(writer);
  
  writeListWithName(mElements, writer, "elements");
  writeListWithName(mPlugins, writer, "plugins");
  writeListWithName(mEnums, writer, "enums");
  writeListWithName(mMappings, writer, "mappings");

}

QString DeviserVersion::toString() const
{
  return QString("Version: %1,%2,%3").arg(mLevel).arg(mVersion).arg(mPkgVersion);
}

int
DeviserVersion::getLevel() const
{
  return mLevel;
}

int
DeviserVersion::getVersion() const
{
  return mVersion;
}

int
DeviserVersion::getPkgVersion() const
{
  return mPkgVersion;
}

void
DeviserVersion::setLevel(int level)
{
  if (level == mLevel) return;
  QString oldId = toString();
  mLevel = level;
  emit levelChanged();
  emit identityChanged(oldId, toString(), this);
  setModified();
}

void
DeviserVersion::setVersion(int version)
{
  if (version == mVersion) return;

  QString oldId = toString();
  mVersion = version;
  emit versionChanged();
  emit identityChanged(oldId, toString(), this);
  setModified();
}

void
DeviserVersion::setPkgVersion(int pkgVersion)
{
  if (pkgVersion == mPkgVersion) return;

  QString oldId = toString();
  mPkgVersion = pkgVersion;
  emit pkgVersionChanged();
  emit identityChanged(oldId, toString(), this);
  setModified();
}


QList<DeviserClass *> &
DeviserVersion::getElements()
{
  return mElements;
}

QList<DeviserPlugin *> &
DeviserVersion::getPlugins()
{
  return mPlugins;
}

QList<DeviserEnum *> &
DeviserVersion::getEnums()
{
  return mEnums;
}

QList<DeviserMapping *> &
DeviserVersion::getMappings()
{
  return mMappings;
}

const QList<DeviserClass *> &
DeviserVersion::getElements() const
{
  return mElements;
}

const QList<DeviserPlugin *> &
DeviserVersion::getPlugins() const
{
  return mPlugins;
}

const QList<DeviserEnum *> &
DeviserVersion::getEnums() const
{
  return mEnums;
}

const QList<DeviserMapping *> &
DeviserVersion::getMappings() const
{
  return mMappings;
}

DeviserEnum*
DeviserVersion::createEnum()
{
  DeviserEnum* element = new DeviserEnum();
  element->setName(QString("enum_%1").arg(mEnums.size()));
  mEnums.append(element);
  setParent(this->mPackage);
  setModified();
  return element;
}

DeviserClass*
DeviserVersion::createElement()
{
  DeviserClass* element = new DeviserClass();
  element->setName(QString("class_%1").arg(mElements.size()));
  mElements.append(element);
  setParent(this->mPackage);
  setModified();
  return element;
}

DeviserPlugin*
DeviserVersion::createPlugin()
{
  DeviserPlugin* element = new DeviserPlugin();
  element->setExtensionPoint(QString("plugin_%1").arg(mPlugins.size()));
  mPlugins.append(element);
  setParent(this->mPackage);
  setModified();
  return element;
}

DeviserEnum* DeviserVersion::getEnum(const QString& name)
{
  if (mEnums.empty()) return NULL;
  for (QList<DeviserEnum*>::const_iterator it = mEnums.begin(); it != mEnums.end(); ++it)
    if ((*it)->getName() == name)
      return *it;
  return NULL;
}

DeviserPlugin* DeviserVersion::getPlugin(const QString& name)
{
  if (mPlugins.empty()) return NULL;
  for (QList<DeviserPlugin*>::const_iterator it = mPlugins.begin(); it != mPlugins.end(); ++it)
    if ((*it)->getExtensionPoint() == name)
      return *it;
  return NULL;
}

DeviserClass* DeviserVersion::getElement(const QString& name)
{
  if (mElements.empty()) return NULL;
  for (QList<DeviserClass*>::const_iterator it = mElements.begin(); it != mElements.end(); ++it)
    if ((*it)->getName() == name)
      return *it;
  return NULL;
}

QString
DeviserVersion::toYuml(bool usecolor /*= true*/) const
{
  QByteArray array;
  QTextStream stream(&array, QIODevice::WriteOnly);
  stream.setCodec("UTF-8");

  foreach(const DeviserPlugin* item, mPlugins)
    stream << item->toYuml(usecolor);
  foreach(const DeviserEnum* item, mEnums)
    stream << item->toYuml(usecolor);
  foreach(const DeviserClass* item, mElements)
    stream << item->toYuml(usecolor);

  stream.flush();

  return QString::fromUtf8(array);
}
bool DeviserVersion::getIgnorePackageVersion() const
{
    return mIgnorePackageVersion;
}

void DeviserVersion::setIgnorePackageVersion(bool ignorePackageVersion)
{
    mIgnorePackageVersion = ignorePackageVersion;
    setModified();
}


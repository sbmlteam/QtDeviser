#include "deviserversion.h"

#include "deviserclass.h"
#include "deviserattribute.h"
#include "deviserconcrete.h"
#include "deviserenum.h"
#include "deviserplugin.h"
#include "devisermapping.h"
#include "util.h"

#include <QByteArray>
#include <QTextStream>
#include <algorithm>


DeviserVersion::DeviserVersion()
  : DeviserBase()
  , mLevel(0)
  , mVersion(0)
  , mPkgVersion(1)
  , mElements()
  , mPlugins()
  , mEnums()
  , mMappings()
  , mIgnorePackageVersion(false)
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
  , mIgnorePackageVersion(false)
{
  cloneElements(other.mElements, mElements);
  cloneElements(other.mPlugins, mPlugins);
  cloneElements(other.mEnums, mEnums);
  cloneElements(other.mMappings, mMappings);
  setParent(mPackage);
}

DeviserVersion &
DeviserVersion::operator=(const DeviserVersion &rhs)
{
  if (&rhs == this)
    return *this;

  mLevel = rhs.mLevel;
  mVersion = rhs.mVersion;
  mPkgVersion = rhs.mPkgVersion;
  mIgnorePackageVersion = rhs.mIgnorePackageVersion;

  cloneElements(rhs.mElements, mElements);
  cloneElements(rhs.mPlugins, mPlugins);
  cloneElements(rhs.mEnums, mEnums);
  cloneElements(rhs.mMappings, mMappings);
  setParent(mPackage);

  return *this;
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
DeviserVersion::initializeFrom(YamlSpec element)
{
  DeviserBase::initializeFrom(element);

  mLevel = 1; // element.attribute("level").toInt();
  mVersion = 1; // element.attribute("version").toInt();
  mPkgVersion = 1; // element.attribute("pkg_version").toInt();
  mIgnorePackageVersion = true; // element.attribute("ignorePackageversion") == "true";

  initializeListFrom(mElements, element, "element");
  //initializeListFrom(mPlugins, element, "plugin");
  //initializeListFrom(mEnums, element, "enum");
  //initializeListFrom(mMappings, element, "mapping");

}

void
DeviserVersion::initializeFrom(YamlClass* element)
{
  DeviserBase::initializeFrom(element);
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
  if (mPkgVersion >= 0)
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

  if (pkgVersion < 0) return;

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

bool DeviserVersion::hasMappingFor(const QString &element) const
{
  foreach(DeviserMapping* mapping, mMappings)
  {
    if (mapping->getName() == element)
      return true;
  }
  return false;
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

void DeviserVersion::initializeMappings()
{
  QList<QString> usedClasses = getUsedClasses();

  foreach(QString element,Util::getCoreClasses())
    usedClasses.removeAll(element);
  foreach(QString element,getDefinedClasses())
    usedClasses.removeAll(element);

  usedClasses.removeAll("ASTNode*");
  usedClasses.removeAll("const ASTNode*");
  usedClasses.removeAll("XMLNode*");
  usedClasses.removeAll("const XMLNode*");

  foreach(QString item, usedClasses)
  {
    if (!hasMappingFor(item))
    {
      DeviserMapping* mapping = new DeviserMapping();
      mapping->setName(item);
      mapping->setParent(mPackage);
      mMappings << mapping;
    }
  }
}

QList<QString> DeviserVersion::getUsedClasses() const
{
  QList<QString> result;

  foreach (DeviserClass* element, mElements)
  {
    if (!element->getBaseClass().isEmpty() &&
        !result.contains(element->getBaseClass()))
      result << element->getBaseClass();

    foreach (DeviserAttribute* attribute, element->getAttributes())
    {
      if (attribute->getType() == "element" ||
          attribute->getType() == "inline_lo_element" )
        if (!result.contains(attribute->getElement()))
          result << attribute->getElement();
    }

    foreach(DeviserConcrete* concrete, element->getConcretes())
    {
      if (!result.contains(concrete->getElement()))
        result << concrete->getElement();
    }

  }

  foreach (DeviserPlugin* element, mPlugins)
  {
    if (!element->getExtensionPoint().isEmpty() &&
        !result.contains(element->getExtensionPoint()))
      result << element->getExtensionPoint();

    foreach (DeviserAttribute* attribute, element->getAttributes())
    {
      if (attribute->getType() == "element" ||
          attribute->getType() == "inline_lo_element" )
        if (!result.contains(attribute->getElement()))
          result << attribute->getElement();
    }
  }

  std::sort(result.begin(), result.end());
  return result;
}

QList<QString> DeviserVersion::getDefinedClasses() const
{
  QList<QString> result;

  foreach (DeviserClass* element, mElements)
  {
    if (!element->getName().isEmpty() &&
        !result.contains(element->getName()))
      result << element->getName();
  }

  std::sort(result.begin(), result.end());
  return result;
}

void
DeviserVersion::getUsedTypes(QStringList &list) const
{
  foreach (DeviserClass* element, mElements)
  {
    element->getUsedTypes(list);
  }

  foreach (DeviserPlugin* element, mPlugins)
  {
    element->getUsedTypes(list);
  }

}


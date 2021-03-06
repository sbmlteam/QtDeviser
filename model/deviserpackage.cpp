#include "deviserpackage.h"
#include "deviserversion.h"

#include <QFile>
#include <QDomDocument>
#include <QByteArray>
#include <QTextStream>
#include <QStringList>

DeviserPackage::DeviserPackage()
  : DeviserBase()
  , mName()
  , mFullName()
  , mStartNumber(0)
  , mOffset(0)
  , mVersion(1)
  , mRequired(false)
  , mAdditionalDeclarations()
  , mAdditionalDefinitions()
  , mVersions()
  , mModified(false)
  , mLanguage()
  , mCustomCopyright()
{
  createVersion();
  setParent(this);
}

DeviserPackage::DeviserPackage(const DeviserPackage& other)
  : DeviserBase(other)
  , mName(other.mName)
  , mFullName(other.mFullName)
  , mStartNumber(other.mStartNumber)
  , mOffset(other.mOffset)
  , mRequired(other.mRequired)
  , mAdditionalDeclarations(other.mAdditionalDeclarations)
  , mAdditionalDefinitions(other.mAdditionalDefinitions)
  , mVersions()
  , mModified(false)
  , mLanguage(other.mLanguage)
  , mCustomCopyright(other.mCustomCopyright)
{
  cloneElements(other.mVersions, mVersions);
  setParent(this);
}

DeviserPackage::DeviserPackage(const QString& fileName)
  : DeviserBase()
  , mName()
  , mFullName()
  , mStartNumber(0)
  , mOffset(0)
  , mVersion(1)
  , mRequired(false)
  , mAdditionalDeclarations()
  , mAdditionalDefinitions()
  , mVersions()
  , mModified(false)
  , mLanguage()
  , mCustomCopyright()
{
  QDomDocument document (fileName);
  QFile file(fileName);
  document.setContent(&file);
  QDomElement root = document .documentElement();
  initializeFrom(root);
  mModified = false;
}

DeviserPackage::DeviserPackage(QDomElement& element)
  : DeviserBase()
  , mName()
  , mFullName()
  , mStartNumber(0)
  , mOffset(0)
  , mVersion(1)
  , mRequired(false)
  , mAdditionalDeclarations()
  , mAdditionalDefinitions()
  , mVersions()
  , mModified(false)
  , mLanguage()
  , mCustomCopyright()
{
  initializeFrom(element);
}

DeviserPackage &
DeviserPackage::operator=(const DeviserPackage &rhs)
{
  if (&rhs == this)
    return *this;

  DeviserBase::operator =(rhs);
  mName = rhs.mName;
  mFullName = rhs.mFullName;
  mStartNumber = rhs.mStartNumber;
  mOffset = rhs.mOffset;
  mRequired = rhs.mRequired;
  mAdditionalDeclarations = rhs.mAdditionalDeclarations;
  mAdditionalDefinitions = rhs.mAdditionalDefinitions;
  mModified = false;
  mLanguage = rhs.mLanguage;
  mCustomCopyright = rhs.mCustomCopyright;

  cloneElements(rhs.mVersions, mVersions);
  setParent(this);

  return *this;
}

DeviserVersion*
DeviserPackage::createVersion()
{
  DeviserVersion* newVersion = new DeviserVersion();

  int level = 3;
  int version = 1;
  int pkgVersion = 1;
  while (getVersion(level, version, pkgVersion)!=NULL)
    ++pkgVersion;

  newVersion->setLevel(level);
  newVersion->setVersion(version);
  newVersion->setPkgVersion(pkgVersion);

  mVersions.append(newVersion);

  setModified(true);

  return newVersion;
}

bool
DeviserPackage::getModified() const
{
  return mModified;
}

void
DeviserPackage::setModified(bool modified)
{
  if (mModified == modified)
    return;

  mModified = modified;
  emit modifiedChanged();
}

const DeviserLanguage&
DeviserPackage::getLanguage() const
{
  return mLanguage;
}

DeviserLanguage&
DeviserPackage::getLanguage()
{
  return mLanguage;
}

void
DeviserPackage::setLanguage(const DeviserLanguage &language)
{
  mLanguage = language;
}

QString
DeviserPackage::getDefaultListOfClass() const
{
  if (!mLanguage.listOfClass().isEmpty())
    return mLanguage.listOfClass();
  return "ListOf";
}

QStringList
DeviserPackage::getUsedTypes() const
{
  QStringList result;
  foreach (DeviserVersion* version, mVersions)
  {
    version->getUsedTypes(result);
  }

  return result;
}
QString DeviserPackage::getCustomCopyright() const
{
  return mCustomCopyright;
}

void DeviserPackage::setCustomCopyright(const QString& customCopyright)
{
  mCustomCopyright = customCopyright;
}


void
DeviserPackage::initializeFrom(const QDomElement& element)
{
  DeviserBase::initializeFrom(element);

  mName = element.attribute("name");
  mFullName = element.attribute("fullname");
  mAdditionalDeclarations = element.attribute("additionalDecls");
  mAdditionalDefinitions = element.attribute("additionalDefs");


  mStartNumber = element.attribute("number").toInt();
  mOffset = element.attribute("offset").toInt();
  mVersion = element.attribute("version").toInt();
  mRequired = element.attribute("required").toLower() == "true";

  mCustomCopyright = element.attribute("customCopyright");

  initializeListFrom(mVersions, element, "pkgVersion");

  initializeElementFrom(mLanguage, element, "language");

  setParent(this);

}

void
DeviserPackage::setParent(DeviserPackage* doc)
{
  DeviserBase::setParent(doc);

  setParentOn(mVersions, doc);

  mLanguage.setParent(doc);
}

QString
DeviserPackage::toYuml(bool usecolor ) const
{
  QByteArray array;
  QTextStream stream(&array, QIODevice::WriteOnly);
  stream.setCodec("UTF-8");

  foreach (const DeviserVersion* version, mVersions)
    stream << version->toYuml(usecolor);

  return QString::fromUtf8(array);

}

void
DeviserPackage::writeAttributesTo(QXmlStreamWriter& writer) const
{
  DeviserBase::writeAttributesTo(writer);

  if (!mName.isEmpty())
    writer.writeAttribute("name", mName);

  if (!mFullName.isEmpty())
    writer.writeAttribute("fullname", mFullName);

  if (mStartNumber != 0)
    writer.writeAttribute("number", QString::number(mStartNumber));

  if (mOffset!= 0)
    writer.writeAttribute("offset", QString::number( mOffset));

  // version here is now re-used to track the xml version
  if (mVersion == 0)
    const_cast<DeviserPackage*>(this)->mVersion = 1;

  writer.writeAttribute("version", QString::number(mVersion));

  writer.writeAttribute("required", mRequired ? "true" : "false");

  if (!mAdditionalDeclarations.isEmpty())
    writer.writeAttribute("additionalDecls", mAdditionalDeclarations);
  if (!mAdditionalDefinitions.isEmpty())
    writer.writeAttribute("additionalDefs", mAdditionalDefinitions);

  if (!mCustomCopyright.isEmpty())
    writer.writeAttribute("customCopyright", mCustomCopyright);
}

void
DeviserPackage::writeElementsTo(QXmlStreamWriter& writer) const
{
  DeviserBase::writeElementsTo(writer);

  if (!mLanguage.isEmpty())
    mLanguage.writeTo(writer);

  writeListWithName(mVersions, writer, "versions");

}

void
DeviserPackage::writeTo(QXmlStreamWriter& writer) const
{
  writeElementsWithNameTo(writer, "package");
}

void DeviserPackage::writeTo(const QString& fileName) const
{
  QFile file(fileName);
  if (!file.open(QIODevice::WriteOnly))
    return;
  QXmlStreamWriter writer(&file);
  writer.setAutoFormatting(true);
  writer.setAutoFormattingIndent(2);
  writer.setCodec("UTF-8");
  writer.writeStartDocument();
  writeTo(writer);
  writer.writeEndDocument();
  file.close();

  const_cast<DeviserPackage*>(this)->setModified(false);

}

QList<DeviserVersion *> &
DeviserPackage::getVersions()
{
  return mVersions;
}

const QList<DeviserVersion *> &
DeviserPackage::getVersions() const
{
  return mVersions;
}


const QString&
DeviserPackage::getName() const
{
  return mName;
}

void
DeviserPackage::setName(const QString &name)
{
  mName = name;
  emit nameChanged();
  setModified(true);
}

const QString&
DeviserPackage::getFullName() const
{
  return mFullName;
}

void
DeviserPackage::setFullName(const QString &fullName)
{
  mFullName = fullName;
  emit fullNameChanged();
  setModified(true);
}

int
DeviserPackage::getStartNumber() const
{
  return mStartNumber;
}

void
DeviserPackage::setStartNumber(int startNumber)
{
  mStartNumber = startNumber;
  emit startNumberChanged();
  setModified(true);
}

int
DeviserPackage::getOffset() const
{
  return mOffset;
}

void
DeviserPackage::setOffset(int offset)
{
  mOffset = offset;
  emit offsetChanged();
  setModified(true);
}

int
DeviserPackage::getVersion() const
{
  return mVersion;
}

void
DeviserPackage::setVersion(int version)
{
  mVersion = version;
  emit versionChanged();
  setModified(true);
}

bool
DeviserPackage::isRequired() const
{
  return mRequired;
}

void
DeviserPackage::setRequired(bool isRequired)
{
  mRequired = isRequired;
  emit requiredChanged();
  setModified(true);
}

const QString&
DeviserPackage::getAdditionalDeclarations() const
{
  return mAdditionalDeclarations;
}

void
DeviserPackage::setAdditionalDeclarations(const QString &additionalDeclarations)
{
  mAdditionalDeclarations = additionalDeclarations;
  emit additionalDeclarationsChanged();
  setModified(true);
}

const QString&
DeviserPackage::getAdditionalDefinitions() const
{
  return mAdditionalDefinitions;
}

void
DeviserPackage::setAdditionalDefinitions(const QString &additionalDefinitions)
{
  mAdditionalDefinitions = additionalDefinitions;
  emit additionalDefinitionsChanged();
  setModified(true);
}

DeviserVersion*
DeviserPackage::getVersion(const QString& name)
{
  if (mVersions.empty()) return NULL;
  for (QList<DeviserVersion*>::const_iterator it = mVersions.begin(); it != mVersions.end(); ++it)
    if ((*it)->toString() == name)
      return *it;
  return NULL;
}

DeviserVersion*
DeviserPackage::getVersion(int level, int version, int pkgVersion)
{
  return getVersion(QString("Version: %1,%2,%3").arg(level).arg(version).arg(pkgVersion));
}

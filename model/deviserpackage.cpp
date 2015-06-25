#include "deviserpackage.h"
#include "deviserversion.h"

#include <QFile>
#include <QDomDocument>

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
{
  QDomDocument document (fileName);
  QFile file(fileName);
  document.setContent(&file);
  QDomElement root = document .documentElement();
  initializeFrom(root);
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
{
    initializeFrom(element);
}

DeviserVersion*
DeviserPackage::createVersion(int level, int version, int pkgVersion)
{
    DeviserVersion* newVersion = new DeviserVersion();
    newVersion->setLevel(level);
    newVersion->setVersion(version);
    newVersion->setPkgVersion(pkgVersion);

    mVersions.append(newVersion);

    return newVersion;
}

void DeviserPackage::initializeFrom(const QDomElement& element)
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

   initializeListFrom(mVersions, element, "pkgVersion");

   setParent(this);

}

void DeviserPackage::setParent(DeviserPackage* doc)
{
    DeviserBase::setParent(doc);

    setParentOn(mVersions, doc);
}

QString DeviserPackage::toXmlString() const
{
 return "";
}

QString DeviserPackage::toYuml(bool usecolor ) const
{
return "";
}

void DeviserPackage::writeAttributesTo(QXmlStreamWriter& writer) const
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

}

void DeviserPackage::writeElementsTo(QXmlStreamWriter& writer) const
{
    DeviserBase::writeElementsTo(writer);

    writeListWithName(mVersions, writer, "versions");

}

void DeviserPackage::writeTo(QXmlStreamWriter& writer) const
{
  writeElementsWithNameTo(writer, "package");
}

void DeviserPackage::writeTo(const QString& fileName) const
{
  QFile file(fileName);
  QXmlStreamWriter writer(&file);
  writer.setAutoFormatting(true);
  writer.setAutoFormattingIndent(2);
  writer.setCodec("UTF-8");
  writer.writeStartDocument();
  writeTo(writer);
  writer.writeEndDocument();
}


const QString& DeviserPackage::getName() const { return mName; }
const QString& DeviserPackage::getFullName() const { return mFullName; }
int DeviserPackage::getStartNumber() const { return mStartNumber; }
int DeviserPackage::getOffset() const { return mOffset; }
int DeviserPackage::getVersion() const { return mVersion; }
bool DeviserPackage::isRequired() const { return mRequired; }
const QString& DeviserPackage::getAdditionalDeclarations() const { return mAdditionalDeclarations; }
const QString& DeviserPackage::getAdditionalDefinitions() const { return mAdditionalDefinitions; }

DeviserVersion* DeviserPackage::getVersion(const QString& name)
{
  if (mVersions.empty()) return NULL;
    for (auto it = mVersions.begin(); it != mVersions.end(); ++it)
        if ((*it)->toString() == name)
            return *it;
    return NULL;
}

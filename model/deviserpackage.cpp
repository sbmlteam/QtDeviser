#include "deviserpackage.h"

#include <QFile>
#include <QDomDocument>

DeviserPackage::DeviserPackage()
{

}

DeviserPackage::DeviserPackage(const DeviserPackage& other)
{

}

DeviserPackage::DeviserPackage(const QString& fileName)
{
  QDomDocument document (fileName);
  QDomElement root = document .documentElement();
  initializeFrom(root);
}

DeviserPackage::DeviserPackage(QDomElement& element)
{
    initializeFrom(element);
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

   mCurrentVersion = NULL;
   if (!mVersions.empty())
     mCurrentVersion = &*mVersions.begin();

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

#include "deviserplugin.h"

#include "deviserreferenceattribute.h"
#include "deviserattribute.h"

DeviserPlugin::DeviserPlugin()
  : DeviserBase()
  , mExtensionPoint()
  , mAdditionalDeclarations()
  , mAdditionalDefinitions()
  , mTypeCode()
  , mPackage()
  , mReferences()
  , mAttributes()
{

}

DeviserPlugin::DeviserPlugin(const DeviserPlugin& other)
  : DeviserBase(other)
  , mExtensionPoint(other.mExtensionPoint)
  , mAdditionalDeclarations(other.mAdditionalDeclarations)
  , mAdditionalDefinitions(other.mAdditionalDefinitions)
  , mTypeCode(other.mTypeCode)
  , mPackage(other.mPackage)
  , mReferences()
  , mAttributes()
{
  cloneElements(other.mReferences, mReferences);
  cloneElements(other.mAttributes, mAttributes);
}

void
DeviserPlugin::initializeFrom(const QDomElement& element)
{
    DeviserBase::initializeFrom(element);

    mExtensionPoint = element.attribute("extensionPoint");
    mAdditionalDeclarations = element.attribute("additionalDecls");
    mAdditionalDefinitions = element.attribute("additionalDefs");
    mTypeCode = element.attribute("typecode");
    mPackage = element.attribute("package");

    initializeListFrom(mReferences, element, "reference");
    initializeListFrom(mAttributes, element, "attribute");
}


void
DeviserPlugin::writeAttributesTo(QXmlStreamWriter& writer) const
{
  DeviserBase::writeAttributesTo(writer);

  if (!mTypeCode.isEmpty())
    writer.writeAttribute("typecode", mTypeCode);
  if (!mPackage.isEmpty())
    writer.writeAttribute("package", mPackage);
  if (!mExtensionPoint.isEmpty())
    writer.writeAttribute("extensionPoint", mExtensionPoint);
  if (!mAdditionalDeclarations.isEmpty())
    writer.writeAttribute("additionalDecls", mAdditionalDeclarations);
  if (!mAdditionalDefinitions.isEmpty())
    writer.writeAttribute("additionalDefs", mAdditionalDefinitions);
}

void
DeviserPlugin::writeElementsTo(QXmlStreamWriter& writer) const
{
  DeviserBase::writeElementsTo(writer);
  
  writeListWithName(mReferences, writer, "references");
  writeListWithName(mAttributes, writer, "attributes");
}

void
DeviserPlugin::writeTo(QXmlStreamWriter& writer) const
{
  writeElementsWithNameTo(writer, "plugin");
}

#include "devisermapping.h"

DeviserMapping::DeviserMapping()
 : DeviserBase()
 , mName()
 , mPackage()
{

}

DeviserMapping::DeviserMapping(const DeviserMapping& other)
 : DeviserBase(other)
 , mName(other.mName)
 , mPackage(other.mPackage)
{

}

void
DeviserMapping::initializeFrom(const QDomElement& element)
{
    DeviserBase::initializeFrom(element);

    mName = element.attribute("name");
    mPackage = element.attribute("package");
}

void 
DeviserMapping::writeAttributesTo(QXmlStreamWriter& writer) const
{
  DeviserBase::writeAttributesTo(writer);

  if (!mName.isEmpty())
    writer.writeAttribute("name", mName);
  if (!mPackage.isEmpty())
    writer.writeAttribute("package", mPackage);

}

void 
DeviserMapping::writeTo(QXmlStreamWriter& writer) const
{
  writeElementsWithNameTo(writer, "mapping");
}


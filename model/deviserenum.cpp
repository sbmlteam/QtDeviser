#include "deviserenum.h"

#include "deviserenumvalue.h"

DeviserEnum::DeviserEnum()
  : DeviserBase()
  , mName()
  , mValues()
{

}

DeviserEnum::DeviserEnum(const DeviserEnum& other)
  : DeviserBase(other)
  , mName(other.mName)
  , mValues()
{
  cloneElements(other.mValues, mValues);
  setParent(mPackage);
}

void
DeviserEnum::initializeFrom(const QDomElement& element)
{
  DeviserBase::initializeFrom(element);

  mName = element.attribute("name");

  initializeListFrom(mValues, element, "enumValue");

}

void 
DeviserEnum::writeAttributesTo(QXmlStreamWriter& writer) const
{
  DeviserBase::writeAttributesTo(writer);

  if (!mName.isEmpty())
    writer.writeAttribute("name", mName);

}

void 
DeviserEnum::writeElementsTo(QXmlStreamWriter& writer) const
{
  DeviserBase::writeElementsTo(writer);

  writeListWithName(mValues, writer, "enumValues");

}

void 
DeviserEnum::writeTo(QXmlStreamWriter& writer) const
{
  writeElementsWithNameTo(writer, "enum");
}

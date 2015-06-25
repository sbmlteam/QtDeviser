#include "deviserenumvalue.h"

DeviserEnumValue::DeviserEnumValue()
  : DeviserBase()
  , mName()
  , mValue()
{

}

DeviserEnumValue::DeviserEnumValue(const DeviserEnumValue& other)
  : DeviserBase(other)
  , mName(other.mName)
  , mValue(other.mValue)
{

}

void
DeviserEnumValue::initializeFrom(const QDomElement& element)
{
    DeviserBase::initializeFrom(element);

    mName = element.attribute("name");
    mValue = element.attribute("value");

}

void 
DeviserEnumValue::writeAttributesTo(QXmlStreamWriter& writer) const
{
  DeviserBase::writeAttributesTo(writer);
  if (!mName.isEmpty())
    writer.writeAttribute("name", mName);
  if (!mValue.isEmpty())
    writer.writeAttribute("value", mValue);
}

void 
DeviserEnumValue::writeTo(QXmlStreamWriter& writer) const
{
  writeElementsWithNameTo(writer, "enumValue");
}

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

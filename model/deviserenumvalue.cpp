#include "deviserenumvalue.h"

DeviserEnumValue::DeviserEnumValue()
{

}

void
DeviserEnumValue::initializeFrom(const QDomElement& element)
{
    DeviserBase::initializeFrom(element);

    mName = element.attribute("name");
    mValue = element.attribute("value");

}

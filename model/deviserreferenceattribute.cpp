#include "deviserreferenceattribute.h"

DeviserReferenceAttribute::DeviserReferenceAttribute()
  : DeviserBase()
  , mName()
{

}

DeviserReferenceAttribute::DeviserReferenceAttribute(const DeviserReferenceAttribute& other)
  : DeviserBase(other)
  , mName(other.mName)
{

}

void
DeviserReferenceAttribute::initializeFrom(const QDomElement& element)
{
    DeviserBase::initializeFrom(element);
    mName = element.attribute("name");
}

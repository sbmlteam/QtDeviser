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

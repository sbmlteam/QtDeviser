#include "deviserenum.h"

#include "deviserenumvalue.h"

DeviserEnum::DeviserEnum()
{

}

void
DeviserEnum::initializeFrom(const QDomElement& element)
{
  DeviserBase::initializeFrom(element);

  mName = element.attribute("name");

  initializeListFrom(mValues, element, "enumValue");

}

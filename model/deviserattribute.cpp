#include "deviserattribute.h"

DeviserAttribute::DeviserAttribute()
{

}

void DeviserAttribute::initializeFrom(const QDomElement& element)
{
  DeviserReferenceAttribute::initializeFrom(element);

  mType = element.attribute("type");
  mElement = element.attribute("element");
  mXMLName = element.attribute("xmlName");
  mRequired = element.attribute("required").toLower() == "true";
  mAbstract = element.attribute("abstract").toLower() == "true";

}

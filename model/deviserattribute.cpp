#include "deviserattribute.h"

DeviserAttribute::DeviserAttribute()
 : DeviserReferenceAttribute()
 , mXMLName()
 , mType()
 , mElement()
 , mRequired(false)
 , mAbstract(false)
{

}

DeviserAttribute::DeviserAttribute(const DeviserAttribute& other)
 : DeviserReferenceAttribute(other)
 , mXMLName(other.mXMLName)
 , mType(other.mType)
 , mElement(other.mElement)
 , mRequired(other.mRequired)
 , mAbstract(other.mAbstract)
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

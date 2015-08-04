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

void
DeviserAttribute::initializeFrom(const QDomElement& element)
{
  DeviserReferenceAttribute::initializeFrom(element);

  mRequired = element.attribute("required").toLower() == "true";
  mType = element.attribute("type");
  mElement = element.attribute("element");
  mXMLName = element.attribute("xmlName");
  mAbstract = element.attribute("abstract").toLower() == "true";

}

const QString &
DeviserAttribute::getXMLName() const
{
  return mXMLName;
}

void
DeviserAttribute::setXMLName(const QString &name)
{
  mXMLName = name;
  emit xmlNameChanged();
}

const QString &
DeviserAttribute::getType() const
{
  return mType;
}

void
DeviserAttribute::setType(const QString &type)
{
  mType = type;
  emit typeChanged();
}

const QString &
DeviserAttribute::getElement() const
{
  return mElement;
}

void
DeviserAttribute::setElement(const QString &element)
{
  mElement = element;
  emit elementChanged();
}

bool
DeviserAttribute::getRequired() const
{
  return mRequired;
}

void
DeviserAttribute::setRequired(bool isRequired)
{
  mRequired = isRequired;
  emit requiredChanged();
}

bool
DeviserAttribute::getAbstract() const
{
  return mAbstract;
}

void
DeviserAttribute::setAbstract(bool isAbstract)
{
  mAbstract = isAbstract;
  emit abstractChanged();
}

void
DeviserAttribute::writeAttributesTo(QXmlStreamWriter& writer) const
{
  DeviserReferenceAttribute::writeAttributesTo(writer);

  writer.writeAttribute("required", mRequired ? "true" : "false");
  if (!mType.isEmpty())
    writer.writeAttribute("type", mType);
  if (!mElement.isEmpty())
    writer.writeAttribute("element", mElement);
  if (!mXMLName.isEmpty())
    writer.writeAttribute("xmlName", mXMLName);

  writer.writeAttribute("abstract", mAbstract ? "true" : "false");

}

void
DeviserAttribute::writeTo(QXmlStreamWriter& writer) const
{
  writeElementsWithNameTo(writer, "attribute");
}

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

const QString &
DeviserReferenceAttribute::getName() const
{
  return mName;
}

void
DeviserReferenceAttribute::setName(const QString &name)
{
  mName = name;
  emit nameChanged();
}

void 
DeviserReferenceAttribute::writeAttributesTo(QXmlStreamWriter& writer) const
{
  DeviserBase::writeAttributesTo(writer);
  
  if (!mName.isEmpty())
    writer.writeAttribute("name", mName);

}

void 
DeviserReferenceAttribute::writeTo(QXmlStreamWriter& writer) const
{
  writeElementsWithNameTo(writer, "reference");
}

QString
DeviserReferenceAttribute::toYuml(bool /*usecolor = true*/) const
{
  return mName;
}

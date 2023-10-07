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

DeviserReferenceAttribute &
DeviserReferenceAttribute::operator=(const DeviserReferenceAttribute &rhs)
{
  if (&rhs == this)
    return *this;

  DeviserBase::operator =(rhs);
  mName = rhs.mName;

  return *this;
}

void
DeviserReferenceAttribute::initializeFrom(const QDomElement& element)
{
  DeviserBase::initializeFrom(element);
  mName = element.attribute("name");
}


void
DeviserReferenceAttribute::initializeFrom(idPair element)
{
  DeviserBase::initializeFrom(element);
  mName = QString::fromUtf8(element.first.c_str());
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
  setModified();
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

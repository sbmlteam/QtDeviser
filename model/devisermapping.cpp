#include "devisermapping.h"

DeviserMapping::DeviserMapping()
  : DeviserBase()
  , mName()
  , mPackage()
{

}

DeviserMapping::DeviserMapping(const DeviserMapping& other)
  : DeviserBase(other)
  , mName(other.mName)
  , mPackage(other.mPackage)
{

}

void
DeviserMapping::initializeFrom(const QDomElement& element)
{
  DeviserBase::initializeFrom(element);

  mName = element.attribute("name");
  mPackage = element.attribute("package");
}

const QString &
DeviserMapping::getName() const
{
  return mName;
}

void
DeviserMapping::setName(const QString &name)
{
  mName = name;
  emit nameChanged();
}

const QString &
DeviserMapping::getPackage() const
{
  return mPackage;
}

void
DeviserMapping::setPackage(const QString &package)
{
  mPackage = package;
  emit packageChanged();
}

void 
DeviserMapping::writeAttributesTo(QXmlStreamWriter& writer) const
{
  DeviserBase::writeAttributesTo(writer);

  if (!mName.isEmpty())
    writer.writeAttribute("name", mName);
  if (!mPackage.isEmpty())
    writer.writeAttribute("package", mPackage);

}

void 
DeviserMapping::writeTo(QXmlStreamWriter& writer) const
{
  writeElementsWithNameTo(writer, "mapping");
}


#include "deviserbase.h"

DeviserBase::DeviserBase()
  : mPackage(NULL)
  , mVersion(NULL)
  , mUserData(NULL)
{

}

DeviserBase::DeviserBase(const DeviserBase &other)
  : mPackage(other.mPackage)
  , mVersion(NULL)
  , mUserData(NULL)
{

}

void DeviserBase::initializeFrom(const QDomElement& )
{

}

void DeviserBase::setParent(DeviserPackage* doc)
{
  mPackage = doc;
}

void DeviserBase::setParentVersion(DeviserVersion* version)
{
  mVersion = version;
}

QString DeviserBase::toXmlString() const
{
  return QString();
}

QString DeviserBase::toYuml(bool usecolor) const
{
  return QString();
}

void DeviserBase::writeAttributesTo(QXmlStreamWriter& ) const
{

}

void DeviserBase::writeElementsTo(QXmlStreamWriter& ) const
{

}

void DeviserBase::writeTo(QXmlStreamWriter& writer) const
{
  writeAttributesTo(writer);
  writeElementsTo(writer);
}
void DeviserBase::writeElementsWithNameTo(QXmlStreamWriter& writer, const QString& name) const
{
  writer.writeStartElement(name);
  DeviserBase::writeTo(writer);
  writer.writeEndElement();
}

DeviserPackage*
DeviserBase::getParent()
{
  return mPackage;
}

DeviserVersion*
DeviserBase::getParentVersion()
{
  return mVersion;
}

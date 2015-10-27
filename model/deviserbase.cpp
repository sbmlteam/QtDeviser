#include "deviserbase.h"

#include "deviserpackage.h"

#include <QTextStream>
#include <QXmlStreamWriter>

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

DeviserBase &
DeviserBase::operator=(const DeviserBase &rhs)
{
  if (&rhs == this)
    return *this;

  mPackage = rhs.mPackage;
  mVersion = rhs.mVersion;
  mUserData = rhs.mUserData;

  return *this;

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
  QByteArray array;

  QXmlStreamWriter writer(&array);
  writer.setAutoFormatting(true);  
  writer.setAutoFormattingIndent(2);
  writer.setCodec("UTF-8");
  writer.writeStartDocument();
  writeTo(writer);
  writer.writeEndDocument();
  
  return QString::fromUtf8(array);  
}

QString DeviserBase::toYuml(bool /*usecolor*/) const
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
void DeviserBase::writeElementsWithNameTo(
    QXmlStreamWriter& writer,
    const QString& name) const
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

void
DeviserBase::setModified()
{
  if (mPackage == NULL)
    return;

  mPackage->setModified(true);
}

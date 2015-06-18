#include "deviserbase.h"

DeviserBase::DeviserBase()
{

}

DeviserBase::DeviserBase(const DeviserBase &)
{

}

void DeviserBase::initializeFrom(const QDomElement& )
{

}

void DeviserBase::setParent(DeviserPackage* doc)
{
    mPackage = doc;
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
    writeTo(writer);
    writer.writeEndElement();
}

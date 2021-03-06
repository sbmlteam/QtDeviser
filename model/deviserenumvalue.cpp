#include "deviserenumvalue.h"

DeviserEnumValue::DeviserEnumValue()
  : DeviserBase()
  , mName()
  , mValue()
{

}

DeviserEnumValue::DeviserEnumValue(const DeviserEnumValue& other)
  : DeviserBase(other)
  , mName(other.mName)
  , mValue(other.mValue)
{

}

DeviserEnumValue &
DeviserEnumValue::operator=(const DeviserEnumValue &rhs)
{
  if (&rhs == this)
    return *this;

  DeviserBase::operator =(rhs);

  mName = rhs.mName;
  mValue = rhs.mValue;

  return *this;
}

void
DeviserEnumValue::initializeFrom(const QDomElement& element)
{
  DeviserBase::initializeFrom(element);

  mName = element.attribute("name");
  mValue = element.attribute("value");

}

const QString &
DeviserEnumValue::getName() const
{
  return mName;
}

void
DeviserEnumValue::setName(const QString &name)
{
  mName = name;
  emit nameChanged();
  setModified();
}

const QString &
DeviserEnumValue::getValue() const
{
  return mValue;
}

void
DeviserEnumValue::setValue(const QString &value)
{
  mValue = value;
  emit valueChanged();
  setModified();
}

void 
DeviserEnumValue::writeAttributesTo(QXmlStreamWriter& writer) const
{
  DeviserBase::writeAttributesTo(writer);
  if (!mName.isEmpty())
    writer.writeAttribute("name", mName);
  if (!mValue.isEmpty())
    writer.writeAttribute("value", mValue);
}

void 
DeviserEnumValue::writeTo(QXmlStreamWriter& writer) const
{
  writeElementsWithNameTo(writer, "enumValue");
}

QString
DeviserEnumValue::toYuml(bool /*usecolor*/) const
{
  if (mValue.isEmpty()) return mName;
  return QString("%1 = %2").arg(mName, mValue);
}


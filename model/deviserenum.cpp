#include "deviserenum.h"

#include "deviserenumvalue.h"

DeviserEnum::DeviserEnum()
  : DeviserBase()
  , mName()
  , mValues()
{

}

DeviserEnum::DeviserEnum(const DeviserEnum& other)
  : DeviserBase(other)
  , mName(other.mName)
  , mValues()
{
  cloneElements(other.mValues, mValues);
  setParent(mPackage);
}

void
DeviserEnum::initializeFrom(const QDomElement& element)
{
  DeviserBase::initializeFrom(element);

  mName = element.attribute("name");

  initializeListFrom(mValues, element, "enumValue");

}

const QString &
DeviserEnum::getName() const
{
  return mName;
}

void
DeviserEnum::setName(const QString &name)
{
  if (name == mName) return;

  QString oldName(mName);
  mName = name;

  if (!name.isEmpty())
  emit nameChanged(oldName, name);
}

const QList<DeviserEnumValue *> &
DeviserEnum::getValues() const
{
  return mValues;
}

QList<DeviserEnumValue *> &
DeviserEnum::getValues()
{
  return mValues;
}

DeviserEnumValue*
DeviserEnum::createValue()
{
  DeviserEnumValue *result = new DeviserEnumValue();
  result->setName(QString("value_%1").arg(mValues.size()));
  mValues.append(result);
  setParent(mPackage);
  return result;
}

void 
DeviserEnum::writeAttributesTo(QXmlStreamWriter& writer) const
{
  DeviserBase::writeAttributesTo(writer);

  if (!mName.isEmpty())
    writer.writeAttribute("name", mName);

}

void 
DeviserEnum::writeElementsTo(QXmlStreamWriter& writer) const
{
  DeviserBase::writeElementsTo(writer);

  writeListWithName(mValues, writer, "enumValues");

}

void 
DeviserEnum::writeTo(QXmlStreamWriter& writer) const
{
  writeElementsWithNameTo(writer, "enum");
}

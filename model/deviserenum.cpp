#include "deviserenum.h"

#include "deviserenumvalue.h"
#include "util.h"

#include <QByteArray>
#include <QTextStream>

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
  emit nameChanged(oldName, name, mVersion);
  setModified();
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
  setModified();
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

QString
DeviserEnum::toYuml(bool usecolor /*= true*/) const
{
  QByteArray array;
  QTextStream stream(&array, QIODevice::WriteOnly);
  stream.setCodec("UTF-8");

  stream << "[" << Util::getEnumPrefix() << mName;

  if (!mValues.empty())
    stream << "|";

  for (int i = 0; i < mValues.count(); ++i)
  {
    stream << mValues[i]->toYuml();

    if (i+1 < mValues.count())
      stream << ";";

  }
  if (usecolor)
    stream << "{bg:" << Util::getEnumColor() <<  "}";

  stream << "]" << endl;

  return QString::fromUtf8(array);
}

#include "devisermapping.h"

DeviserMapping::DeviserMapping()
  : DeviserBase()
  , mName()
  , mPackageName()
{

}

DeviserMapping::DeviserMapping(const DeviserMapping& other)
  : DeviserBase(other)
  , mName(other.mName)
  , mPackageName(other.mPackageName)
{

}

DeviserMapping &
DeviserMapping::operator=(const DeviserMapping &rhs)
{
  if (&rhs == this)
    return *this;

  DeviserBase::operator =(rhs);
  mName = rhs.mName;
  mPackageName = rhs.mPackageName;

  return *this;
}

void
DeviserMapping::initializeFrom(const QDomElement& element)
{
  DeviserBase::initializeFrom(element);

  mName = element.attribute("name");
  mPackageName = element.attribute("package");
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
  setModified();
}

const QString &
DeviserMapping::getPackage() const
{
  return mPackageName;
}

void
DeviserMapping::setPackage(const QString &package)
{
  mPackageName = package;
  emit packageChanged();
  setModified();
}

void 
DeviserMapping::writeAttributesTo(QXmlStreamWriter& writer) const
{
  DeviserBase::writeAttributesTo(writer);

  if (!mName.isEmpty())
    writer.writeAttribute("name", mName);
  if (!mPackageName.isEmpty())
    writer.writeAttribute("package", mPackageName);

}

void 
DeviserMapping::writeTo(QXmlStreamWriter& writer) const
{
  writeElementsWithNameTo(writer, "mapping");
}


QString
DeviserMapping::toYuml(bool /*usecolor */) const
{
  if (mPackageName.isEmpty()) return mName;
  return QString("%1 = %2").arg(mName, mPackageName);
}

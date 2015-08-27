
#include "deviserconcrete.h"

DeviserConcrete::DeviserConcrete()
  : DeviserBase()
  , mName()
  , mElement()
  , mMinNumChildren(0)
  , mMaxNumChildren(0)
{

}

DeviserConcrete::DeviserConcrete(const DeviserConcrete& other)
  : DeviserBase(other)
  , mName(other.mName)
  , mElement(other.mElement)
  , mMinNumChildren(other.mMinNumChildren)
  , mMaxNumChildren(other.mMaxNumChildren)
{

}

void
DeviserConcrete::initializeFrom(const QDomElement& element)
{
  DeviserBase::initializeFrom(element);

  mName = element.attribute("name");
  mElement = element.attribute("element");
  mMinNumChildren = element.attribute("minNumChildren").toInt();
  mMaxNumChildren = element.attribute("maxNumChildren").toInt();
}

const QString &
DeviserConcrete::getName() const
{
  return mName;
}

void
DeviserConcrete::setName(const QString &name)
{
  mName = name;
  emit nameChanged();
  setModified();
}

const QString &
DeviserConcrete::getElement() const
{
  return mElement;
}

void
DeviserConcrete::setElement(const QString &element)
{
  mElement = element;
  emit elementChanged();
  setModified();
}

int
DeviserConcrete::getMinNumChildren() const
{
  return mMinNumChildren;
}

void
DeviserConcrete::setMinNumChildren(int minNoChildren)
{
  mMinNumChildren = minNoChildren;
  emit minNoChildrenChanged();
  setModified();
}

int
DeviserConcrete::getMaxNumChildren() const
{
  return mMaxNumChildren;
}

void
DeviserConcrete::setMaxNumChildren(int maxNoChildren)
{
  mMaxNumChildren = maxNoChildren;
  emit maxNoChildrenChanged();
  setModified();
}

void 
DeviserConcrete::writeAttributesTo(QXmlStreamWriter& writer) const
{
  DeviserBase::writeAttributesTo(writer);

  if (!mName.isEmpty())
    writer.writeAttribute("name", mName);
  if (!mElement.isEmpty())
    writer.writeAttribute("element", mElement);
  if (mMinNumChildren != 0)
    writer.writeAttribute("minNumChildren", QString::number(mMinNumChildren));
  if (mMaxNumChildren != 0)
    writer.writeAttribute("maxNumChildren", QString::number(mMaxNumChildren));

}

void 
DeviserConcrete::writeTo(QXmlStreamWriter& writer) const
{
  writeElementsWithNameTo(writer, "concrete");
}

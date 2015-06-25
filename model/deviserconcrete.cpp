
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

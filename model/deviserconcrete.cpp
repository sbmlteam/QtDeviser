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

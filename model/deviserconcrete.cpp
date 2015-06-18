#include "deviserconcrete.h"

DeviserConcrete::DeviserConcrete()
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

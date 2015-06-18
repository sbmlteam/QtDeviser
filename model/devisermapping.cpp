#include "devisermapping.h"

DeviserMapping::DeviserMapping()
{

}

void
DeviserMapping::initializeFrom(const QDomElement& element)
{
    DeviserBase::initializeFrom(element);

    mName = element.attribute("name");
    mPackage = element.attribute("package");
}

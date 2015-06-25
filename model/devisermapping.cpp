#include "devisermapping.h"

DeviserMapping::DeviserMapping()
 : DeviserBase()
 , mName()
 , mPackage()
{

}

DeviserMapping::DeviserMapping(const DeviserMapping& other)
 : DeviserBase(other)
 , mName(other.mName)
 , mPackage(other.mPackage)
{

}

void
DeviserMapping::initializeFrom(const QDomElement& element)
{
    DeviserBase::initializeFrom(element);

    mName = element.attribute("name");
    mPackage = element.attribute("package");
}

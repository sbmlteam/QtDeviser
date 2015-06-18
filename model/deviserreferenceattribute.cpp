#include "deviserreferenceattribute.h"

DeviserReferenceAttribute::DeviserReferenceAttribute()
{

}

void
DeviserReferenceAttribute::initializeFrom(const QDomElement& element)
{
    DeviserBase::initializeFrom(element);
    mName = element.attribute("name");
}

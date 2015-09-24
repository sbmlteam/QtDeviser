#include "deviserlistofattribute.h"

DeviserListOfAttribute::DeviserListOfAttribute()
  : DeviserAttribute()
{

}

DeviserListOfAttribute::DeviserListOfAttribute(const DeviserListOfAttribute& other)
  : DeviserAttribute(other)
{

}

DeviserListOfAttribute &
DeviserListOfAttribute::operator=(const DeviserListOfAttribute &rhs)
{
  if (&rhs == this)
    return *this;

  DeviserAttribute::operator =(rhs);

  return *this;
}

void 
DeviserListOfAttribute::initializeFrom(const QDomElement& element)
{
  DeviserAttribute::initializeFrom(element);
}

void 
DeviserListOfAttribute::writeTo(QXmlStreamWriter& writer) const
{
  writeElementsWithNameTo(writer, "listOfAttribute");
}

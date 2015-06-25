#include "deviserlistofattribute.h"

DeviserListOfAttribute::DeviserListOfAttribute()
  : DeviserAttribute()
{

}

DeviserListOfAttribute::DeviserListOfAttribute(const DeviserListOfAttribute& other)
  : DeviserAttribute(other)
{

}


void DeviserListOfAttribute::initializeFrom(const QDomElement& element)
{
    DeviserAttribute::initializeFrom(element);
}

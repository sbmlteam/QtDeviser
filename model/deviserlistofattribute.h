#ifndef DEVISERLISTOFATTRIBUTE_H
#define DEVISERLISTOFATTRIBUTE_H

#include <model/deviserattribute.h>

class DeviserListOfAttribute : public DeviserAttribute
{
public:
    DeviserListOfAttribute();
    DeviserListOfAttribute(const DeviserListOfAttribute& other) {}
    virtual void initializeFrom(const QDomElement& element) {}
};

#endif // DEVISERLISTOFATTRIBUTE_H

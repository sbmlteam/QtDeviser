#ifndef DEVISERLISTOFATTRIBUTE_H
#define DEVISERLISTOFATTRIBUTE_H

#include <model/deviserattribute.h>

class DeviserListOfAttribute : public DeviserAttribute
{
public:
    DeviserListOfAttribute();
    virtual void initializeFrom(const QDomElement& element) {}
};

#endif // DEVISERLISTOFATTRIBUTE_H

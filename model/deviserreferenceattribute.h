#ifndef DEVISERREFERENCEATTRIBUTE_H
#define DEVISERREFERENCEATTRIBUTE_H

#include <model/deviserbase.h>

class DeviserReferenceAttribute : public DeviserBase
{
public:
    DeviserReferenceAttribute();
    virtual void initializeFrom(const QDomElement& element) {}
};

#endif // DEVISERREFERENCEATTRIBUTE_H

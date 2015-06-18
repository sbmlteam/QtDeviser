#ifndef DEVISERATTRIBUTE_H
#define DEVISERATTRIBUTE_H

#include <model/deviserbase.h>

class DeviserAttribute : public DeviserBase
{
public:
    DeviserAttribute();
    virtual void initializeFrom(const QDomElement& element) {}
};

#endif // DEVISERATTRIBUTE_H

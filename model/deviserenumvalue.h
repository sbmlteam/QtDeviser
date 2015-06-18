#ifndef DEVISERENUMVALUE_H
#define DEVISERENUMVALUE_H

#include <model/deviserbase.h>

class DeviserEnumValue : public DeviserBase
{
public:
    DeviserEnumValue();
    virtual void initializeFrom(const QDomElement& element) {}
};

#endif // DEVISERENUMVALUE_H

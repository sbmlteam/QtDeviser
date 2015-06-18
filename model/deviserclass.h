#ifndef DEVISERCLASS_H
#define DEVISERCLASS_H

#include <model/deviserbase.h>

class DeviserClass : public DeviserBase
{
public:
    DeviserClass();
    virtual void initializeFrom(const QDomElement& element) {}
};

#endif // DEVISERCLASS_H

#ifndef DEVISERVERSION_H
#define DEVISERVERSION_H

#include <model/deviserbase.h>

class DeviserVersion : public DeviserBase
{
public:
    DeviserVersion();
    virtual void initializeFrom(const QDomElement& element) {}
};

#endif // DEVISERVERSION_H

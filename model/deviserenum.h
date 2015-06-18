#ifndef DEVISERENUM_H
#define DEVISERENUM_H

#include <model/deviserbase.h>

class DeviserEnum : public DeviserBase
{
public:
    DeviserEnum();
    virtual void initializeFrom(const QDomElement& element) {}
};

#endif // DEVISERENUM_H

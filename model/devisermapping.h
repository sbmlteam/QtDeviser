#ifndef DEVISERMAPPING_H
#define DEVISERMAPPING_H

#include <model/deviserbase.h>

class DeviserMapping : public DeviserBase
{
public:
    DeviserMapping();
    virtual void initializeFrom(const QDomElement& element) {}
};

#endif // DEVISERMAPPING_H

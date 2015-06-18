#ifndef DEVISERMAPPING_H
#define DEVISERMAPPING_H

#include <model/deviserbase.h>

class DeviserMapping : public DeviserBase
{
public:
    DeviserMapping();
    DeviserMapping(const DeviserMapping& other) {}
    virtual void initializeFrom(const QDomElement& element) {}
};

#endif // DEVISERMAPPING_H

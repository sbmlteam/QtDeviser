#ifndef DEVISERCONCRETE_H
#define DEVISERCONCRETE_H

#include <model/deviserbase.h>

class DeviserConcrete : public DeviserBase
{
public:
    DeviserConcrete();
    DeviserConcrete(const DeviserConcrete& other) {}
    virtual void initializeFrom(const QDomElement& element) {}
};

#endif // DEVISERCONCRETE_H

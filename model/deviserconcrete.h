#ifndef DEVISERCONCRETE_H
#define DEVISERCONCRETE_H

#include <model/deviserbase.h>

class DeviserConcrete : public DeviserBase
{
public:
    DeviserConcrete();
    virtual void initializeFrom(const QDomElement& element) {}
};

#endif // DEVISERCONCRETE_H

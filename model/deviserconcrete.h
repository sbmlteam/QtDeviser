#ifndef DEVISERCONCRETE_H
#define DEVISERCONCRETE_H

#include <model/deviserbase.h>

class DeviserConcrete : public DeviserBase
{
    Q_OBJECT

public:
    DeviserConcrete();
    DeviserConcrete(const DeviserConcrete& other) {}
    virtual void initializeFrom(const QDomElement& element);

    const QString& getName() const { return mName;}
    const QString& getElement() const { return mElement;}
    int getMinNumChildren() const { return mMinNumChildren;}
    int getMaxNumChildren() const { return mMaxNumChildren;}

protected:
    QString mName;
    QString mElement;
    int mMinNumChildren;
    int mMaxNumChildren;

};

#endif // DEVISERCONCRETE_H

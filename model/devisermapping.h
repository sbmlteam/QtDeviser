#ifndef DEVISERMAPPING_H
#define DEVISERMAPPING_H

#include <model/deviserbase.h>

class DeviserMapping : public DeviserBase
{
    Q_OBJECT

public:
    DeviserMapping();
    DeviserMapping(const DeviserMapping& other) {}
    virtual void initializeFrom(const QDomElement& element);

    const QString& getName() const { return mName; }
    const QString& getPackage() const { return mPackage; }

protected:
    QString mName;
    QString mPackage;
};

#endif // DEVISERMAPPING_H

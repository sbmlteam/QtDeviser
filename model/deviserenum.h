#ifndef DEVISERENUM_H
#define DEVISERENUM_H

#include <model/deviserbase.h>

class DeviserEnumValue;

class DeviserEnum : public DeviserBase
{
    Q_OBJECT

public:
    DeviserEnum();
    DeviserEnum(const DeviserEnum& other) {}
    virtual void initializeFrom(const QDomElement& element);

    const QString& getName() const { return mName; }
    const QList<DeviserEnumValue*>& getValues() { return mValues; }

protected:
    QString mName;
    QList<DeviserEnumValue*> mValues;
};

#endif // DEVISERENUM_H

#ifndef DEVISERENUMVALUE_H
#define DEVISERENUMVALUE_H

#include <model/deviserbase.h>

class DeviserEnumValue : public DeviserBase
{
    Q_OBJECT

public:
    DeviserEnumValue();
    DeviserEnumValue(const DeviserEnumValue& other);
    virtual void initializeFrom(const QDomElement& element);

    const QString& getName() const{ return mName;}
    void setName(const QString& name) { mName = name; emit nameChanged(); }
    const QString& getValue() const { return mValue;}
    void setValue(const QString& value) { mValue = value; emit valueChanged(); }

signals:
    void nameChanged();
    void valueChanged();

protected:
    QString mName;
    QString mValue;
};

#endif // DEVISERENUMVALUE_H

#ifndef DEVISERENUM_H
#define DEVISERENUM_H

#include <model/deviserbase.h>

class DeviserEnumValue;

class DeviserEnum : public DeviserBase
{
    Q_OBJECT

public:
    DeviserEnum();
    DeviserEnum(const DeviserEnum& other);
    virtual void initializeFrom(const QDomElement& element);

    const QString& getName() const { return mName; }
    void setName(const QString& name) { QString oldName(mName); mName = name; emit nameChanged(oldName, name); }

    const QList<DeviserEnumValue*>& getValues() const { return mValues; }
    QList<DeviserEnumValue*>& getValues() { return mValues; }

    virtual void writeAttributesTo(QXmlStreamWriter& writer) const;
    virtual void writeElementsTo(QXmlStreamWriter& writer) const;
    virtual void writeTo(QXmlStreamWriter& writer) const;

signals:
    void nameChanged(const QString& oldName, const QString& newName);

protected:
    QString mName;
    QList<DeviserEnumValue*> mValues;
};

#endif // DEVISERENUM_H

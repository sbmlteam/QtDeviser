#ifndef DEVISERREFERENCEATTRIBUTE_H
#define DEVISERREFERENCEATTRIBUTE_H

#include <model/deviserbase.h>

class DeviserReferenceAttribute : public DeviserBase
{
    Q_OBJECT

public:
    DeviserReferenceAttribute();
    DeviserReferenceAttribute(const DeviserReferenceAttribute& other);
    virtual void initializeFrom(const QDomElement& element);

    const QString& getName() const { return mName; }
    void setName(const QString& name) { mName = name; emit nameChanged(); }

    virtual void writeAttributesTo(QXmlStreamWriter& writer) const;
    virtual void writeTo(QXmlStreamWriter& writer) const;

signals:
    void nameChanged();

protected:
    QString mName;
};

#endif // DEVISERREFERENCEATTRIBUTE_H

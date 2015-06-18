#ifndef DEVISERATTRIBUTE_H
#define DEVISERATTRIBUTE_H

#include <model/deviserreferenceattribute.h>

class DeviserAttribute : public DeviserReferenceAttribute
{
    Q_OBJECT

public:
    DeviserAttribute();
    DeviserAttribute(const DeviserAttribute& other) {}
    virtual void initializeFrom(const QDomElement& element);

    const QString& getXMLName() const { return mXMLName;}
    const QString& getType() const { return mType;}
    const QString& getElement() const { return mElement;}
    bool getRequired() const { return mRequired;}
    bool getAbstract() const { return mAbstract;}

protected:
    QString mXMLName;
    QString mType;
    QString mElement;
    bool mRequired;
    bool mAbstract;

};

#endif // DEVISERATTRIBUTE_H

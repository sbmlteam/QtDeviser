#ifndef DEVISERATTRIBUTE_H
#define DEVISERATTRIBUTE_H

#include <model/deviserreferenceattribute.h>

class DeviserAttribute : public DeviserReferenceAttribute
{
    Q_OBJECT

public:
    DeviserAttribute();
    DeviserAttribute(const DeviserAttribute& other);
    virtual void initializeFrom(const QDomElement& element);

    const QString& getXMLName() const { return mXMLName;}
    void setXMLName(const QString& name) { mXMLName = name; emit xmlNameChanged(); }
    const QString& getType() const { return mType;}
    void setType(const QString& type) { mType = type; emit typeChanged(); }
    const QString& getElement() const { return mElement;}
    void setElement(const QString& element) { mElement = element; emit elementChanged(); }
    bool getRequired() const { return mRequired;}
    void setRequired(bool isRequired) { mRequired = isRequired; emit requiredChanged(); }
    bool getAbstract() const { return mAbstract;}
    void setAbstract(bool isAbstract) { mAbstract = isAbstract; emit abstractChanged(); }

signals:
    void xmlNameChanged();
    void typeChanged();
    void elementChanged();
    void requiredChanged();
    void abstractChanged();

protected:
    QString mXMLName;
    QString mType;
    QString mElement;
    bool mRequired;
    bool mAbstract;

};

#endif // DEVISERATTRIBUTE_H

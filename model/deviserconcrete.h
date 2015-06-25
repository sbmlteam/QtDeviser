#ifndef DEVISERCONCRETE_H
#define DEVISERCONCRETE_H

#include <model/deviserbase.h>

class DeviserConcrete : public DeviserBase
{
    Q_OBJECT

public:
    DeviserConcrete();
    DeviserConcrete(const DeviserConcrete& other);
    virtual void initializeFrom(const QDomElement& element);

    const QString& getName() const { return mName;}
    void setName(const QString& name) { mName = name; emit nameChanged();}
    const QString& getElement() const { return mElement;}
    void setElement(const QString& element) { mElement = element; emit elementChanged(); }
    int getMinNumChildren() const { return mMinNumChildren;}
    void setMinNumChildren(int minNoChildren) { mMinNumChildren = minNoChildren; emit minNoChildrenChanged();}
    int getMaxNumChildren() const { return mMaxNumChildren;}
    void setMaxNumChildren(int maxNoChildren) { mMaxNumChildren = maxNoChildren; emit maxNoChildrenChanged();}

    virtual void writeAttributesTo(QXmlStreamWriter& writer) const;
    virtual void writeTo(QXmlStreamWriter& writer) const;

signals:

    void nameChanged();
    void elementChanged();
    void minNoChildrenChanged();
    void maxNoChildrenChanged();

protected:
    QString mName;
    QString mElement;
    int mMinNumChildren;
    int mMaxNumChildren;

};

#endif // DEVISERCONCRETE_H

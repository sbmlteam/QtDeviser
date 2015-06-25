#ifndef DEVISERCLASS_H
#define DEVISERCLASS_H

#include <model/deviserbase.h>

class DeviserAttribute;
class DeviserListOfAttribute;
class DeviserConcrete;

class DeviserClass : public DeviserBase
{
    Q_OBJECT

public:
    DeviserClass();
    DeviserClass(const DeviserClass& other);
    virtual void initializeFrom(const QDomElement& element);

    const QString& getName() const { return mName; }
    void setName(const QString& name) { QString oldName = mName; mName = name; emit nameChanged(oldName, name); }
    const QString& getBaseClass() const { return mBaseClass; }
    void setBaseClass(const QString& baseClass) { mBaseClass = baseClass; emit baseClassChanged(); }
    const QString& getTypeCode() const { return mTypeCode; }
    void setTypeCode(const QString& typeCode) { mTypeCode = typeCode; emit typeCodeChanged(); }

    bool hasListOf() const { return mHasListOf; }
    void setHasListOf(bool hasListOf) { mHasListOf = hasListOf; emit hasListOfChanged(); }
    bool hasMath() const { return mHasMath; }
    void setHasMath(bool hasMath) { mHasMath = hasMath; emit hasMathChanged(); }
    bool hasChildren() const { return mHasChildren; }
    void setHasChildren(bool hasChildren) { mHasChildren = hasChildren; emit hasChildrenChanged(); }
    bool isBaseClass() const { return mIsBaseClass; }
    void setIsBaseClass(bool isBaseClass) { mIsBaseClass = isBaseClass; emit isBaseClassChanged(); }

    const QString& getElementName() const { return mElementName; }
    void setElementName(const QString& elementName) { mElementName = elementName; emit elementNameChanged(); }
    const QString& getListOfName() const { return mListOfName; }
    void setListOfName(const QString& listOfName) { mListOfName = listOfName; emit listOfNameChanged(); }
    const QString& getListOfClassName() const { return mListOfClassName; }
    void setListOfClassName(const QString& listOfClassName) { mListOfClassName = listOfClassName; emit listOfClassNameChanged(); }

    bool getChildrenOverwriteElementName() const { return mChildrenOverwriteElementName; }

    const QString& getAdditionalDeclarations() const { return mAdditionalDeclarations; }
    void setAdditionalDeclarations(const QString& additionalDeclarations) { mAdditionalDeclarations = additionalDeclarations; emit additionalDeclarationsChanged();}
    const QString& getAdditionalDefinitions() const { return mAdditionalDefinitions; }
    void setAdditionalDefinitions(const QString& additionalDefinitions) { mAdditionalDefinitions = additionalDefinitions; emit additionalDefinitionsChanged();}

    int getMinNumberChildren() const { return mMinNumberChildren; }
    void setMinNumberChildren(int minNoChildren) { mMinNumberChildren = minNoChildren; emit minNoChildrenChanged();}
    int getMaxNumberChildren() const { return mMaxNumberChildren; }
    void setMaxNumberChildren(int maxNoChildren) { mMaxNumberChildren = maxNoChildren; emit maxNoChildrenChanged();}

    const QList<DeviserAttribute*>& getAttributes() const { return mAttributes;}
    const QList<DeviserListOfAttribute*>& getListOfAttributes() const { return mListOfAttributes; }
    const QList<DeviserConcrete*>& getConcretes() const { return mConcretes; }
    QList<DeviserAttribute*>& getAttributes()  { return mAttributes;}
    QList<DeviserListOfAttribute*>& getListOfAttributes()  { return mListOfAttributes; }
    QList<DeviserConcrete*>& getConcretes()  { return mConcretes; }

    DeviserAttribute* createAttribute();
    DeviserListOfAttribute* createListOfAttribute();
    DeviserConcrete* createConcrete();

    virtual void writeAttributesTo(QXmlStreamWriter& writer) const;
    virtual void writeElementsTo(QXmlStreamWriter& writer) const;
    virtual void writeTo(QXmlStreamWriter& writer) const;

signals:
    void nameChanged(const QString& oldName, const QString& newName);
    void baseClassChanged();
    void typeCodeChanged();
    void hasListOfChanged();
    void hasMathChanged();
    void hasChildrenChanged();
    void isBaseClassChanged();
    void elementNameChanged();
    void listOfNameChanged();
    void listOfClassNameChanged();
    void additionalDeclarationsChanged();
    void additionalDefinitionsChanged();
    void minNoChildrenChanged();
    void maxNoChildrenChanged();



protected:
    QString mName;
    QString mBaseClass;
    QString mTypeCode;

    bool mHasListOf;
    bool mHasMath;
    bool mHasChildren;
    bool mIsBaseClass;

    QString mElementName;
    QString mListOfName;
    QString mListOfClassName;

    bool mChildrenOverwriteElementName;

    QString mAdditionalDeclarations;
    QString mAdditionalDefinitions;

    int mMinNumberChildren;
    int mMaxNumberChildren;

    QList<DeviserAttribute*> mAttributes;
    QList<DeviserListOfAttribute*> mListOfAttributes;
    QList<DeviserConcrete*> mConcretes;
};

#endif // DEVISERCLASS_H

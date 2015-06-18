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
    DeviserClass(const DeviserClass& other) {}
    virtual void initializeFrom(const QDomElement& element);

    const QString& getName() const { return mName; }
    const QString& getBaseClass() const { return mBaseClass; }
    const QString& getTypeCode() const { return mTypeCode; }

    bool getHasListOf() const { return mHasListOf; }
    bool getHasMath() const { return mHasMath; }
    bool getHasChildren() const { return mHasChildren; }
    bool getIsBaseClass() const { return mIsBaseClass; }

    const QString& getElementName() const { return mElementName; }
    const QString& getListOfName() const { return mListOfName; }
    const QString& getListOfClassName() const { return mListOfClassName; }

    bool getChildrenOverwriteElementName() const { return mChildrenOverwriteElementName; }

    const QString& getAdditionalDeclarations() const { return mAdditionalDeclarations; }
    const QString& getAdditionalDefinitions() const { return mAdditionalDefinitions; }

    int getMinNumberChildren() const { return mMinNumberChildren; }
    int getMaxNumberChildren() const { return mMaxNumberChildren; }

    const QList<DeviserAttribute*>& getAttributes() const { return mAttributes;}
    const QList<DeviserListOfAttribute*>& getListOfAttributes() const { return mListOfAttributes; }
    const QList<DeviserConcrete*>& getConcretes() const { return mConcretes; }

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

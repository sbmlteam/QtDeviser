#include "deviserclass.h"

#include "deviserenum.h"
#include "deviserattribute.h"
#include "deviserlistofattribute.h"
#include "deviserconcrete.h"

DeviserClass::DeviserClass()
  : DeviserBase()
  , mName()
  , mBaseClass()
  , mTypeCode()
  , mHasListOf(false)
  , mHasMath(false)
  , mHasChildren(false)
  , mIsBaseClass(false)
  , mElementName()
  , mListOfName()
  , mListOfClassName()
  , mChildrenOverwriteElementName(false)
  , mAdditionalDeclarations()
  , mAdditionalDefinitions()
  , mMinNumberChildren(0)
  , mMaxNumberChildren(0)
  , mAttributes()
  , mListOfAttributes()
  , mConcretes()
{

}

DeviserClass::DeviserClass(const DeviserClass& other)
  : DeviserBase(other)
  , mName(other.mName)
  , mBaseClass(other.mBaseClass)
  , mTypeCode(other.mTypeCode)
  , mHasListOf(other.mHasListOf)
  , mHasMath(other.mHasMath)
  , mHasChildren(other.mHasChildren)
  , mIsBaseClass(other.mIsBaseClass)
  , mElementName(other.mElementName)
  , mListOfName(other.mListOfName)
  , mListOfClassName(other.mListOfClassName)
  , mChildrenOverwriteElementName(other.mChildrenOverwriteElementName)
  , mAdditionalDeclarations(other.mAdditionalDeclarations)
  , mAdditionalDefinitions(other.mAdditionalDefinitions)
  , mMinNumberChildren(other.mMinNumberChildren)
  , mMaxNumberChildren(other.mMaxNumberChildren)
  , mAttributes()
  , mListOfAttributes()
  , mConcretes()
{
  cloneElements(other.mAttributes, mAttributes);
  cloneElements(other.mListOfAttributes, mListOfAttributes);
  cloneElements(other.mConcretes, mConcretes);
}



void DeviserClass::initializeFrom(const QDomElement& element)
{
    DeviserBase::initializeFrom(element);

    mName = element.attribute("name");
    mBaseClass = element.attribute("baseClass");

    mTypeCode = element.attribute("typeCode");
    mHasListOf = element.attribute("hasListOf").toLower() == "true";
    mHasChildren = element.attribute("hasChildren").toLower() == "true";
    mHasMath = element.attribute("hasMath").toLower() == "true";
    mIsBaseClass = element.attribute("abstract").toLower() == "true";
    mMinNumberChildren = element.attribute("minNumListOfChildren").toInt();
    mMaxNumberChildren = element.attribute("maxNumListOfChildren").toInt();
    mChildrenOverwriteElementName = element.attribute("childrenOverwriteElementName").toLower()== "true";
    mElementName = element.attribute("elementName");
    mListOfName = element.attribute("listOfName");
    mListOfClassName = element.attribute("listOfClassName");

    mAdditionalDeclarations = element.attribute("additionalDecls");
    mAdditionalDefinitions = element.attribute("additionalDefs");

    initializeListFrom(mAttributes, element, "attribute");
    initializeListFrom(mListOfAttributes, element, "listOfAttribute");
    initializeListFrom(mConcretes, element, "concrete");
}

DeviserAttribute*
DeviserClass::createAttribute()
{
  DeviserAttribute *result = new DeviserAttribute();
  result->setName(QString("attribute_%1").arg(mAttributes.size()));
  mAttributes.append(result);
  setParent(mPackage);
  return result;
}

DeviserListOfAttribute*
DeviserClass::createListOfAttribute()
{
    DeviserListOfAttribute *result = new DeviserListOfAttribute();
    result->setName(QString("loattribute_%1").arg(mListOfAttributes.size()));
    mListOfAttributes.append(result);
    setParent(mPackage);
    return result;
}

DeviserConcrete*
DeviserClass::createConcrete()
{
    DeviserConcrete *result = new DeviserConcrete();
    result->setName(QString("concrete_%1").arg(mConcretes.size()));
    mConcretes.append(result);
    setParent(mPackage);
    return result;
}


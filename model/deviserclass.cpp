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


void 
DeviserClass::writeAttributesTo(QXmlStreamWriter& writer) const
{
  DeviserBase::writeAttributesTo(writer);

  if (!mName.isEmpty())
    writer.writeAttribute("name", mName);
  if (!mTypeCode.isEmpty())
    writer.writeAttribute("typeCode", mTypeCode);

  writer.writeAttribute("hasListOf", mHasListOf ? "true" : "false");
  writer.writeAttribute("hasChildren", mHasChildren ? "true" : "false");
  writer.writeAttribute("hasMath", mHasMath ? "true" : "false");
  writer.writeAttribute("childrenOverwriteElementName", mChildrenOverwriteElementName ? "true" : "false");

  if (mMinNumberChildren != 0)
    writer.writeAttribute("minNumListOfChildren", QString::number(mMinNumberChildren));
  if (mMaxNumberChildren!= 0)
    writer.writeAttribute("maxNumListOfChildren", QString::number(mMaxNumberChildren));

  if (!mBaseClass.isEmpty())
    writer.writeAttribute("baseClass", mBaseClass);

  writer.writeAttribute("abstract", mIsBaseClass ? "true" : "false");

  if (!mElementName.isEmpty())
    writer.writeAttribute("elementName", mElementName);
  if (!mListOfName.isEmpty())
    writer.writeAttribute("listOfName", mListOfName);
  if (!mListOfClassName.isEmpty())
    writer.writeAttribute("listOfClassName", mListOfClassName);
  if (!mAdditionalDeclarations.isEmpty())
    writer.writeAttribute("additionalDecls", mAdditionalDeclarations);
  if (!mAdditionalDefinitions.isEmpty())
    writer.writeAttribute("additionalDefs", mAdditionalDefinitions);
  
}

void 
DeviserClass::writeElementsTo(QXmlStreamWriter& writer) const
{
  DeviserBase::writeElementsTo(writer);
  
  writeListWithName(mAttributes, writer, "attributes");
  writeListWithName(mListOfAttributes, writer, "listOfAttributes");
  writeListWithName(mConcretes, writer, "concretes");
  
}

void 
DeviserClass::writeTo(QXmlStreamWriter& writer) const
{
  writeElementsWithNameTo(writer, "element");
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


#include "deviserclass.h"

#include "deviserenum.h"
#include "deviserattribute.h"
#include "deviserlistofattribute.h"
#include "deviserconcrete.h"

DeviserClass::DeviserClass()
{

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

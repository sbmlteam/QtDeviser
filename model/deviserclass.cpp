#include "deviserclass.h"

#include "deviserenum.h"
#include "deviserattribute.h"
#include "deviserlistofattribute.h"
#include "deviserconcrete.h"

#include "util.h"

#include <QByteArray>
#include <QTextStream>

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

const QString &
DeviserClass::getName() const
{
  return mName;
}

void
DeviserClass::setName(const QString &name)
{
  if (name == mName) return;

  QString oldName = mName;
  mName = name;

  if (!name.isEmpty())
  emit nameChanged(oldName, name, mVersion);
}

const QString &
DeviserClass::getBaseClass() const
{
  return mBaseClass;
}

void
DeviserClass::setBaseClass(const QString &baseClass)
{
  mBaseClass = baseClass;
  emit baseClassChanged();
}

const QString &
DeviserClass::getTypeCode() const
{
  return mTypeCode;
}

void
DeviserClass::setTypeCode(const QString &typeCode)
{
  mTypeCode = typeCode;
  emit typeCodeChanged();
}

bool
DeviserClass::hasListOf() const
{
  return mHasListOf;
}

void
DeviserClass::setHasListOf(bool hasListOf)
{
  mHasListOf = hasListOf;
  emit hasListOfChanged();
}

bool
DeviserClass::hasMath() const
{
  return mHasMath;
}

void
DeviserClass::setHasMath(bool hasMath)
{
  mHasMath = hasMath;
  emit hasMathChanged();
}

bool
DeviserClass::hasChildren() const
{
  return mHasChildren;
}

void
DeviserClass::setHasChildren(bool hasChildren)
{
  mHasChildren = hasChildren;
  emit hasChildrenChanged();
}

bool
DeviserClass::isBaseClass() const
{
  return mIsBaseClass;
}

void
DeviserClass::setIsBaseClass(bool isBaseClass)
{
  mIsBaseClass = isBaseClass;
  emit isBaseClassChanged();
}

const QString &
DeviserClass::getElementName() const
{
  return mElementName;
}

void
DeviserClass::setElementName(const QString &elementName)
{
  mElementName = elementName;
  emit elementNameChanged();
}

const QString &
DeviserClass::getListOfName() const
{
  return mListOfName;
}

QString
DeviserClass::getActualListOfName() const
{
  if (!mListOfClassName.isEmpty())
    return mListOfClassName;
  if (!mListOfName.isEmpty())
    return mListOfName;
  return "ListOf" + Util::guessPlural(mName);
}

void
DeviserClass::setListOfName(const QString &listOfName)
{
  mListOfName = listOfName;
  emit listOfNameChanged();
}

const QString &
DeviserClass::getListOfClassName() const
{
  return mListOfClassName;
}

void
DeviserClass::setListOfClassName(const QString &listOfClassName)
{
  mListOfClassName = listOfClassName;
  emit listOfClassNameChanged();
}

bool
DeviserClass::getChildrenOverwriteElementName() const
{
  return mChildrenOverwriteElementName;
}

const QString &
DeviserClass::getAdditionalDeclarations() const
{
  return mAdditionalDeclarations;
}

void
DeviserClass::setAdditionalDeclarations(const QString &additionalDeclarations)
{
  mAdditionalDeclarations = additionalDeclarations;
  emit additionalDeclarationsChanged();
}

const QString &
DeviserClass::getAdditionalDefinitions() const
{
  return mAdditionalDefinitions;
}

void
DeviserClass::setAdditionalDefinitions(const QString &additionalDefinitions)
{
  mAdditionalDefinitions = additionalDefinitions;
  emit additionalDefinitionsChanged();
}

int
DeviserClass::getMinNumberChildren() const
{
  return mMinNumberChildren;
}

void
DeviserClass::setMinNumberChildren(int minNoChildren)
{
  mMinNumberChildren = minNoChildren;
  emit minNoChildrenChanged();
}

int
DeviserClass::getMaxNumberChildren() const
{
  return mMaxNumberChildren;
}

void
DeviserClass::setMaxNumberChildren(int maxNoChildren)
{
  mMaxNumberChildren = maxNoChildren;
  emit maxNoChildrenChanged();
}

const QList<DeviserAttribute *> &
DeviserClass::getAttributes() const
{
  return mAttributes;
}

const QList<DeviserListOfAttribute *> &
DeviserClass::getListOfAttributes() const
{
  return mListOfAttributes;
}

const QList<DeviserConcrete *> &
DeviserClass::getConcretes() const
{
  return mConcretes;
}

QList<DeviserAttribute *> &
DeviserClass::getAttributes()
{
  return mAttributes;
}

QList<DeviserListOfAttribute *> &
DeviserClass::getListOfAttributes()
{
  return mListOfAttributes;
}

QList<DeviserConcrete *> &
DeviserClass::getConcretes()
{
  return mConcretes;
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

QString
DeviserClass::toYuml(bool usecolor) const
{
  QByteArray array;
  QTextStream stream(&array, QIODevice::WriteOnly);

  if (!mBaseClass.isEmpty())
  {
    stream << "[" << mBaseClass << "]<>-";
  }

  stream << "[" << mName;


  if (!mAttributes.empty())
    stream << "|";


  QList<const DeviserAttribute*> list;
  for (int i = 0; i < mAttributes.count(); ++i)
  {
    if (mAttributes[i]->isComplexType())
    {
      list.append(mAttributes[i]);
    }

    stream << mAttributes[i]->toYuml();
    if (i + 1 < mAttributes.count())
      stream << ";";
  }
  if (usecolor)
    stream << "{bg:" << Util::getClassColor() << "}";

  stream << "]" << endl;

  foreach (const DeviserAttribute* item, list)
  {
    stream << item->getYumlReferences(mName);
  }
  if (hasListOf())
  {
    QString listOf = getActualListOfName();
    stream << "[ListOf]<>-[" << listOf;
    if (!mListOfAttributes.empty())
      stream << "|";

    list.clear();
    for (int i = 0; i < mListOfAttributes.count(); ++i)
    {
      if (mListOfAttributes[i]->isComplexType())
      {
        list.append(mListOfAttributes[i]);
      }

      stream << mListOfAttributes[i]->toYuml();
      if (i + 1 < mListOfAttributes.count())
        stream << ";";

    }

    stream << "]" << endl;


    QString name = Util::lowerFirst(mName);
    if (!mElementName.isEmpty())
      name = Util::lowerFirst(mElementName);
    stream << QString("[%3]-%2  1..*>[%1]").arg( listOf, name, mName);

    foreach (const DeviserAttribute* item, list)
    {
      stream << item->getYumlReferences(mName);
    }

  }

  stream << endl;
  stream.flush();    
  return array;
}

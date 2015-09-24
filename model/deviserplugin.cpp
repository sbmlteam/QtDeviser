#include "deviserplugin.h"

#include "deviserreferenceattribute.h"
#include "deviserattribute.h"

#include "util.h"

#include <QByteArray>
#include <QTextStream>

DeviserPlugin::DeviserPlugin()
  : DeviserBase()
  , mExtensionPoint()
  , mAdditionalDeclarations()
  , mAdditionalDefinitions()
  , mTypeCode()
  , mExtPointPackage()
  , mReferences()
  , mAttributes()
{

}

DeviserPlugin::DeviserPlugin(const DeviserPlugin& other)
  : DeviserBase(other)
  , mExtensionPoint(other.mExtensionPoint)
  , mAdditionalDeclarations(other.mAdditionalDeclarations)
  , mAdditionalDefinitions(other.mAdditionalDefinitions)
  , mTypeCode(other.mTypeCode)
  , mExtPointPackage(other.mExtPointPackage)
  , mReferences()
  , mAttributes()
{
  cloneElements(other.mReferences, mReferences);
  cloneElements(other.mAttributes, mAttributes);
}

void
DeviserPlugin::initializeFrom(const QDomElement& element)
{
  DeviserBase::initializeFrom(element);

  mExtensionPoint = element.attribute("extensionPoint");
  mAdditionalDeclarations = element.attribute("additionalDecls");
  mAdditionalDefinitions = element.attribute("additionalDefs");
  mTypeCode = element.attribute("typecode");
  mExtPointPackage = element.attribute("package");

  initializeListFrom(mReferences, element, "reference");
  initializeListFrom(mAttributes, element, "attribute");
}

const QString &
DeviserPlugin::getExtensionPoint() const
{
  return mExtensionPoint;
}


void 
DeviserPlugin::removeReference(const QString& reference)
{
  int index = getIndexForReference(reference);
  if (index == -1) return;
  
  mReferences.takeAt(index)->deleteLater();

}

DeviserReferenceAttribute* 
DeviserPlugin::createReference()
{
  DeviserReferenceAttribute* attribute = new DeviserReferenceAttribute();
  attribute->setName(QString("reference_%1").arg(mReferences.count()));
  attribute->setParent(mPackage);
  mReferences.append(attribute);
  setModified();
  return attribute;
}


int 
DeviserPlugin::getIndexForReference(const QString& reference)
{
  int count = 0;
  foreach(DeviserReferenceAttribute* attribute, mReferences)
  {
    if (attribute->getName() == reference)
    {
      return count;
    }

    ++count;
  }
  return -1;
}

bool 
DeviserPlugin::containsReference(const QString& reference)
{
  return getIndexForReference(reference) != -1;
}


void 
DeviserPlugin::addReference(const QString& reference)
{
  DeviserReferenceAttribute* attribute = createReference();
  attribute->setName(reference);


}

void
DeviserPlugin::setExtensionPoint(const QString &extPoint)
{
  if (extPoint == mExtensionPoint) return;

  QString oldExtPoint(mExtensionPoint);
  mExtensionPoint = extPoint;

  if (!extPoint.isEmpty())
  emit extensionPointChanged(oldExtPoint, extPoint, mVersion);
  setModified();
}

const QString &
DeviserPlugin::getAdditionalDeclarations() const
{
  return mAdditionalDeclarations;
}

void
DeviserPlugin::setAdditionalDeclarations(const QString &additionalDeclarations)
{
  mAdditionalDeclarations = additionalDeclarations;
  emit additionalDeclarationsChanged();
  setModified();
}

const QString &
DeviserPlugin::getAdditionalDefinitions() const
{
  return mAdditionalDefinitions;
}

void
DeviserPlugin::setAdditionalDefinitions(const QString &additionalDefinitions)
{
  mAdditionalDefinitions = additionalDefinitions;
  emit additionalDefinitionsChanged();
  setModified();
}

const QString &
DeviserPlugin::getTypeCode() const
{
  return mTypeCode;
}

void
DeviserPlugin::setTypeCode(const QString &typeCode)
{
  mTypeCode = typeCode;
  emit typeCodeChanged();
  setModified();
}

const QString &
DeviserPlugin::getPackage() const
{
  return mExtPointPackage;
}

void
DeviserPlugin::setPackage(const QString &package)
{
  mExtPointPackage = package;
  emit packageChanged();
  setModified();
}

const QList<DeviserReferenceAttribute *> &
DeviserPlugin::getReferences() const
{
  return mReferences;
}

const QList<DeviserAttribute *> &
DeviserPlugin::getAttributes() const
{
  return mAttributes;
}

QList<DeviserReferenceAttribute *> &
DeviserPlugin::getReferences()
{
  return mReferences;
}

QList<DeviserAttribute *> &
DeviserPlugin::getAttributes()
{
  return mAttributes;
}


void
DeviserPlugin::writeAttributesTo(QXmlStreamWriter& writer) const
{
  DeviserBase::writeAttributesTo(writer);

  if (!mTypeCode.isEmpty())
    writer.writeAttribute("typecode", mTypeCode);
  if (!mExtPointPackage.isEmpty())
    writer.writeAttribute("package", mExtPointPackage);
  if (!mExtensionPoint.isEmpty())
    writer.writeAttribute("extensionPoint", mExtensionPoint);
  if (!mAdditionalDeclarations.isEmpty())
    writer.writeAttribute("additionalDecls", mAdditionalDeclarations);
  if (!mAdditionalDefinitions.isEmpty())
    writer.writeAttribute("additionalDefs", mAdditionalDefinitions);
}


DeviserAttribute*
DeviserPlugin::createAttribute()
{
  DeviserAttribute *result = new DeviserAttribute();
  result->setName(QString("attribute_%1").arg(mAttributes.size()));
  mAttributes.append(result);
  setParent(mPackage);
  setModified();
  return result;
}

void
DeviserPlugin::writeElementsTo(QXmlStreamWriter& writer) const
{
  DeviserBase::writeElementsTo(writer);
  
  writeListWithName(mReferences, writer, "references");
  writeListWithName(mAttributes, writer, "attributes");
}

void
DeviserPlugin::writeTo(QXmlStreamWriter& writer) const
{
  writeElementsWithNameTo(writer, "plugin");
}

QString
DeviserPlugin::toYuml(bool usecolor /*= true*/) const
{
  QByteArray array;
  QTextStream stream(&array, QIODevice::WriteOnly);
  stream.setCodec("UTF-8");

  stream << "[" << mExtensionPoint;


  if (!mAttributes.empty() || !mReferences.empty())
    stream << "|";

  QList<const DeviserAttribute*> list;

  for (int i = 0; i < mAttributes.count(); ++i)
  {
    const DeviserAttribute* item = mAttributes[i];
    if (item->isComplexType())
    {
      list.append(item);
    }

    stream << item->toYuml(usecolor);


    if (i + 1 < mAttributes.count())
    {
      stream << ";";
    }
  }
  if (usecolor)
    stream << "{bg:" << Util::getExtensionColor() << "}";

  stream << "]" << endl;


  foreach (const DeviserAttribute* item , list)
  {
    stream << item ->getYumlReferences(mExtensionPoint) << endl;
  }


  for (int i = 0; i < mReferences.count(); ++i)
  {
    const DeviserReferenceAttribute* item = mReferences[i];
    stream << "[" << mExtensionPoint <<  "]->[" << item->getName() << "]"
           << endl;
  }
  stream.flush();


  return QString::fromUtf8(array);
}

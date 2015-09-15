#include "deviserattribute.h"
#include "deviserpackage.h"
#include "deviserclass.h"
#include "deviserversion.h"
#include "util.h"

#include <QTextStream>
#include <QByteArray>

DeviserAttribute::DeviserAttribute()
  : DeviserReferenceAttribute()
  , mXMLName()
  , mType()
  , mElement()
  , mRequired(false)
  , mAbstract(false)
{

}

DeviserAttribute::DeviserAttribute(const DeviserAttribute& other)
  : DeviserReferenceAttribute(other)
  , mXMLName(other.mXMLName)
  , mType(other.mType)
  , mElement(other.mElement)
  , mRequired(other.mRequired)
  , mAbstract(other.mAbstract)
{

}

void
DeviserAttribute::initializeFrom(const QDomElement& element)
{
  DeviserReferenceAttribute::initializeFrom(element);

  mRequired = element.attribute("required").toLower() == "true";
  mType = element.attribute("type");
  mElement = element.attribute("element");
  mXMLName = element.attribute("xmlName");
  mAbstract = element.attribute("abstract").toLower() == "true";

}

const QString &
DeviserAttribute::getXMLName() const
{
  return mXMLName;
}

void
DeviserAttribute::setXMLName(const QString &name)
{
  mXMLName = name;
  emit xmlNameChanged();
}

const QString &
DeviserAttribute::getType() const
{
  return mType;
}

void
DeviserAttribute::setType(const QString &type)
{
  mType = type;
  emit typeChanged();
  setModified();
}

const QString &
DeviserAttribute::getElement() const
{
  return mElement;
}

void
DeviserAttribute::setElement(const QString &element)
{
  mElement = element;
  emit elementChanged();
  setModified();
}

bool
DeviserAttribute::getRequired() const
{
  return mRequired;
}

void
DeviserAttribute::setRequired(bool isRequired)
{
  mRequired = isRequired;
  emit requiredChanged();
  setModified();
}

bool
DeviserAttribute::getAbstract() const
{
  return mAbstract;
}

void
DeviserAttribute::setAbstract(bool isAbstract)
{
  mAbstract = isAbstract;
  emit abstractChanged();
  setModified();
}

void
DeviserAttribute::writeAttributesTo(QXmlStreamWriter& writer) const
{
  DeviserReferenceAttribute::writeAttributesTo(writer);

  writer.writeAttribute("required", mRequired ? "true" : "false");
  if (!mType.isEmpty())
    writer.writeAttribute("type", mType);
  if (!mElement.isEmpty())
    writer.writeAttribute("element", mElement);
  if (!mXMLName.isEmpty())
    writer.writeAttribute("xmlName", mXMLName);

  writer.writeAttribute("abstract", mAbstract ? "true" : "false");

}

void
DeviserAttribute::writeTo(QXmlStreamWriter& writer) const
{
  writeElementsWithNameTo(writer, "attribute");
}

bool
DeviserAttribute::isComplexType() const
{
  return mType == "element" || mType == "lo_element" ||
          mType == "enum" || mType == "inline_lo_element";
}

bool
DeviserAttribute::isListOf() const
{
  return mType == "lo_element";
}

const DeviserClass*
DeviserAttribute::getUnderLyingElement() const
{
  if (mVersion == NULL) return NULL;
  return mVersion->getElement(mElement);
}

QString
DeviserAttribute::toYuml(bool /*usecolor*/) const
{
  QByteArray array;
  QTextStream stream(&array, QIODevice::WriteOnly);
  stream.setCodec("UTF-8");

  QString name = Util::lowerFirst(mName);
  if (!mXMLName.isEmpty())
    name = Util::lowerFirst(mXMLName);
  stream << name;

  if (!mType.isEmpty())
  {
    if (!isComplexType())
    {
      stream << " : " << mType;
    }
    else
    {
      const DeviserClass* element = getUnderLyingElement();
      if (element == NULL)
        if (isListOf())
          stream << " : " << "ListOf" << Util::guessPlural(mElement);
        else
          stream << " : " << mElement;
      else
        if (isListOf())
          stream << " : " << element->getActualListOfName();
        else
          stream << " : " << element->getName();

    }
  }
  if (!mRequired)
    //stream << " use=\u201Coptional\u201D";
    stream << " use=optional";
  stream.flush();
  return QString::fromUtf8(array);
}


QString
DeviserAttribute::getYumlReferences(const QString& source) const
{
  QString lowerName = Util::lowerFirst(mName);
  if (!mXMLName.isEmpty())
    lowerName = Util::lowerFirst(mXMLName);

  if (mType == "element")
  {
    return QString("[%3]<%2%4-[%1]").arg( source, lowerName, mElement,
                         true ? "" : mRequired ? " ..1" : " ..0,1");
  }

  if (mType == "inline_lo_element")
  {
    return QString("[%1]-%2%4>[%3]").arg( source, lowerName, mElement,
                         mRequired ? " 1..* " : " *");
  }

  if (mType == "enum")
  {
    return QString("[%1]-%2>[%4%3]").arg( source, lowerName, mElement,
                                          Util::getEnumPrefix());
  }

  QString elementName = mElement;
  const DeviserClass* element = getUnderLyingElement();
  QString listOfName = QString("ListOf%1")
      .arg(Util::guessPlural(elementName));
  QString link = Util::lowerFirst(listOfName);
  if (element != NULL)
  {
    listOfName = element->getActualListOfName();
    link = Util::lowerFirst(listOfName);
    if (!element->getListOfName().isEmpty())
      link = Util::lowerFirst(element->getListOfName());
  }
  return QString("[%3]-%2%4>[%1]").arg( source, link, listOfName,
                       true ? "" : mRequired ? " ..1" : " ..0,1");
}

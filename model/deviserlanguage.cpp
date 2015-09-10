#include "deviserlanguage.h"

DeviserLanguage::DeviserLanguage()
 : DeviserBase()
 , mName()
 , mBaseClass()
 , mDocumentClass()
 , mPrefix()
 , mLibraryName()
{

}

DeviserLanguage::DeviserLanguage(const DeviserLanguage& other)
  : DeviserBase(other)
  , mName(other.mName)
  , mBaseClass(other.mBaseClass)
  , mDocumentClass(other.mDocumentClass)
  , mPrefix(other.mPrefix)
  , mLibraryName(other.mLibraryName)
{

}


void
DeviserLanguage::initializeFrom(const QDomElement& element)
{
  DeviserBase::initializeFrom(element);

  mName = element.attribute("name");
  mBaseClass = element.attribute("baseClass");
  mDocumentClass = element.attribute("documentClass");
  mPrefix = element.attribute("prefix");
  mLibraryName = element.attribute("libraryName");

}

void
DeviserLanguage::writeAttributesTo(QXmlStreamWriter& writer) const
{
  DeviserBase::writeAttributesTo(writer);

  if (!mName.isEmpty())
  writer.writeAttribute("name", mName);
  if (!mBaseClass.isEmpty())
  writer.writeAttribute("baseClass", mBaseClass);
  if (!mDocumentClass.isEmpty())
  writer.writeAttribute("documentClass", mDocumentClass);
  if (!mPrefix.isEmpty())
  writer.writeAttribute("prefix", mPrefix);
  if (!mLibraryName.isEmpty())
  writer.writeAttribute("libraryName", mLibraryName);

}

void
DeviserLanguage::writeTo(QXmlStreamWriter& writer) const
{
  writeElementsWithNameTo(writer, "language");
}

bool DeviserLanguage::isEmpty() const
{
  return mName.isEmpty() && mBaseClass.isEmpty() &&
      mDocumentClass.isEmpty();
}

QString DeviserLanguage::name() const
{
  return mName;
}

void DeviserLanguage::setName(const QString &name)
{
  mName = name;
}
QString DeviserLanguage::baseClass() const
{
  return mBaseClass;
}

void DeviserLanguage::setBaseClass(const QString &baseClass)
{
  mBaseClass = baseClass;
}
QString DeviserLanguage::documentClass() const
{
  return mDocumentClass;
}

void DeviserLanguage::setDocumentClass(const QString &documentClass)
{
  mDocumentClass = documentClass;
}
QString DeviserLanguage::prefix() const
{
  return mPrefix;
}

void DeviserLanguage::setPrefix(const QString &prefix)
{
  mPrefix = prefix;
}
QString DeviserLanguage::libraryName() const
{
  return mLibraryName;
}

void DeviserLanguage::setLibraryName(const QString &libraryName)
{
  mLibraryName = libraryName;
}







#include "deviserlanguage.h"

DeviserLanguage::DeviserLanguage()
 : DeviserBase()
 , mName()
 , mBaseClass()
 , mDocumentClass()
 , mPrefix()
 , mLibraryName()
 , mListOfClass()
{

}

DeviserLanguage::DeviserLanguage(const DeviserLanguage& other)
  : DeviserBase(other)
  , mName(other.mName)
  , mBaseClass(other.mBaseClass)
  , mDocumentClass(other.mDocumentClass)
  , mPrefix(other.mPrefix)
  , mLibraryName(other.mLibraryName)
  , mListOfClass(other.mListOfClass)
{

}

DeviserLanguage &
DeviserLanguage::operator=(const DeviserLanguage &rhs)
{
  if (&rhs == this)
    return *this;

  DeviserBase::operator =(rhs);

  mName = rhs.mName;
  mBaseClass = rhs.mBaseClass;
  mDocumentClass = rhs.mDocumentClass;
  mPrefix = rhs.mPrefix;
  mLibraryName = rhs.mLibraryName;
  mListOfClass = rhs.mListOfClass;

  return *this;
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
  mListOfClass = element.attribute("listOfClass");

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
  if (!mListOfClass.isEmpty())
    writer.writeAttribute("listOfClass", mListOfClass);

}

void
DeviserLanguage::writeTo(QXmlStreamWriter& writer) const
{
  writeElementsWithNameTo(writer, "language");
}

bool
DeviserLanguage::isEmpty() const
{
  return mName.isEmpty() &&
      mBaseClass.isEmpty() &&
      mDocumentClass.isEmpty();
}

const QString &
DeviserLanguage::name() const
{
  return mName;
}

void
DeviserLanguage::setName(const QString &name)
{
  mName = name;
}

const QString &
DeviserLanguage::baseClass() const
{
  return mBaseClass;
}

void
DeviserLanguage::setBaseClass(const QString &baseClass)
{
  mBaseClass = baseClass;
}

const QString &
DeviserLanguage::documentClass() const
{
  return mDocumentClass;
}

void
DeviserLanguage::setDocumentClass(const QString &documentClass)
{
  mDocumentClass = documentClass;
}

const QString &
DeviserLanguage::prefix() const
{
  return mPrefix;
}

void
DeviserLanguage::setPrefix(const QString &prefix)
{
  mPrefix = prefix;
}

const QString &
DeviserLanguage::libraryName() const
{
  return mLibraryName;
}

void
DeviserLanguage::setLibraryName(const QString &libraryName)
{
  mLibraryName = libraryName;
}

const QString &
DeviserLanguage::listOfClass() const
{
  return mListOfClass;
}

void
DeviserLanguage::setListOfClass(const QString &listOfClass)
{
  mListOfClass = listOfClass;
}

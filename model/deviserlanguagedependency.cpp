#include "deviserlanguagedependency.h"

DeviserLanguageDependency::DeviserLanguageDependency()
  : DeviserBase()
  , mLibraryName()
  , mPrefix()
{

}

DeviserLanguageDependency::DeviserLanguageDependency(const DeviserLanguageDependency& other)
  : DeviserBase(other)
  , mLibraryName(other.mLibraryName)
  , mPrefix(other.mPrefix)
{

}

DeviserLanguageDependency&
DeviserLanguageDependency::operator=(const DeviserLanguageDependency& rhs)
{
  if (this != &rhs)
  {
    mLibraryName = rhs.mLibraryName;
    mPrefix = rhs.mPrefix;
  }

  return *this;
}

void
DeviserLanguageDependency::initializeFrom(const QDomElement& element)
{
  DeviserBase::initializeFrom(element);

  mLibraryName = element.attribute("library_name");
  mPrefix = element.attribute("prefix");
}

void
DeviserLanguageDependency::writeAttributesTo(QXmlStreamWriter& writer) const
{
  DeviserBase::writeAttributesTo(writer);

  if (!mLibraryName.isEmpty())
    writer.writeAttribute("library_name", mLibraryName);

  if (!mPrefix.isEmpty())
    writer.writeAttribute("prefix", mPrefix);
}

void
DeviserLanguageDependency::writeTo(QXmlStreamWriter& writer) const
{
  writeElementsWithNameTo(writer, "dependency");
}

QString
DeviserLanguageDependency::libraryName() const
{
  return mLibraryName;
}

void
DeviserLanguageDependency::setLibraryName(const QString& libraryName)
{
  mLibraryName = libraryName;
}

QString
DeviserLanguageDependency::prefix() const
{
  return mPrefix;
}

void
DeviserLanguageDependency::setPrefix(const QString& prefix)
{
  mPrefix = prefix;
}

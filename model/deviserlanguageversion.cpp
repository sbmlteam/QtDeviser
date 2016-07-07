#include "deviserlanguageversion.h"

DeviserLanguageVersion::DeviserLanguageVersion()
  : DeviserBase()
  , mNamespaceUri()
  , mLevel(-1)
  , mVersion(-1)
{

}

DeviserLanguageVersion::DeviserLanguageVersion(const DeviserLanguageVersion& other)
  : DeviserBase(other)
  , mNamespaceUri(other.mNamespaceUri)
  , mLevel(other.mLevel)
  , mVersion(other.mVersion)
{

}

DeviserLanguageVersion&
DeviserLanguageVersion::operator=(const DeviserLanguageVersion& rhs)
{
  if (this != &rhs)
  {
    mNamespaceUri = rhs.mNamespaceUri;
    mLevel = rhs.mLevel;
    mVersion = rhs.mVersion;
  }

  return *this;
}

void
DeviserLanguageVersion::initializeFrom(const QDomElement& element)
{
  DeviserBase::initializeFrom(element);

  mNamespaceUri = element.attribute("namespace");
  mLevel = element.attribute("level", "-1").toInt();
  mVersion = element.attribute("version", "-1").toInt();
}

void
DeviserLanguageVersion::writeAttributesTo(QXmlStreamWriter& writer) const
{
  DeviserBase::writeAttributesTo(writer);

  if (mLevel >= 0)
    writer.writeAttribute("level", QString::number(mLevel));

  if (mVersion >= 0)
    writer.writeAttribute("version", QString::number(mVersion));

  if (!mNamespaceUri.isEmpty())
    writer.writeAttribute("namespace", mNamespaceUri);

}

void
DeviserLanguageVersion::writeTo(QXmlStreamWriter& writer) const
{
  writeElementsWithNameTo(writer, "version");
}

QString
DeviserLanguageVersion::namespaceUri() const
{
  return mNamespaceUri;
}

void
DeviserLanguageVersion::setNamespaceUri(const QString& namespaceUri)
{
  mNamespaceUri = namespaceUri;
}

int
DeviserLanguageVersion::level() const
{
  return mLevel;
}

void
DeviserLanguageVersion::setLevel(int level)
{
  mLevel = level;
}

int
DeviserLanguageVersion::version() const
{
  return mVersion;
}

void
DeviserLanguageVersion::setVersion(int version)
{
  mVersion = version;
}

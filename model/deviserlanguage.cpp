#include "deviserlanguage.h"

DeviserLanguage::DeviserLanguage()
 : DeviserBase()
 , mName()
 , mBaseClass()
 , mDocumentClass()
 , mPrefix()
 , mLibraryName()
 , mListOfClass()
 , mAnnotationElementName()
 , mTopLevelElementName()
 , mIsPackage(true)
 , mUsesASTNode(true)
 , mUsesXMLNode(true)
 , mLibraryMajorVersion(-1)
 , mLibraryMinorVersion(-1)
 , mLibraryRevision(-1)
 , mDependencies()
 , mLanguageVersions()
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
  , mAnnotationElementName(other.mAnnotationElementName)
  , mTopLevelElementName(other.mTopLevelElementName)
  , mIsPackage(other.mIsPackage)
  , mUsesASTNode(other.mUsesASTNode)
  , mUsesXMLNode(other.mUsesXMLNode)
  , mLibraryMajorVersion(other.mLibraryMajorVersion)
  , mLibraryMinorVersion(other.mLibraryMinorVersion)
  , mLibraryRevision(other.mLibraryRevision)
  , mDependencies()
  , mLanguageVersions()
{
  cloneElements(other.mDependencies, mDependencies);
  cloneElements(other.mLanguageVersions, mLanguageVersions);
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
  mAnnotationElementName = rhs.mAnnotationElementName;
  mTopLevelElementName = rhs.mTopLevelElementName;

  mIsPackage = rhs.mIsPackage;
  mUsesASTNode = rhs.mUsesASTNode;
  mUsesXMLNode = rhs.mUsesXMLNode;

  mLibraryMajorVersion = rhs.mLibraryMajorVersion;
  mLibraryMinorVersion = rhs.mLibraryMinorVersion;
  mLibraryRevision = rhs.mLibraryRevision;

  cloneElements(rhs.mDependencies, mDependencies);
  cloneElements(rhs.mLanguageVersions, mLanguageVersions);

  setParent(mPackage);

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
  mAnnotationElementName = element.attribute("annotationElementName");
  mTopLevelElementName = element.attribute("topLevelElementName");
  mIsPackage = element.attribute("isPackage", "true").toLower() == "true";
  mUsesASTNode = element.attribute("uses_ASTNode", "true").toLower() == "true";
  mUsesXMLNode = element.attribute("uses_XMLNode", "true").toLower() == "true";

  const QDomNodeList& nodes = element.elementsByTagName("library_version");
  for(int i = 0;i < nodes.count(); ++i)
  {
    const QDomElement& child = nodes.at(i).toElement();
    mLibraryMajorVersion = child.attribute("major", "-1").toInt();
    mLibraryMinorVersion = child.attribute("minor", "-1").toInt();
    mLibraryRevision = child.attribute("revision", "-1").toInt();
    break;
  }

  initializeListFrom(mLanguageVersions, element, "version");
  initializeListFrom(mDependencies, element, "dependency");

}

void DeviserLanguage::setParent(DeviserPackage* doc)
{
  DeviserBase::setParent(doc);

  setParentOn(mDependencies, doc, mVersion);
  setParentOn(mLanguageVersions, doc, mVersion);  

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
  if (!mAnnotationElementName.isEmpty())
    writer.writeAttribute("annotationElementName", mAnnotationElementName);
  if (!mTopLevelElementName.isEmpty())
    writer.writeAttribute("topLevelElementName", mAnnotationElementName);
  if (!mIsPackage)
    writer.writeAttribute("isPackage", "false");
  writer.writeAttribute("uses_ASTNode", mUsesASTNode ? "true" : "false");
  writer.writeAttribute("uses_XMLNode", mUsesXMLNode ? "true" : "false");

}

void DeviserLanguage::writeElementsTo(QXmlStreamWriter& writer) const
{
  DeviserBase::writeElementsTo(writer);

  if (mLibraryMajorVersion >= 0 || mLibraryMinorVersion >=0)
  {
    writer.writeStartElement("library_version");

    if (mLibraryMajorVersion >=0)
      writer.writeAttribute("major", QString::number(mLibraryMajorVersion));
    if (mLibraryMinorVersion >=0)
      writer.writeAttribute("minor", QString::number(mLibraryMinorVersion));
    if (mLibraryRevision >=0)
      writer.writeAttribute("revision", QString::number(mLibraryRevision));

    writer.writeEndElement();
  }

  writeListWithName(mLanguageVersions, writer, "language_versions");
  writeListWithName(mDependencies, writer, "dependencies");

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

bool
DeviserLanguage::isPackage() const
{
  return mIsPackage;
}

void
DeviserLanguage::setIsPackage(bool isPackage)
{
  mIsPackage = isPackage;
}

int
DeviserLanguage::libraryMajorVersion() const
{
  return mLibraryMajorVersion;
}

void
DeviserLanguage::setLibraryMajorVersion(int libraryMajorVersion)
{
  mLibraryMajorVersion = libraryMajorVersion;
}

int
DeviserLanguage::libraryMinorVersion() const
{
  return mLibraryMinorVersion;
}

void
DeviserLanguage::setLibraryMinorVersion(int libraryMinorVersion)
{
  mLibraryMinorVersion = libraryMinorVersion;
}

int
DeviserLanguage::libraryRevision() const
{
  return mLibraryRevision;
}

void
DeviserLanguage::setLibraryRevision(int libraryRevision)
{
  mLibraryRevision = libraryRevision;
}

const QList<DeviserLanguageDependency*>&
DeviserLanguage::getDependencies() const
{
  return mDependencies;
}

QList<DeviserLanguageDependency*>&
DeviserLanguage::getDependencies()
{
  return mDependencies;
}

const QList<DeviserLanguageVersion*>&
DeviserLanguage::getVersions() const
{
  return mLanguageVersions;
}

QList<DeviserLanguageVersion*>&
DeviserLanguage::getVersions()
{
  return mLanguageVersions;
}

DeviserLanguageDependency*
DeviserLanguage::createDependency()
{
  DeviserLanguageDependency *result = new DeviserLanguageDependency();
  result->setLibraryName(QString("library_%1").arg(mDependencies.size()));
  mDependencies.append(result);
  setParent(mPackage);
  setModified();
  return result;
}

DeviserLanguageVersion*
DeviserLanguage::createVersion()
{
  DeviserLanguageVersion *result = new DeviserLanguageVersion();
  result->setNamespaceUri(QString("ns1_%1").arg(mLanguageVersions.size()));
  mLanguageVersions.append(result);
  setParent(mPackage);
  setModified();
  return result;
}

QString DeviserLanguage::getTopLevelElementName() const
{
  return mTopLevelElementName;
}

void DeviserLanguage::setTopLevelElementName(const QString& topLevelElementName)
{
  mTopLevelElementName = topLevelElementName;
}

bool DeviserLanguage::getUsesASTNode() const
{
  return mUsesASTNode;
}

void DeviserLanguage::setUsesASTNode(bool usesASTNode)
{
  mUsesASTNode = usesASTNode;
}

bool DeviserLanguage::getUsesXMLNode() const
{
  return mUsesXMLNode;
}

void DeviserLanguage::setUsesXMLNode(bool usesXMLNode)
{
  mUsesXMLNode = usesXMLNode;
}

QString DeviserLanguage::getAnnotationElementName() const
{
  return mAnnotationElementName;
}

void DeviserLanguage::setAnnotationElementName(const QString& annotationElementName)
{
  mAnnotationElementName = annotationElementName;
}

#ifndef DEVISERLANGUAGE_H
#define DEVISERLANGUAGE_H

#include <QMap>
#include <QList>

#include <model/deviserbase.h>
#include <model/deviserlanguageversion.h>
#include <model/deviserlanguagedependency.h>

class DeviserLanguage : public DeviserBase
{
  Q_OBJECT

public:
  DeviserLanguage();
  DeviserLanguage(const DeviserLanguage& other);
  DeviserLanguage& operator= (const DeviserLanguage& rhs);

  virtual void initializeFrom(const QDomElement& element);
  virtual void setParent(DeviserPackage* doc);

  virtual void writeAttributesTo(QXmlStreamWriter& writer) const;
  virtual void writeElementsTo(QXmlStreamWriter& writer) const;
  virtual void writeTo(QXmlStreamWriter& writer) const;

  bool isEmpty() const;

  const QString &name() const;
  void setName(const QString &name);

  const QString &baseClass() const;
  void setBaseClass(const QString &baseClass);

  const QString &documentClass() const;
  void setDocumentClass(const QString &documentClass);

  const QString &prefix() const;
  void setPrefix(const QString &prefix);

  const QString &libraryName() const;
  void setLibraryName(const QString &libraryName);

  const QString &listOfClass() const;
  void setListOfClass(const QString &listOfClass);

  bool isPackage() const;
  void setIsPackage(bool isPackage);

  int libraryMajorVersion() const;
  void setLibraryMajorVersion(int libraryMajorVersion);

  int libraryMinorVersion() const;
  void setLibraryMinorVersion(int libraryMinorVersion);

  int libraryRevision() const;
  void setLibraryRevision(int libraryRevision);

  QString getAnnotationElementName() const;
  void setAnnotationElementName(const QString& annotationElementName);

  const QList<DeviserLanguageDependency*>& getDependencies() const;
  QList<DeviserLanguageDependency*>& getDependencies();

  const QList<DeviserLanguageVersion*>& getVersions() const;
  QList<DeviserLanguageVersion*>& getVersions();

  DeviserLanguageDependency* createDependency();
  DeviserLanguageVersion* createVersion();

protected:

  QString mName;
  QString mBaseClass;
  QString mDocumentClass;
  QString mPrefix;
  QString mLibraryName;
  QString mListOfClass;
  QString mAnnotationElementName;

  bool mIsPackage;

  int mLibraryMajorVersion;
  int mLibraryMinorVersion;
  int mLibraryRevision;

  QList<DeviserLanguageDependency*> mDependencies;
  QList<DeviserLanguageVersion*> mLanguageVersions;


};

#endif // DEVISERLANGUAGE_H

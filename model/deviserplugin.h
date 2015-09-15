#ifndef DEVISERPLUGIN_H
#define DEVISERPLUGIN_H

#include <model/deviserbase.h>

class DeviserReferenceAttribute;
class DeviserAttribute;

class DeviserPlugin : public DeviserBase
{
  Q_OBJECT

public:
  DeviserPlugin();
  DeviserPlugin(const DeviserPlugin& other);
  virtual void initializeFrom(const QDomElement& element);

  DeviserReferenceAttribute* createReference();
  void addReference(const QString& reference);
  void removeReference(const QString& reference);
  int getIndexForReference(const QString& reference);
  bool containsReference(const QString& reference);


  const QString& getExtensionPoint() const;
  void setExtensionPoint(const QString& extPoint);

  const QString& getAdditionalDeclarations() const;
  void setAdditionalDeclarations(const QString& additionalDeclarations);

  const QString& getAdditionalDefinitions() const;
  void setAdditionalDefinitions(const QString& additionalDefinitions);

  const QString& getTypeCode() const;
  void setTypeCode(const QString& typeCode);

  const QString& getPackage() const;
  void setPackage(const QString& package);

  const QList<DeviserReferenceAttribute*>& getReferences () const;
  QList<DeviserReferenceAttribute*>& getReferences ();

  const QList<DeviserAttribute*>& getAttributes() const;
  QList<DeviserAttribute*>& getAttributes();

  virtual void writeAttributesTo(QXmlStreamWriter& writer) const;
  virtual void writeElementsTo(QXmlStreamWriter& writer) const;
  virtual void writeTo(QXmlStreamWriter& writer) const;

  virtual QString toYuml(bool usecolor = true) const;

  DeviserAttribute* createAttribute();

signals:
  void extensionPointChanged(const QString& oldName, const QString& newName,
                             const DeviserVersion* version);
  void typeCodeChanged();
  void packageChanged();
  void additionalDeclarationsChanged();
  void additionalDefinitionsChanged();


protected:
  QString mExtensionPoint;
  QString mAdditionalDeclarations;
  QString mAdditionalDefinitions;
  QString mTypeCode;
  QString mExtPointPackage;

  QList<DeviserReferenceAttribute*> mReferences ;
  QList<DeviserAttribute*> mAttributes;

};

#endif // DEVISERPLUGIN_H

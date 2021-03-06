#ifndef DEVISERATTRIBUTE_H
#define DEVISERATTRIBUTE_H

#include <model/deviserreferenceattribute.h>

class DeviserClass;

class DeviserAttribute : public DeviserReferenceAttribute
{
  Q_OBJECT

public:
  DeviserAttribute();
  DeviserAttribute(const DeviserAttribute& other);
  DeviserAttribute& operator= (const DeviserAttribute& rhs);

  virtual void initializeFrom(const QDomElement& element);

  const QString& getXMLName() const;
  void setXMLName(const QString& name);

  const QString& getType() const;
  void setType(const QString& type);

  const QString& getElement() const;
  void setElement(const QString& element);

  bool getRequired() const;
  void setRequired(bool isRequired);

  bool getAbstract() const;
  void setAbstract(bool isAbstract);

  virtual void writeAttributesTo(QXmlStreamWriter& writer) const;
  virtual void writeTo(QXmlStreamWriter& writer) const;

  virtual QString toYuml(bool usecolor = true) const;

  bool isComplexType() const;
  bool isListOf() const;

  const DeviserClass* getUnderLyingElement() const;
  QString getYumlReferences(const QString& source) const;

signals:
  void xmlNameChanged();
  void typeChanged();
  void elementChanged();
  void requiredChanged();
  void abstractChanged();

protected:
  QString mXMLName;
  QString mType;
  QString mElement;
  bool mRequired;
  bool mAbstract;

  static QStringList mKnownTypes;

};

#endif // DEVISERATTRIBUTE_H

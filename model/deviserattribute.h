#ifndef DEVISERATTRIBUTE_H
#define DEVISERATTRIBUTE_H

#include <model/deviserreferenceattribute.h>

class DeviserAttribute : public DeviserReferenceAttribute
{
  Q_OBJECT

public:
  DeviserAttribute();
  DeviserAttribute(const DeviserAttribute& other);
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

};

#endif // DEVISERATTRIBUTE_H

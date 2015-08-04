#ifndef DEVISERENUM_H
#define DEVISERENUM_H

#include <model/deviserbase.h>

class DeviserEnumValue;
class DeviserVersion;

class DeviserEnum : public DeviserBase
{
  Q_OBJECT

public:
  DeviserEnum();
  DeviserEnum(const DeviserEnum& other);
  virtual void initializeFrom(const QDomElement& element);

  const QString& getName() const;
  void setName(const QString& name);

  const QList<DeviserEnumValue*>& getValues() const;
  QList<DeviserEnumValue*>& getValues();

  virtual void writeAttributesTo(QXmlStreamWriter& writer) const;
  virtual void writeElementsTo(QXmlStreamWriter& writer) const;
  virtual void writeTo(QXmlStreamWriter& writer) const;

  DeviserEnumValue* createValue();


signals:
  void nameChanged(const QString& oldName, const QString& newName,
                   const DeviserVersion* version);

protected:
  QString mName;
  QList<DeviserEnumValue*> mValues;
};

#endif // DEVISERENUM_H

#ifndef DEVISERENUMVALUE_H
#define DEVISERENUMVALUE_H

#include <model/deviserbase.h>

class DeviserEnumValue : public DeviserBase
{
  Q_OBJECT

public:
  DeviserEnumValue();
  DeviserEnumValue(const DeviserEnumValue& other);
  DeviserEnumValue& operator= (const DeviserEnumValue& rhs);

  virtual void initializeFrom(const QDomElement& element);

  const QString& getName() const;
  void setName(const QString& name);

  const QString& getValue() const;
  void setValue(const QString& value);

  virtual void writeAttributesTo(QXmlStreamWriter& writer) const;
  virtual void writeTo(QXmlStreamWriter& writer) const;

  virtual QString toYuml(bool usecolor = true) const;

signals:
  void nameChanged();
  void valueChanged();

protected:
  QString mName;
  QString mValue;
};

#endif // DEVISERENUMVALUE_H

#ifndef DEVISERMAPPING_H
#define DEVISERMAPPING_H

#include <model/deviserbase.h>

class DeviserMapping : public DeviserBase
{
  Q_OBJECT

public:
  DeviserMapping();
  DeviserMapping(const DeviserMapping& other);
  virtual void initializeFrom(const QDomElement& element);

  const QString& getName() const;
  void setName(const QString& name);

  const QString& getPackage() const;
  void setPackage(const QString& package);

  virtual void writeAttributesTo(QXmlStreamWriter& writer) const;
  virtual void writeTo(QXmlStreamWriter& writer) const;
  virtual QString toYuml(bool usecolor = true) const;

signals:
  void nameChanged();
  void packageChanged();

protected:
  QString mName;
  QString mPackage;
};

#endif // DEVISERMAPPING_H

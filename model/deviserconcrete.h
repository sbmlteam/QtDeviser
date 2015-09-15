#ifndef DEVISERCONCRETE_H
#define DEVISERCONCRETE_H

#include <model/deviserbase.h>

class DeviserConcrete : public DeviserBase
{
  Q_OBJECT

public:
  DeviserConcrete();
  DeviserConcrete(const DeviserConcrete& other);
  virtual void initializeFrom(const QDomElement& element);

  const QString& getName() const;
  void setName(const QString& name);

  const QString& getElement() const;
  void setElement(const QString& element);

  int getMinNumChildren() const;
  void setMinNumChildren(int minNoChildren);

  int getMaxNumChildren() const;
  void setMaxNumChildren(int maxNoChildren);

  virtual void writeAttributesTo(QXmlStreamWriter& writer) const;
  virtual void writeTo(QXmlStreamWriter& writer) const;

signals:

  void nameChanged();
  void elementChanged();
  void minNoChildrenChanged();
  void maxNoChildrenChanged();

protected:
  QString mName;
  QString mElement;
  int mMinNumChildren;
  int mMaxNumChildren;

};

#endif // DEVISERCONCRETE_H

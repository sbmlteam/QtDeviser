#ifndef DEVISERBASE_H
#define DEVISERBASE_H

#include <QObject>
#include <QList>
#include <QDomElement>
#include <QXmlStreamWriter>

class DeviserPackage;
class DeviserVersion;

class DeviserBase  : public QObject
{
  Q_OBJECT

public:
  DeviserBase();
  DeviserBase(const DeviserBase& );

  virtual void initializeFrom(const QDomElement& element);

  virtual void setParent(DeviserPackage* doc);
  virtual void setParentVersion(DeviserVersion* version);

  virtual QString toXmlString() const;
  virtual QString toYuml(bool usecolor = true) const;

  virtual void writeAttributesTo(QXmlStreamWriter& writer) const;
  virtual void writeElementsTo(QXmlStreamWriter& writer) const;
  virtual void writeElementsWithNameTo(QXmlStreamWriter& writer, const QString& name) const;
  virtual void writeTo(QXmlStreamWriter& writer) const;



  DeviserPackage* getParent();
  DeviserVersion* getParentVersion();

protected:

  void setModified();

  DeviserPackage* mPackage;
  DeviserVersion* mVersion;
  void* mUserData;

};

template<typename T> void writeListWithName(const QList<T*>& list, QXmlStreamWriter& writer, const QString& name)
{
  if (!list.empty())
  {
    writer.writeStartElement(name);
    foreach(const T* element, list)
    {
      element->writeTo(writer);
    }

    writer.writeEndElement();
  }
}

template<typename T> void setParentOn(QList<T*>& list, DeviserPackage* parent, DeviserVersion* version = NULL)
{
  if (!list.empty())
  {
    for(typename QList<T*>::iterator it = list.begin();  it != list.end(); ++it)
    {
      (*it)->setParent(parent);
      (*it)->setParentVersion(version);
    }

  }
}

template<typename T> void initializeListFrom(QList<T*>& list, const QDomElement& element, const QString& name)
{
  list.clear();
  const QDomNodeList& nodes = element.elementsByTagName(name);
  for(int i = 0;i < nodes.count(); ++i)
  {
    const QDomElement& child = nodes.at(i).toElement();
    T* newElement = new T();
    newElement->initializeFrom(child);
    list.append(newElement);
  }
}

template<typename T> void cloneElements(const QList<T*>& source, QList<T*>& destination)
{
  destination.clear();
  foreach(const T* element, source)
  {
    T* newElement = new T(*element);

    destination.append(newElement);
  }

}



#endif // DEVISERBASE_H

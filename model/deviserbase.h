#ifndef DEVISERBASE_H
#define DEVISERBASE_H

#include <QObject>
#include <QList>
#include <QDomElement>
#include <QXmlStreamWriter>

class DeviserPackage;

class DeviserBase  : public QObject
{
    Q_OBJECT

public:
    DeviserBase();
    DeviserBase(const DeviserBase& );

    virtual void initializeFrom(const QDomElement& element);

    virtual void setParent(DeviserPackage* doc);

    virtual QString toXmlString() const;
    virtual QString toYuml(bool usecolor = true) const;

    virtual void writeAttributesTo(QXmlStreamWriter& writer) const;
    virtual void writeElementsTo(QXmlStreamWriter& writer) const;
    virtual void writeElementsWithNameTo(QXmlStreamWriter& writer, const QString& name) const;
    virtual void writeTo(QXmlStreamWriter& writer) const;



protected:

    DeviserPackage* mPackage;
    void* mUserData;

};

template<typename T> void writeListWithName(const QList<T>& list, QXmlStreamWriter& writer, const QString& name)
{
    if (!list.empty())
    {
      writer.writeStartElement(name);
      foreach(const T& element, list)
      {
          element.writeTo(writer);
      }

      writer.writeEndElement();
    }
}

template<typename T> void setParentOn(QList<T>& list, DeviserPackage* parent)
{
    if (!list.empty())
    {
      for(auto& it = list.begin();  it != list.end(); ++it)
      {
          (*it).setParent(parent);
      }

    }
}

template<typename T> void initializeListFrom(QList<T>& list, const QDomElement& element, const QString& name)
{
    list.clear();
    const QDomNodeList& nodes = element.elementsByTagName(name);
    for(int i = 0;i < nodes.count(); ++i)
    {
        const QDomElement& child = nodes.at(i).toElement();
        T newElement;
        newElement.initializeFrom(child);
        list.append(newElement);
    }
}


#endif // DEVISERBASE_H

#ifndef LIST_OF_ATTRIBUTESMODEL_H
#define LIST_OF_ATTRIBUTESMODEL_H

#include <QList>
#include <QAbstractTableModel>
#include <QModelIndex>
#include <QVariant>

class QObject;
class DeviserListOfAttribute;

class LoAttributesModel : public QAbstractTableModel
{
public:
  LoAttributesModel(QObject * parent, QList<DeviserListOfAttribute*>* data);

  virtual int rowCount(const QModelIndex &) const;
  virtual int columnCount(const QModelIndex &) const;
  virtual QVariant data(const QModelIndex &index, int role) const;
  virtual bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
  virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const;
  virtual Qt::ItemFlags flags(const QModelIndex &index) const;

  void addAttribute(DeviserListOfAttribute* attr);
  DeviserListOfAttribute* getAttribute(int row);
  DeviserListOfAttribute* removeAttribute(int row);

  void beginAdding();
  void endAdding();


protected:

  QList<DeviserListOfAttribute*>* mData;

};

#endif // LIST_OF_ATTRIBUTESMODEL_H

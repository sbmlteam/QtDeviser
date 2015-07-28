#ifndef ATTRIBUTESMODEL_H
#define ATTRIBUTESMODEL_H

#include <QList>
#include <QAbstractTableModel>
#include <QModelIndex>
#include <QVariant>

class QObject;
class DeviserAttribute;

class AttributesModel : public QAbstractTableModel
{
public:
  AttributesModel(QObject * parent, const QList<DeviserAttribute*>& data);

  virtual int rowCount(const QModelIndex &) const;
  virtual int columnCount(const QModelIndex &) const;
  virtual QVariant data(const QModelIndex &index, int role) const;
  virtual bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
  virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const;
  virtual Qt::ItemFlags flags(const QModelIndex &index) const;

  void addAttribute(DeviserAttribute* attr);
  DeviserAttribute* getAttribute(int row);
  DeviserAttribute* removeAttribute(int row);


protected:

  QList<DeviserAttribute*> mData;

};

#endif // ATTRIBUTESMODEL_H

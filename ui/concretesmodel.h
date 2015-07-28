#ifndef CONCRETESMODEL_H
#define CONCRETESMODEL_H

#include <QList>
#include <QAbstractTableModel>
#include <QModelIndex>
#include <QVariant>

class QObject;
class DeviserConcrete;

class ConcretesModel : public QAbstractTableModel
{
public:
  ConcretesModel(QObject * parent, QList<DeviserConcrete*>* data);

  virtual int rowCount(const QModelIndex &) const;
  virtual int columnCount(const QModelIndex &) const;
  virtual QVariant data(const QModelIndex &index, int role) const;
  virtual bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
  virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const;
  virtual Qt::ItemFlags flags(const QModelIndex &index) const;

  void addAttribute(DeviserConcrete* attr);
  DeviserConcrete* getAttribute(int row);
  DeviserConcrete* removeAttribute(int row);

  void beginAdding();
  void endAdding();


protected:

  QList<DeviserConcrete*>* mData;

};

#endif // CONCRETESMODEL_H

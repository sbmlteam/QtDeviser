#ifndef MAPPING_MODEL_H
#define MAPPING_MODEL_H

#include <QList>
#include <QAbstractTableModel>
#include <QModelIndex>
#include <QVariant>

class QObject;
class DeviserMapping;

class MappingModel : public QAbstractTableModel
{
public:
  MappingModel(QObject * parent, QList<DeviserMapping*>* data);

  virtual int rowCount(const QModelIndex &) const;
  virtual int columnCount(const QModelIndex &) const;
  virtual QVariant data(const QModelIndex &index, int role) const;
  virtual bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
  virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const;
  virtual Qt::ItemFlags flags(const QModelIndex &index) const;

  void addAttribute(DeviserMapping* attr);
  DeviserMapping* getAttribute(int row);
  DeviserMapping* removeAttribute(int row);

  void beginAdding();
  void endAdding();


protected:

  QList<DeviserMapping*>* mData;

};

#endif // MAPPING_MODEL_H

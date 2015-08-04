#ifndef ENUM_MODEL_H
#define ENUM_MODEL_H

#include <QList>
#include <QAbstractTableModel>
#include <QModelIndex>
#include <QVariant>

class QObject;
class DeviserEnumValue;

class EnumModel : public QAbstractTableModel
{
public:
  EnumModel(QObject * parent, QList<DeviserEnumValue*>* data);

  virtual int rowCount(const QModelIndex &) const;
  virtual int columnCount(const QModelIndex &) const;
  virtual QVariant data(const QModelIndex &index, int role) const;
  virtual bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
  virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const;
  virtual Qt::ItemFlags flags(const QModelIndex &index) const;

  void addAttribute(DeviserEnumValue* attr);
  DeviserEnumValue* getAttribute(int row);
  DeviserEnumValue* removeAttribute(int row);

  void beginAdding();
  void endAdding();


protected:

  QList<DeviserEnumValue*>* mData;

};

#endif // ENUM_MODEL_H

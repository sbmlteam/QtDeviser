#ifndef LANGUAGEVERSIONMODEL_H
#define LANGUAGEVERSIONMODEL_H

#include <QList>
#include <QAbstractTableModel>
#include <QModelIndex>
#include <QVariant>

class QObject;
class DeviserLanguageVersion;

class LanguageVersionModel: public QAbstractTableModel
{
public:
  LanguageVersionModel(QObject * parent, QList<DeviserLanguageVersion*>* data);

  virtual int rowCount(const QModelIndex &) const;
  virtual int columnCount(const QModelIndex &) const;
  virtual QVariant data(const QModelIndex &index, int role) const;
  virtual bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
  virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const;
  virtual Qt::ItemFlags flags(const QModelIndex &index) const;

  void addVersion(DeviserLanguageVersion* attr);
  DeviserLanguageVersion* getVersion(int row);
  DeviserLanguageVersion* removeVersion(int row);

  void beginAdding();
  void endAdding();


protected:

  QList<DeviserLanguageVersion*>* mData;
};

#endif // LANGUAGEVERSIONMODEL_H

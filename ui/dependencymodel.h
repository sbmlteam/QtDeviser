#ifndef DEPENDENCYMODEL_H
#define DEPENDENCYMODEL_H

#include <QList>
#include <QAbstractTableModel>
#include <QModelIndex>
#include <QVariant>

class QObject;
class DeviserLanguageDependency;


class DependencyModel: public QAbstractTableModel
{
public:
  DependencyModel(QObject * parent, QList<DeviserLanguageDependency*>* data);

  virtual int rowCount(const QModelIndex &) const;
  virtual int columnCount(const QModelIndex &) const;
  virtual QVariant data(const QModelIndex &index, int role) const;
  virtual bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
  virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const;
  virtual Qt::ItemFlags flags(const QModelIndex &index) const;

  void addDependency(DeviserLanguageDependency* attr);
  DeviserLanguageDependency* getDependency(int row);
  DeviserLanguageDependency* removeDependency(int row);

  void beginAdding();
  void endAdding();


protected:

  QList<DeviserLanguageDependency*>* mData;

};

#endif // DEPENDENCYMODEL_H

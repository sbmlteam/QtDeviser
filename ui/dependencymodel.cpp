#include "dependencymodel.h"

#include <model/deviserlanguagedependency.h>

DependencyModel::DependencyModel(QObject * parent,
                                 QList<DeviserLanguageDependency*>* data)
  : QAbstractTableModel(parent)
  , mData(data)
{

}

int
DependencyModel::rowCount(const QModelIndex &) const
{
  return mData->count();
}

int
DependencyModel::columnCount(const QModelIndex &) const
{
  return 2;
}


Qt::ItemFlags
DependencyModel::flags(const QModelIndex &index) const
{
  if (!index.isValid())
    return Qt::ItemIsEnabled;
  return QAbstractTableModel::flags(index) | Qt::ItemIsEditable;
}

QVariant
DependencyModel::data(const QModelIndex &index, int role) const
{
  if (role != Qt::DisplayRole
      && role != Qt::EditRole
      && role != Qt::ToolTipRole) return QVariant();

  if (role == Qt::ToolTipRole)
  {
    switch(index.column())
    {
    case 0:
      return "The name of the library that this library depends on.";
    case 1:
      return "The prefix of the library that ought to be used.";
    default:
      return QVariant();
    }
  }

  const DeviserLanguageDependency* attr = (*mData)[index.row()];
  switch(index.column())
  {
  case 0:
    return attr->libraryName();
  case 1:
    return attr->prefix();
  default:
    return QVariant();
  }

}

bool
DependencyModel::setData(const QModelIndex &index,
                   const QVariant &value, int role /*= Qt::EditRole*/)
{
  if (role != Qt::DisplayRole && role != Qt::EditRole) return false;
  DeviserLanguageDependency* attr = (*mData)[index.row()];
  if (attr == NULL) return false;

  switch(index.column())
  {
  case 0:
    attr->setLibraryName(value.toString());
    return true;
  case 1:
    attr->setPrefix(value.toString());
    return true;
  default:
    return false;
  }

}

QVariant
DependencyModel::headerData(int section,
                      Qt::Orientation orientation,
                      int role) const
{
  if (orientation != Qt::Horizontal) return QVariant();

  if (role != Qt::DisplayRole) return QVariant();

  switch(section)
  {
  case 0:
    return "Library Name";
  case 1:
    return "Prefix";
  default:
    return QVariant();
  }

}

void DependencyModel::beginAdding()
{
  beginInsertRows(QModelIndex(),mData->count(),mData->count());
}

void DependencyModel::endAdding()
{
  endInsertRows();
}

void
DependencyModel::addDependency(DeviserLanguageDependency* attr)
{
  beginInsertRows(QModelIndex(),mData->count(),mData->count());
  mData->append(attr);
  endInsertRows();
}

DeviserLanguageDependency*
DependencyModel::getDependency(int row)
{
  if (row < 0 || row >= mData->count())
    return NULL;
  return (*mData)[row];
}

DeviserLanguageDependency*
DependencyModel::removeDependency(int row)
{
  beginRemoveRows(QModelIndex(),row,row);
  DeviserLanguageDependency* result = getDependency(row);
  mData->removeAt(row);
  endRemoveRows();
  return result;
}



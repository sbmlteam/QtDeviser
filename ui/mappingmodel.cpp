#include "mappingmodel.h"

#include <model/devisermapping.h>

MappingModel::MappingModel(
    QObject * parent,
    QList<DeviserMapping*>* data)
  : QAbstractTableModel(parent)
  , mData(data)
{

}

int
MappingModel::rowCount(const QModelIndex &) const
{
  return mData->count();
}

int
MappingModel::columnCount(const QModelIndex &) const
{
  return 2;
}


Qt::ItemFlags
MappingModel::flags(const QModelIndex &index) const
{
  if (!index.isValid())
    return Qt::ItemIsEnabled;
  Qt::ItemFlags flags = QAbstractTableModel::flags(index);
  if (index.column() == 1)
    flags |= Qt::ItemIsEditable;
  return flags;
}

QVariant
MappingModel::data(const QModelIndex &index, int role) const
{
  if (role != Qt::DisplayRole && role != Qt::EditRole) return QVariant();
  const DeviserMapping* attr = (*mData)[index.row()];
  switch(index.column())
  {
  case 0:
    return attr->getName();
  case 1:
    return attr->getPackage();
  default:
    return QVariant();
  }

}

bool
MappingModel::setData(const QModelIndex &index,
                   const QVariant &value, int role /*= Qt::EditRole*/)
{
  if (role != Qt::DisplayRole && role != Qt::EditRole) return false;
  DeviserMapping* attr = (*mData)[index.row()];
  if (attr == NULL) return false;

  switch(index.column())
  {
  case 0:
    attr->setName(value.toString());
    return true;
  case 1:
    attr->setPackage(value.toString());
    return true;
  default:
    return false;
  }

}

QVariant
MappingModel::headerData(int section,
                      Qt::Orientation orientation,
                      int role) const
{
  if (orientation != Qt::Horizontal) return QVariant();

  if (role != Qt::DisplayRole) return QVariant();

  switch(section)
  {
  case 0:
    return "Name";
  case 1:
    return "Package";
  default:
    return QVariant();
  }

}

void MappingModel::beginAdding()
{
  beginInsertRows(QModelIndex(),mData->count(),mData->count());
}

void MappingModel::endAdding()
{
  endInsertRows();
}

void
MappingModel::addAttribute(DeviserMapping* attr)
{
  beginInsertRows(QModelIndex(),mData->count(),mData->count());
  mData->append(attr);
  endInsertRows();
}

DeviserMapping*
MappingModel::getAttribute(int row)
{
  if (row < 0 || row >= mData->count())
    return NULL;
  return (*mData)[row];
}

DeviserMapping*
MappingModel::removeAttribute(int row)
{
  beginRemoveRows(QModelIndex(),row,row);
  DeviserMapping* result = getAttribute(row);
  mData->removeAt(row);
  endRemoveRows();
  return result;
}



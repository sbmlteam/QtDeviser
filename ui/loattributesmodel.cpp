#include "loattributesmodel.h"

#include <model/deviserlistofattribute.h>

LoAttributesModel::LoAttributesModel(
    QObject * parent,
    QList<DeviserListOfAttribute*>* data)
  : QAbstractTableModel(parent)
  , mData(data)
{

}

int
LoAttributesModel::rowCount(const QModelIndex &) const
{
  return mData->count();
}

int
LoAttributesModel::columnCount(const QModelIndex &) const
{
  return 6;
}


Qt::ItemFlags
LoAttributesModel::flags(const QModelIndex &index) const
{
  if (!index.isValid())
    return Qt::ItemIsEnabled;
  return QAbstractTableModel::flags(index) | Qt::ItemIsEditable;
}

QVariant
LoAttributesModel::data(const QModelIndex &index, int role) const
{
  if (role != Qt::DisplayRole && role != Qt::EditRole) return QVariant();
  const DeviserListOfAttribute* attr = (*mData)[index.row()];
  switch(index.column())
  {
  case 0:
    return attr->getName();
  case 1:
    return attr->getType();
  case 2:
    return attr->getElement();
  case 3:
    return attr->getRequired();
  case 4:
    return attr->getAbstract();
  case 5:
    return attr->getXMLName();
  default:
    return QVariant();
  }

}

bool
LoAttributesModel::setData(const QModelIndex &index,
                           const QVariant &value, int role /*= Qt::EditRole*/)
{
  if (role != Qt::DisplayRole && role != Qt::EditRole) return false;
  DeviserListOfAttribute* attr = (*mData)[index.row()];
  if (attr == NULL) return false;

  switch(index.column())
  {
  case 0:
    attr->setName(value.toString());
    return true;
  case 1:
    attr->setType(value.toString());
    return true;
  case 2:
    attr->setElement(value.toString());
    return true;
  case 3:
    attr->setRequired(value.toBool());
    return true;
  case 4:
    attr->setAbstract(value.toBool());
    return true;
  case 5:
    attr->setXMLName(value.toString());
    return true;
  default:
    return false;
  }

}

QVariant
LoAttributesModel::headerData(int section,
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
    return "Type";
  case 2:
    return "Element";
  case 3:
    return "Required";
  case 4:
    return "isBaseClass";
  case 5:
    return "XML name";
  default:
    return QVariant();
  }

}

void LoAttributesModel::beginAdding()
{
  beginInsertRows(QModelIndex(),mData->count(),mData->count());
}

void LoAttributesModel::endAdding()
{
  endInsertRows();
}

void
LoAttributesModel::addAttribute(DeviserListOfAttribute* attr)
{
  beginInsertRows(QModelIndex(),mData->count(),mData->count());
  mData->append(attr);
  endInsertRows();
}

DeviserListOfAttribute*
LoAttributesModel::getAttribute(int row)
{
  if (row < 0 || row >= mData->count())
    return NULL;
  return (*mData)[row];
}

DeviserListOfAttribute*
LoAttributesModel::removeAttribute(int row)
{
  beginRemoveRows(QModelIndex(),row,row);
  DeviserListOfAttribute* result = getAttribute(row);
  mData->removeAt(row);
  endRemoveRows();
  result->deleteLater();
  return result;
}


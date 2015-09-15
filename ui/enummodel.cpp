#include "enummodel.h"

#include <model/deviserenumvalue.h>

EnumModel::EnumModel(
    QObject * parent,
    QList<DeviserEnumValue*>* data)
  : QAbstractTableModel(parent)
  , mData(data)
{

}

int
EnumModel::rowCount(const QModelIndex &) const
{
  return mData->count();
}

int
EnumModel::columnCount(const QModelIndex &) const
{
  return 2;
}


Qt::ItemFlags
EnumModel::flags(const QModelIndex &index) const
{
  if (!index.isValid())
    return Qt::ItemIsEnabled;
  return QAbstractTableModel::flags(index) | Qt::ItemIsEditable;
}

QVariant
EnumModel::data(const QModelIndex &index, int role) const
{
  if (role != Qt::DisplayRole
      && role != Qt::EditRole
      && role != Qt::ToolTipRole) return QVariant();

  if (role == Qt::ToolTipRole)
  {
    switch(index.column())
    {
    case 0:
      return "The name that will be used for this enumeration entry. Note typically the enumeration entry names are given as CLASS_ENUM_VALUE.";
    case 1:
      return "The string value of this enumeration entry. This is the text that will appear in the XML output for this enumeration value.";
    default:
      return QVariant();
    }
  }

  const DeviserEnumValue* attr = (*mData)[index.row()];
  switch(index.column())
  {
  case 0:
    return attr->getName();
  case 1:
    return attr->getValue();
  default:
    return QVariant();
  }

}

bool
EnumModel::setData(const QModelIndex &index,
                   const QVariant &value, int role /*= Qt::EditRole*/)
{
  if (role != Qt::DisplayRole && role != Qt::EditRole) return false;
  DeviserEnumValue* attr = (*mData)[index.row()];
  if (attr == NULL) return false;

  switch(index.column())
  {
  case 0:
    attr->setName(value.toString());
    return true;
  case 1:
    attr->setValue(value.toString());
    return true;
  default:
    return false;
  }

}

QVariant
EnumModel::headerData(int section,
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
    return "Value (string)";
  default:
    return QVariant();
  }

}

void EnumModel::beginAdding()
{
  beginInsertRows(QModelIndex(),mData->count(),mData->count());
}

void EnumModel::endAdding()
{
  endInsertRows();
}

void
EnumModel::addAttribute(DeviserEnumValue* attr)
{
  beginInsertRows(QModelIndex(),mData->count(),mData->count());
  mData->append(attr);
  endInsertRows();
}

DeviserEnumValue*
EnumModel::getAttribute(int row)
{
  if (row < 0 || row >= mData->count())
    return NULL;
  return (*mData)[row];
}

DeviserEnumValue*
EnumModel::removeAttribute(int row)
{
  beginRemoveRows(QModelIndex(),row,row);
  DeviserEnumValue* result = getAttribute(row);
  mData->removeAt(row);
  endRemoveRows();
  return result;
}



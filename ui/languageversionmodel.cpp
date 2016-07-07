#include "languageversionmodel.h"

#include <model/deviserlanguageversion.h>

LanguageVersionModel::LanguageVersionModel(QObject * parent,
                                 QList<DeviserLanguageVersion*>* data)
  : QAbstractTableModel(parent)
  , mData(data)
{

}

int
LanguageVersionModel::rowCount(const QModelIndex &) const
{
  return mData->count();
}

int
LanguageVersionModel::columnCount(const QModelIndex &) const
{
  return 3;
}


Qt::ItemFlags
LanguageVersionModel::flags(const QModelIndex &index) const
{
  if (!index.isValid())
    return Qt::ItemIsEnabled;
  return QAbstractTableModel::flags(index) | Qt::ItemIsEditable;
}

QVariant
LanguageVersionModel::data(const QModelIndex &index, int role) const
{
  if (role != Qt::DisplayRole
      && role != Qt::EditRole
      && role != Qt::ToolTipRole) return QVariant();

  if (role == Qt::ToolTipRole)
  {
    switch(index.column())
    {
    case 0:
      return "The level of this language.";
    case 1:
      return "The version of this language.";
    case 2:
      return "The namespace of this language.";
    default:
      return QVariant();
    }
  }

  const DeviserLanguageVersion* attr = (*mData)[index.row()];
  switch(index.column())
  {
  case 0:
    return attr->level();
  case 1:
    return attr->version();
  case 2:
    return attr->namespaceUri();
  default:
    return QVariant();
  }

}

bool
LanguageVersionModel::setData(const QModelIndex &index,
                   const QVariant &value, int role /*= Qt::EditRole*/)
{
  if (role != Qt::DisplayRole && role != Qt::EditRole) return false;
  DeviserLanguageVersion* attr = (*mData)[index.row()];
  if (attr == NULL) return false;

  switch(index.column())
  {
  case 0:
    attr->setLevel(value.toInt());
    return true;
  case 1:
    attr->setVersion(value.toInt());
    return true;
  case 2:
    attr->setNamespaceUri(value.toString());
    return true;
  default:
    return false;
  }

}

QVariant
LanguageVersionModel::headerData(int section,
                      Qt::Orientation orientation,
                      int role) const
{
  if (orientation != Qt::Horizontal) return QVariant();

  if (role != Qt::DisplayRole) return QVariant();

  switch(section)
  {
  case 0:
    return "Level";
  case 1:
    return "Version";
  case 2:
    return "Namespace";
  default:
    return QVariant();
  }

}

void LanguageVersionModel::beginAdding()
{
  beginInsertRows(QModelIndex(),mData->count(),mData->count());
}

void LanguageVersionModel::endAdding()
{
  endInsertRows();
}

void
LanguageVersionModel::addVersion(DeviserLanguageVersion* attr)
{
  beginInsertRows(QModelIndex(),mData->count(),mData->count());
  mData->append(attr);
  endInsertRows();
}

DeviserLanguageVersion*
LanguageVersionModel::getVersion(int row)
{
  if (row < 0 || row >= mData->count())
    return NULL;
  return (*mData)[row];
}

DeviserLanguageVersion*
LanguageVersionModel::removeVersion(int row)
{
  beginRemoveRows(QModelIndex(),row,row);
  DeviserLanguageVersion* result = getVersion(row);
  mData->removeAt(row);
  endRemoveRows();
  return result;
}



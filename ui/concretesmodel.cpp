#include "concretesmodel.h"

#include <model/deviserconcrete.h>

ConcretesModel::ConcretesModel(
    QObject * parent,
    QList<DeviserConcrete*>* data)
  : QAbstractTableModel(parent)
  , mData(data)
{

}

int
ConcretesModel::rowCount(const QModelIndex &) const
{
  return mData->count();
}

int
ConcretesModel::columnCount(const QModelIndex &) const
{
  return 4;
}


Qt::ItemFlags
ConcretesModel::flags(const QModelIndex &index) const
{
  if (!index.isValid())
    return Qt::ItemIsEnabled;
  return QAbstractTableModel::flags(index) | Qt::ItemIsEditable;
}

QVariant
ConcretesModel::data(const QModelIndex &index, int role) const
{
  if (role != Qt::DisplayRole
      && role != Qt::EditRole
      && role != Qt::ToolTipRole) return QVariant();
  const DeviserConcrete* attr = (*mData)[index.row()];

  if (role == Qt::ToolTipRole)
  {
    switch(index.column())
    {
    case 0:
      return "The name of the instantiation of this class to be used by the XML output. This field is required.";
    case 1:
      return "The <b>Name</b> of the class that will be derived from this base class. Note this class should also be defined within this package. This field is required.";
    case 2:
      return "The minimum number of child elements that may be present on this element. A missing value or 0 implies there is no minimum.";
    case 3:
      return "The maximum number of child elements that may be present on this element. A missing value or 0 implies there is no maximum.";
    default:
      return QVariant();
    }
  }

  switch(index.column())
  {
  case 0:
    return attr->getName();
  case 1:
    return attr->getElement();
  case 2:
    return attr->getMinNumChildren();
  case 3:
    return attr->getMaxNumChildren();
  default:
    return QVariant();
  }

}

bool
ConcretesModel::setData(const QModelIndex &index,
                        const QVariant &value, int role /*= Qt::EditRole*/)
{
  if (role != Qt::DisplayRole && role != Qt::EditRole) return false;
  DeviserConcrete* attr = (*mData)[index.row()];
  if (attr == NULL) return false;

  switch(index.column())
  {
  case 0:
    attr->setName(value.toString());
    return true;
  case 1:
    attr->setElement(value.toString());
    return true;
  case 2:
    attr->setMinNumChildren(value.toInt());
    return true;
  case 3:
    attr->setMaxNumChildren(value.toInt());
    return true;
  default:
    return false;
  }

}

QVariant
ConcretesModel::headerData(int section,
                           Qt::Orientation orientation,
                           int role) const
{
  if (orientation != Qt::Horizontal) return QVariant();

  if (role != Qt::DisplayRole) return QVariant();

  switch(section)
  {
  case 0:
    return "XML name";
  case 1:
    return "Element";
  case 2:
    return "Min No. Children";
  case 3:
    return "Max No. Children";
  default:
    return QVariant();
  }

}

void ConcretesModel::beginAdding()
{
  beginInsertRows(QModelIndex(),mData->count(),mData->count());
}

void ConcretesModel::endAdding()
{
  endInsertRows();
}

void
ConcretesModel::addAttribute(DeviserConcrete* attr)
{
  beginInsertRows(QModelIndex(),mData->count(),mData->count());
  mData->append(attr);
  endInsertRows();
}

DeviserConcrete*
ConcretesModel::getAttribute(int row)
{
  if (row < 0 || row >= mData->count())
    return NULL;
  return (*mData)[row];
}

DeviserConcrete*
ConcretesModel::removeAttribute(int row)
{
  beginRemoveRows(QModelIndex(),row,row);
  DeviserConcrete* result = getAttribute(row);
  mData->removeAt(row);
  endRemoveRows();
  result->deleteLater();
  return result;
}



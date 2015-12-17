#include "attributesmodel.h"

#include <QBrush>

#include <model/deviserattribute.h>

AttributesModel::AttributesModel(
    QObject * parent,
    QList<DeviserAttribute*>* data)
  : QAbstractTableModel(parent)
  , mData(data)
{

}

int
AttributesModel::rowCount(const QModelIndex &) const
{
  return mData->count();
}

int
AttributesModel::columnCount(const QModelIndex &) const
{
  return 6;
}


Qt::ItemFlags
AttributesModel::flags(const QModelIndex &index) const
{
  if (!index.isValid())
    return Qt::ItemIsEnabled;
  return QAbstractTableModel::flags(index) | Qt::ItemIsEditable;
}

QVariant
AttributesModel::data(const QModelIndex &index, int role) const
{
  if (role == Qt::ToolTipRole)
  {
    switch(index.column())
    {
    case NAME:
      return "The name of the attribute/element to be used by code generation.  The XML output may use a different name (see <b>XML Name</b>). This field is required.";
    case TYPE:
      return "The type of the attribute/element. Allowed values are: SId, SIdRef, string, bool, double, int, unsigned int, IDREF, UnitSId, UnitSIdRef, enum, element, lo_element, inline_lo_element. This field is required.";
    case REQUIRED:
      return "States whether the attribute or element is mandatory. This should be <b>true</b> if the attribute/element is mandatory; <b>false</b> if not.";
    case ELEMENT:
      return "This field provides additional information depending on the <b>Type</b> of the attribute/element. It may be the name of the element, enumeration or object being referenced. This field is required for attributes of type SIdRef, enum, element, lo_element, inline_lo_element.";
    case ABSTRACT:
      return "States whether this element is a base class. This should be <b>true</b> if the element is a base class and therefore not instantiated directly; <b>false</b> if not.";
    case XMLName:
      return "The name of the attribute/element as used by the XML output. If blank, this defaults to the <b>Name</b> given.";
    default:
      return QVariant();
    }
  }

  if (role == Qt::BackgroundRole)
  {
    switch(index.column())
    {
    case TYPE:
    case NAME:
      if (index.data().toString().isEmpty())
        return QBrush(QColor(255, 0, 0, 127));
      else
        return QVariant();

    case ELEMENT:
    {
      QString element = index.data().toString();
      if (!element.isEmpty())
        return QVariant();

      QString type = index.model()->index(index.row(), TYPE).data().toString();
      if (type == "element"
          || type == "inline_lo_element"
          || type == "lo_element"
          || type == "enum"
          || type == "array"
          || type == "SIdRef"
          || type == "IDREF"
          || type == "UnitSIdRef"
          )
        return QBrush(QColor(255, 0, 0, 127));
      else
        return QVariant();
    }
    default:
      return QVariant();
    }

  }

  if (role != Qt::DisplayRole &&
      role != Qt::EditRole ) return QVariant();



  const DeviserAttribute* attr = (*mData)[index.row()];

  switch(index.column())
  {
  case NAME:
    return attr->getName();
  case TYPE:
    return attr->getType();
  case REQUIRED:
    return attr->getRequired();
  case ELEMENT:
    return attr->getElement();
  case ABSTRACT:
    return attr->getAbstract();
  case XMLName:
    return attr->getXMLName();
  default:
    return QVariant();
  }

}

bool
AttributesModel::setData(const QModelIndex &index,
                         const QVariant &value, int role /*= Qt::EditRole*/)
{
  if (role != Qt::DisplayRole && role != Qt::EditRole) return false;
  DeviserAttribute* attr = (*mData)[index.row()];
  if (attr == NULL) return false;

  switch(index.column())
  {
  case NAME:
    attr->setName(value.toString());
    return true;
  case TYPE:
    attr->setType(value.toString());
    return true;
  case REQUIRED:
    attr->setRequired(value.toBool());
    return true;
  case ELEMENT:
    attr->setElement(value.toString());
    return true;
  case ABSTRACT:
    attr->setAbstract(value.toBool());
    return true;
  case XMLName:
    attr->setXMLName(value.toString());
    return true;
  default:
    return false;
  }

}

QVariant
AttributesModel::headerData(int section,
                            Qt::Orientation orientation,
                            int role) const
{
  if (orientation != Qt::Horizontal) return QVariant();

  if (role != Qt::DisplayRole) return QVariant();

  switch(section)
  {
  case NAME:
    return "Name";
  case TYPE:
    return "Type";
  case REQUIRED:
    return "Required";
  case ELEMENT:
    return "Element";
  case ABSTRACT:
    return "isBaseClass";
  case XMLName:
    return "XML name";
  default:
    return QVariant();
  }

}

void AttributesModel::beginAdding()
{
  beginInsertRows(QModelIndex(),mData->count(),mData->count());
}

void AttributesModel::endAdding()
{
  endInsertRows();
}

void
AttributesModel::addAttribute(DeviserAttribute* attr)
{
  beginInsertRows(QModelIndex(),mData->count(),mData->count());
  mData->append(attr);
  endInsertRows();
}

DeviserAttribute*
AttributesModel::getAttribute(int row)
{
  if (row < 0 || row >= mData->count())
    return NULL;
  return (*mData)[row];
}

DeviserAttribute*
AttributesModel::removeAttribute(int row)
{
  beginRemoveRows(QModelIndex(),row,row);
  DeviserAttribute* result = getAttribute(row);
  mData->removeAt(row);
  endRemoveRows();
  result->deleteLater();
  return result;
}



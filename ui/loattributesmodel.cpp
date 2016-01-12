#include "loattributesmodel.h"

#include <model/deviserlistofattribute.h>
#include <model/devisersettings.h>

#include <ui/attributesmodel.h>

#include <QBrush>

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

  if (role == Qt::ToolTipRole)
  {
    switch(index.column())
    {
    case AttributesModel::NAME:
      return "The name of the attribute/element to be used by code generation.  The XML output may use a different name (see <b>XML Name</b>). This field is required.";
    case AttributesModel::TYPE:
      return "The type of the attribute/element. Allowed values are: SId, SIdRef, string, bool, double, int, unsigned int, IDREF, UnitSId, UnitSIdRef, enum, element, lo_element, inline_lo_element. This field is required.";
    case AttributesModel::REQUIRED:
      return "States whether the attribute or element is mandatory. This should be <b>true</b> if the attribute/element is mandatory; <b>false</b> if not.";
    case AttributesModel::ELEMENT:
      return "This field provides additional information depending on the <b>Type</b> of the attribute/element. It may be the name of the element, enumeration or object being referenced. This field is required for attributes of type SIdRef, enum, element, lo_element, inline_lo_element.";
    case AttributesModel::ABSTRACT:
      return "States whether this element is a base class. This should be <b>true</b> if the element is a base class and therefore not instantiated directly; <b>false</b> if not.";
    case AttributesModel::XMLName:
      return "The name of the attribute/element as used by the XML output. If blank, this defaults to the <b>Name</b> given.";
    default:
      return QVariant();
    }
  }

  if (role == Qt::BackgroundRole)
  {
    switch(index.column())
    {
    case AttributesModel::TYPE:
    case AttributesModel::NAME:
      if (index.data().toString().isEmpty())
        return QBrush(DeviserSettings::getInstance()->getValidationColor());
      else
        return QVariant();

    case AttributesModel::ELEMENT:
    {
      QString element = index.data().toString();
      if (!element.isEmpty())
        return QVariant();

      QString type = index.model()->index(index.row(), AttributesModel::TYPE).data().toString();
      if (type == "element"
          || type == "inline_lo_element"
          || type == "lo_element"
          || type == "enum"
          || type == "array"
          || type == "SIdRef"
          || type == "IDREF"
          || type == "UnitSIdRef"
          )
        return QBrush(DeviserSettings::getInstance()->getValidationColor());
      else
        return QVariant();
    }
    default:
      return QVariant();
    }

  }

  if (role != Qt::DisplayRole &&
      role != Qt::EditRole ) return QVariant();


  const DeviserListOfAttribute* attr = (*mData)[index.row()];
  switch(index.column())
  {
  case AttributesModel::NAME:
    return attr->getName();
  case AttributesModel::TYPE:
    return attr->getType();
  case AttributesModel::REQUIRED:
    return attr->getRequired();
  case AttributesModel::ELEMENT:
    return attr->getElement();
  case AttributesModel::ABSTRACT:
    return attr->getAbstract();
  case AttributesModel::XMLName:
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
  case AttributesModel::NAME:
    attr->setName(value.toString());
    return true;
  case AttributesModel::TYPE:
    attr->setType(value.toString());
    return true;
  case AttributesModel::REQUIRED:
    attr->setRequired(value.toBool());
    return true;
  case AttributesModel::ELEMENT:
    attr->setElement(value.toString());
    return true;
  case AttributesModel::ABSTRACT:
    attr->setAbstract(value.toBool());
    return true;
  case AttributesModel::XMLName:
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
  case AttributesModel::NAME:
    return "Name";
  case AttributesModel::TYPE:
    return "Type";
  case AttributesModel::REQUIRED:
    return "Required";
  case AttributesModel::ELEMENT:
    return "Element";
  case AttributesModel::ABSTRACT:
    return "isBaseClass";
  case AttributesModel::XMLName:
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


